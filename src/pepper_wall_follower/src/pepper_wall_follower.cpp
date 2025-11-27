#include "pepper_wall_follower/pepper_wall_follower.hpp"
#include <tf2/utils.h>

using namespace std::chrono_literals;

PepperWallFollower::PepperWallFollower()
: Node("pepper_wall_follower")
{
    // Initialize scan data
    for (int i = 0; i < SECTOR_COUNT; i++) {
        scan_data_[i] = 0.0;
    }

    robot_pose_ = 0.0;
    near_start = false;

    // Publishers
    auto qos = rclcpp::QoS(rclcpp::KeepLast(10));
    cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", qos);

    // Subscribers
    scan_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "laser", rclcpp::SensorDataQoS(),
        std::bind(&PepperWallFollower::scan_callback, this, std::placeholders::_1));

    odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
        "odom", qos, std::bind(&PepperWallFollower::odom_callback, this, std::placeholders::_1));

    // Timer for control loop
    update_timer_ = this->create_wall_timer(
        100ms, std::bind(&PepperWallFollower::update_callback, this));

    RCLCPP_INFO(this->get_logger(), "Pepper wall follower initialized");
}

PepperWallFollower::~PepperWallFollower()
{
    // Stop the robot before shutting down
    update_cmd_vel(0.0, 0.0);
}

void PepperWallFollower::scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
    if (msg->ranges.empty()) {
        RCLCPP_WARN(this->get_logger(), "Received empty laser scan");
        return;
    }

    // Calculate readings per sector (Pepper's laser typically has 15Hz scan rate)
    size_t total_readings = msg->ranges.size();
    size_t readings_per_sector = total_readings / SECTOR_COUNT;
    
    //RCLCPP_INFO(this->get_logger(), "Processing laser scan with %zu total readings, %zu per sector",
    //             total_readings, readings_per_sector);

    for (size_t i = 0; i < SECTOR_COUNT; i++) {
        float min_range = std::numeric_limits<float>::max();
        size_t valid_readings = 0;
        size_t start_idx = i * readings_per_sector;
        size_t end_idx = start_idx + readings_per_sector;

        for (size_t j = start_idx; j < end_idx && j < total_readings; j++) {
            float range = msg->ranges[j];
            if (std::isfinite(range) && range >= msg->range_min && range <= msg->range_max) {
                min_range = std::min(min_range, range);
                valid_readings++;
            }
        }

        if (valid_readings == 0) {
            // No valid readings - obstacle very close or sensor blocked
            scan_data_[i] = msg->range_min;  // Use minimum range to indicate obstacle
            RCLCPP_INFO(this->get_logger(), "Sector %zu: No valid readings - possible obstacle", i);
        } else {
            scan_data_[i] = min_range;
        }
        
        RCLCPP_INFO(this->get_logger(), "Sector %zu distance: %f", i, scan_data_[i]);
    }
    PrintScanData();
}

void PepperWallFollower::odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    // Extract yaw from quaternion
    tf2::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    
    robot_pose_ = tf2::getYaw(q);

    // Store start position on first callback
    if (!near_start) {
        start_x = msg->pose.pose.position.x;
        start_y = msg->pose.pose.position.y;
        near_start = true;
    }
}

void PepperWallFollower::update_cmd_vel(double linear, double angular)
{
    auto msg = geometry_msgs::msg::Twist();
    msg.linear.x = linear;
    msg.angular.z = angular;
    
    // Add debug output for velocity commands
    RCLCPP_INFO(this->get_logger(), 
                "Publishing velocity - linear: %.3f, angular: %.3f", 
                linear, angular);
                
    cmd_vel_pub_->publish(msg);
}

