# COMP3431 RTAB-MAP with Key Teleoperation for Pepper robot using ROS2-NAOqi Driver

## Versions
- Ubuntu 22.04
- ROS Humble
- NAOqi v2.5
- Python 3.10.12

## Public Repositories Used (Follow linked repository instructions for installation)
- ROS2 Naoqi_driver: https://github.com/ros-naoqi/naoqi_driver2
- Teleop Control: https://github.com/ros-teleop/teleop_tools
- RTAB-MAP: https://github.com/introlab/rtabmap_ros/tree/ros2

## Commands to Run Code
Local terminal to SSH to Pepper robot:
```
ssh nao@<pepper_ip> # (It will prompt to ask for password "pepper">
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

# Like the repo, these packages never change
colcon build --symlink-install --packages-skip nao_meshes pepper_meshes --parallel-workers 1
# In case the whole src folder exceeds RAM
colcon build --packages-select naoqi_driver --parallel-workers 1
```









