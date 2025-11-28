# COMP3431 RTAB-MAP with Key Teleoperation for Pepper robot using ROS2-NAOqi Driver

## Versions
- Ubuntu 22.04
- ROS Humble
- NAOqi v2.5
- Python 3.10.12

## Public Repositories Used (Follow linked repository instructions for installation and check Noteworthy Packages section for how to configure to this repository environment)
- ROS2 Naoqi_driver: https://github.com/ros-naoqi/naoqi_driver2 (Installing this would give the currently empty; nao_meshes, naoqi_bridge_msgs, naoqi_driver2, naoqi_lipqi, naoqi_libqicore and pepper_meshes packages.)
- Teleop Control: https://github.com/ros-teleop/teleop_tools
- RTAB-MAP: https://github.com/introlab/rtabmap_ros/tree/ros2 (Installing this would give the currently empty; rtabmap and rtabmap_ros packages.)

## Noteworthy Packages
- naoqi_driver2 (Creates ROS2 topics for your packages to publish or subscribe to that connects to the NAOqi modules on Pepper. Mainly modified boot_config.json to create compatible and necessary topics, and naoqi_driver.cpp to change camera fps and resolution.)
- pepper_wall_follower (Custom wall following implementation for Pepper using its laser sensors)
- rtabmap_ros (Visual Navigation and Environmental Mapping that uses Pepper's camera and depth sensors. )
- transform (Static transformations of Pepper's odom to optical frames for mapping. Not functional right now)
- key_teleop (Keyboard control for Pepper movement. Changed key_teleop.py to subscribe to \cmd_vel instead of \key_vel and tuned movement rate parameters.)

## Commands to Run Code
Local terminal to SSH to Pepper robot:
```
ssh nao@<pepper_ip> # <It will prompt to ask for password "pepper">
qicli call ALAutonomousLife.setState "disabled"
qicli call ALMotion.wakeUp
qicli call ALAutonomousMoves.setBackgroundStrategy "none"
qicli call ALMotion.setStiffnesses "[\"HeadPitch\", \"HeadYaw\"]" "[1.0, 1.0]"
qicli call ALMotion.setAngles "HeadPitch" 0.025 0.1
```
ROS Package Building
```
# Running ROS2 code (every new terminal):
cd ~/ros_ws
source /opt/ros/humble/setup.bash      # system ROS2
source ~/ros_ws/install/setup.bash     # your workspace

# Like the repo, these packages never change (repeated building)
colcon build --symlink-install --packages-skip nao_meshes pepper_meshes --parallel-workers 1
# In case the whole src folder exceeds RAM
colcon build --packages-select naoqi_driver --parallel-workers 1
```
Packages to Run
```
# Naoqi_driver, IP's can differ when running through WSL Tunnel
ros2 launch naoqi_driver naoqi_driver.launch.py \
  nao_ip:=<pepper_ip> \
  qi_listen_url:=tcp://<robot_host_ip>:<port> \
  enable_audio:=false

# In separate terminals for each static transform (can create own package to compile all together)
ros2 run tf2_ros static_transform_publisher 0 0 0 0 0 0 odom base_link
ros2 run tf2_ros static_transform_publisher 0.10 0 1.05  0 0 0 base_link camera_front_link
ros2 run tf2_ros static_transform_publisher 0.10 0 1.02  0 0 0  base_link camera_depth_link
ros2 run tf2_ros static_transform_publisher 0 0 0  -1.5708 0 -1.5708 camera_front_link CameraTop_optical_frame
ros2 run tf2_ros static_transform_publisher 0 0 0  -1.5708 0 -1.5708  camera_depth_link CameraDepth_optical_frame

# Teleop Control (key_teleop)
ros2 run key_teleop key_teleop --ros-args -p twist_stamped_enabled:=false

# RTAB-MAP + Visualizer
ros2 launch rtabmap_launch rtabmap.launch.py \
    rtabmap_args:="--delete_db_on_start" \
    rgb_topic:=/camera/front/image_raw \
    depth_topic:=/camera/depth/image_raw \
    camera_info_topic:=/camera/front/camera_info \
    frame_id:=camera_front_link \
    approx_sync:=true \
    visual_odometry:=true \
    approx_sync_max_interval:=0.5 \
    wait_imu_to_init:=false \
    imu_topic:=/imu/base \
    rviz:=true \
    odom_topic:=/odom
```
Pepper Wall Following with Laser Sensors
```
ros2 launch pepper_wall_follower pepper_wall_follower.launch.py
```