void PepperWallFollower::update_callback()
{
    // Reduced speeds for Pepper's safety limits
    const double DESIRED_WALL_DIST = 0.6; // Desired distance from wall
    const double MAX_LINEAR_SPEED = 0.1;    // Reduced from 0.15
    const double MAX_ANGULAR_SPEED = 0.2;    // Reduced from 0.3
    const double WALL_FOLLOW_OFFSET = 0.1;
    const double BLIND_SPOT_OFFSET = 0.15;
    
    // Print all scan data for debugging
    PrintScanData();
    /*for (int i = 0; i < SECTOR_COUNT; i++) {
        RCLCPP_DEBUG(this->get_logger(), 
                     "Sector %d distance: %.2f m", 
                     i, scan_data_[i]);
    }*/
    
    double linear_speed = MAX_LINEAR_SPEED * 0.0f;
    double angular_speed = MAX_ANGULAR_SPEED;

    blind_spot_[BLIND_SPOT_RIGHT] = std::min(scan_data_[FRONT_RIGHT],scan_data_[RIGHT_FRONT]);
    blind_spot_[BLIND_SPOT_LEFT] = std::min(scan_data_[FRONT_LEFT],scan_data_[LEFT_FRONT]);

if (scan_data_[FRONT_RIGHT] <= 0.10f || scan_data_[FRONT_LEFT] <= 0.10f) {
    if (scan_data_[FRONT_RIGHT] <= 0.10f && scan_data_[FRONT_LEFT] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading front side");
        //scan_data_[FRONT_RIGHT] = DESIRED_WALL_DIST;
        //scan_data_[FRONT_LEFT] = DESIRED_WALL_DIST;
    }
    else if (scan_data_[FRONT_RIGHT] <= 0.10f) {
        // Faulty reading on right side - use left reading as proxy
        scan_data_[FRONT_RIGHT] = scan_data_[FRONT_LEFT]; // Use left reading as proxy
    }
    else if (scan_data_[FRONT_LEFT] <= 0.10f) {
        // Faulty reading on left side - use right reading as proxy
        scan_data_[FRONT_LEFT] = scan_data_[FRONT_RIGHT]; // Use right reading as proxy
    }
}

if (scan_data_[RIGHT_FRONT] <= 0.10f || scan_data_[RIGHT_BACK] <= 0.10f) {
    if (scan_data_[RIGHT_FRONT] <= 0.10f && scan_data_[RIGHT_BACK] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading right side");
        //scan_data_[RIGHT_FRONT] = DESIRED_WALL_DIST;
        //scan_data_[RIGHT_BACK] = DESIRED_WALL_DIST;
    }
    else if (scan_data_[RIGHT_FRONT] <= 0.10f) {
        // Faulty reading on right front side - use right back reading as proxy
        scan_data_[RIGHT_FRONT] = scan_data_[RIGHT_BACK]; // Use right back reading as proxy
    }
    else if (scan_data_[RIGHT_BACK] <= 0.10f) {
        // Faulty reading on right back side - use right front reading as proxy
        scan_data_[RIGHT_BACK] = scan_data_[RIGHT_FRONT]; // Use right front reading as proxy
    }
}

if (scan_data_[LEFT_FRONT] <= 0.10f || scan_data_[LEFT_BACK] <= 0.10f) {
    if (scan_data_[LEFT_FRONT] <= 0.10f && scan_data_[LEFT_BACK] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading left side");
        //scan_data_[LEFT_FRONT] = DESIRED_WALL_DIST;
        //scan_data_[LEFT_BACK] = DESIRED_WALL_DIST;
    }
    else if (scan_data_[LEFT_FRONT] <= 0.10f) {
        // Faulty reading on left front side - use left back reading as proxy
        scan_data_[LEFT_FRONT] = scan_data_[LEFT_BACK]; // Use left back reading as proxy
    }
    else if (scan_data_[LEFT_BACK] <= 0.10f) {
        // Faulty reading on left back side - use left front reading as proxy
        scan_data_[LEFT_BACK] = scan_data_[LEFT_FRONT]; // Use left front reading as proxy
    }
}

    // --- Obstacle avoidance: anything close in front ---
if (scan_data_[FRONT_RIGHT] < DESIRED_WALL_DIST * 0.8f ||
    scan_data_[FRONT_LEFT]  < DESIRED_WALL_DIST * 0.8f) {
    // Obstacle in front → turn left in place
    if (scan_data_[FRONT_RIGHT] <= 0.10f &&
        scan_data_[FRONT_LEFT] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading  from front");
    }
    else {
        linear_speed = 0.0f;
        angular_speed = MAX_ANGULAR_SPEED;
        RCLCPP_INFO(this->get_logger(), "Obstacle ahead - turning left");
    }
}

// --- Too close to right wall ---
else if (scan_data_[RIGHT_FRONT] < (DESIRED_WALL_DIST - WALL_FOLLOW_OFFSET) * 0.8f ||
         scan_data_[RIGHT_BACK]  < (DESIRED_WALL_DIST - WALL_FOLLOW_OFFSET) * 0.9f) {
    // Steer slightly left to increase distance
    if (scan_data_[RIGHT_FRONT] <= 0.10f &&
        scan_data_[RIGHT_BACK] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading from right");
    }
    else {
        linear_speed = MAX_LINEAR_SPEED * 0.2f;
        angular_speed = MAX_ANGULAR_SPEED;
        RCLCPP_INFO(this->get_logger(), "Too close to right wall - adjusting left");
    }
}

else if (blind_spot_[BLIND_SPOT_RIGHT] < (DESIRED_WALL_DIST  - WALL_FOLLOW_OFFSET + BLIND_SPOT_OFFSET) * 0.8f) {
    // Steer slightly left to increase distance
    if (blind_spot_[BLIND_SPOT_RIGHT] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading from right blind spot");
    }
    else {
        linear_speed = MAX_LINEAR_SPEED * 0.1f;
        angular_speed = MAX_ANGULAR_SPEED;
        RCLCPP_INFO(this->get_logger(), "Too close to right wall (blind spot) - adjusting left");
    }
}

// --- Too close to left wall ---
else if (scan_data_[LEFT_FRONT] < (DESIRED_WALL_DIST - WALL_FOLLOW_OFFSET) * 0.8f ||
         scan_data_[LEFT_BACK] < (DESIRED_WALL_DIST - WALL_FOLLOW_OFFSET) * 0.9f) {
    // Steer slightly right to increase distance
    if (scan_data_[LEFT_FRONT] <= 0.10f &&
        scan_data_[LEFT_BACK] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading from left ");
    }
    else {
        linear_speed = MAX_LINEAR_SPEED * 0.2f;
        angular_speed = -MAX_ANGULAR_SPEED;
        RCLCPP_INFO(this->get_logger(), "Too close to left wall - adjusting right");
    }
}

else if (blind_spot_[BLIND_SPOT_LEFT] < (DESIRED_WALL_DIST - WALL_FOLLOW_OFFSET + BLIND_SPOT_OFFSET) * 0.8f) {
    // Steer slightly right to increase distance
    if (blind_spot_[BLIND_SPOT_LEFT] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading from left blind spot");
    }
    else {
        linear_speed = MAX_LINEAR_SPEED * 0.1f;
        angular_speed = -MAX_ANGULAR_SPEED;
        RCLCPP_INFO(this->get_logger(), "Too close to left wall (blind spot) - adjusting right");
    }
}

// --- Too far from right wall ---
else if (scan_data_[RIGHT_FRONT] >= (DESIRED_WALL_DIST + WALL_FOLLOW_OFFSET) * 0.8f &&
         scan_data_[RIGHT_BACK]  >= (DESIRED_WALL_DIST + WALL_FOLLOW_OFFSET) * 0.5f) {
    // Steer slightly right to reduce distance
    if (scan_data_[RIGHT_FRONT] <= 0.10f) {
        RCLCPP_INFO(this->get_logger(), "Faulty reading too far from right");
    }
    else {
        linear_speed = MAX_LINEAR_SPEED * 0.5f;
        angular_speed = -MAX_ANGULAR_SPEED;
        RCLCPP_INFO(this->get_logger(), "Too far from right wall - adjusting right");
    }
}

// --- Path clear, keep moving straight ---
else {
    linear_speed = MAX_LINEAR_SPEED * 0.6f;
    angular_speed = 0.0f;
    RCLCPP_INFO(this->get_logger(), "Following wall smoothly");
}
    //linear_speed = 0.0f; // TEMPORARY STOP FOR TESTING
    //angular_speed = 0.0f;
    update_cmd_vel(linear_speed, angular_speed);
}

