cmake_minimum_required(VERSION 3.8)
project(pepper_wall_follower)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(naoqi_bridge_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

include_directories(
  include
  ${tf2_INCLUDE_DIRS}
  ${tf2_ros_INCLUDE_DIRS}
  ${tf2_geometry_msgs_INCLUDE_DIRS}
)

add_executable(pepper_wall_follower 
  src/pepper_wall_follower.cpp
)

ament_target_dependencies(pepper_wall_follower
  rclcpp
  geometry_msgs
  sensor_msgs
  nav_msgs
  naoqi_bridge_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
)

install(TARGETS
  pepper_wall_follower
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_export_include_directories(include)
ament_export_dependencies(
  rclcpp
  geometry_msgs
  sensor_msgs
  nav_msgs
  naoqi_bridge_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
)

ament_package()