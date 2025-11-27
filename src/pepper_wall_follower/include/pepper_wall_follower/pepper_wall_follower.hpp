#ifndef PEPPER_WALL_FOLLOWER_HPP_
#define PEPPER_WALL_FOLLOWER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

class PepperWallFollower : public rclcpp::Node
{
public:
  PepperWallFollower();
  ~PepperWallFollower();

private:
  // Constants for laser scan angles
  enum { // Right is the lowest, front is the middle, left is the highest
    /*FRONT = 0,
    FRONT_RIGHT = 1,
    RIGHT_FRONT = 2,
    RIGHT = 3,
    RIGHT_BACK = 4,
    BACK_RIGHT = 5,
    BACK = 6,
    BACK_LEFT = 7,
    LEFT_BACK = 8,
    LEFT = 9,
    LEFT_FRONT = 10,
    FRONT_LEFT = 11*/
    RIGHT_BACK = 0,
    RIGHT_FRONT = 1,
    FRONT_RIGHT = 2,
    FRONT_LEFT = 3,
    LEFT_FRONT = 4,
    LEFT_BACK = 5,
    SECTOR_COUNT = 6,
    BLIND_SPOT_RIGHT = 0,
    BLIND_SPOT_LEFT = 1
  };

  // ROS Publishers
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;

  // ROS Subscribers
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;

  // Timer
  rclcpp::TimerBase::SharedPtr update_timer_;

  // Callback functions
  void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg);
  void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg);
  void update_callback();
  void update_cmd_vel(double linear, double angular);
  void PrintScanData();

  // Member variables
  double scan_data_[SECTOR_COUNT];
  double blind_spot_[SECTOR_COUNT/3];
  double robot_pose_;
  double start_x;
  double start_y;
  bool near_start;

  // Pepper-specific parameters
  const double MAX_LINEAR_VELOCITY = 0.35;  // Pepper's max linear velocity
  const double MAX_ANGULAR_VELOCITY = 1.0;  // Pepper's max angular velocity
  const double WALL_DISTANCE = 0.5;         // Desired distance from wall
};

#endif  // PEPPER_WALL_FOLLOWER_HPP_