void PepperWallFollower::PrintScanData() 
{
    /*RCLCPP_INFO(this->get_logger(), 
        "Scan Data:\n"
        "  Front: %.2f\n"
        "  FR/RF: %.2f/%.2f\n"
        "  Right: %.2f (F:%.2f B:%.2f)\n"
        "  BR/RB: %.2f/%.2f\n"
        "  Back: %.2f\n"
        "  BL/LB: %.2f/%.2f\n"
        "  Left: %.2f (F:%.2f B:%.2f)\n"
        "  FL/LF: %.2f/%.2f",
        scan_data_[FRONT],
        scan_data_[FRONT_RIGHT], scan_data_[RIGHT_FRONT],
        scan_data_[RIGHT], scan_data_[RIGHT_FRONT], scan_data_[RIGHT_BACK],
        scan_data_[BACK_RIGHT], scan_data_[RIGHT_BACK],
        scan_data_[BACK],
        scan_data_[BACK_LEFT], scan_data_[LEFT_BACK],
        scan_data_[LEFT], scan_data_[LEFT_FRONT], scan_data_[LEFT_BACK],
        scan_data_[FRONT_LEFT], scan_data_[LEFT_FRONT]);*/
    RCLCPP_INFO(this->get_logger(), 
        "Scan Data:\n"
        "  FRONT_LEFT: %.2f\n"
        "  FRONT_RIGHT: %.2f\n"
        "  RIGHT_BACK: %.2f\n"
        "  RIGHT_FRONT: %.2f\n"
        "  LEFT_BACK: %.2f\n"
        "  LEFT_FRONT: %.2f\n"
        "  BLIND_SPOT_LEFT: %.2f\n"
        "  BLIND_SPOT_RIGHT: %.2f\n",
        scan_data_[FRONT_LEFT],
        scan_data_[FRONT_RIGHT],
        scan_data_[RIGHT_BACK],
        scan_data_[RIGHT_FRONT],
        scan_data_[LEFT_BACK],
        scan_data_[LEFT_FRONT],
        blind_spot_[BLIND_SPOT_LEFT],
        blind_spot_[BLIND_SPOT_RIGHT]);
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PepperWallFollower>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}