import rclpy
from rclpy.node import Node
from tf2_ros import StaticTransformBroadcaster
from geometry_msgs.msg import TransformStamped, Quaternion
import math


class PepperStaticTF(Node):
    def __init__(self):
        super().__init__('pepper_static_tf')

        self.broadcaster = StaticTransformBroadcaster(self)

        transforms = []

        # -----------------------------
        # 1) odom → base_link
        # -----------------------------
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = "odom"
        t.child_frame_id = "base_link"
        transforms.append(t)

        # -----------------------------
        # 2) base_link → camera_front_link
        # -----------------------------
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = "base_link"
        t.child_frame_id = "camera_front_link"
        t.transform.translation.x = 0.10
        t.transform.translation.y = 0.0
        t.transform.translation.z = 1.05
        t.transform.rotation = self.quat_from_euler(0, 0, 0)
        transforms.append(t)

        # -----------------------------
        # 3) camera_front_link → CameraTop_optical_frame
        # -----------------------------
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = "camera_front_link"
        t.child_frame_id = "CameraTop_optical_frame"
        t.transform.translation.x = 0.0
        t.transform.translation.y = 0.0
        t.transform.translation.z = 0.0
        t.transform.rotation = self.quat_from_euler(-1.5708, 0.0, -1.5708)
        transforms.append(t)

        # -----------------------------
        # 4) base_link → camera_depth_link
        # -----------------------------
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = "base_link"
        t.child_frame_id = "camera_depth_link"
        t.transform.translation.x = 0.10
        t.transform.translation.y = 0.0
        t.transform.translation.z = 1.02
        t.transform.rotation = self.quat_from_euler(0, 0, 0)
        transforms.append(t)

        # -----------------------------
        # 5) camera_depth_link → CameraDepth_optical_frame
        # -----------------------------
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = "camera_depth_link"
        t.child_frame_id = "CameraDepth_optical_frame"
        t.transform.translation.x = 0.0
        t.transform.translation.y = 0.0
        t.transform.translation.z = 0.0
        t.transform.rotation = self.quat_from_euler(-1.5708, 0.0, -1.5708)
        transforms.append(t)

        # Publish all transforms at once
        self.broadcaster.send_transforms(transforms)

        self.get_logger().info("Pepper static TF tree published.")


    def quat_from_euler(self, r, p, y):
        import tf_transformations
        q = tf_transformations.quaternion_from_euler(r, p, y)
        return Quaternion(x=q[0], y=q[1], z=q[2], w=q[3])


def main():
    rclpy.init()
    node = PepperStaticTF()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
