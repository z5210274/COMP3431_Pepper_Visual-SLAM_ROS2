from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='pepper_wall_follower',
            executable='pepper_wall_follower',
            name='pepper_wall_follower',
            output='screen',
            parameters=[{
                'use_sim_time': False
            }]
        )
    ])