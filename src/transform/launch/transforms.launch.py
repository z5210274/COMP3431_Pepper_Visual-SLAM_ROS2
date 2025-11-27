from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='transform',
            executable='pepper_tf',
            name='pepper_static_tf'
        )
    ])