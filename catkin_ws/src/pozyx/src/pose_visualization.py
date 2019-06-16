#!/usr/bin/env python
import rospy
from visualization_msgs.msg import Marker
from geometry_msgs.msg import PoseStamped

class visualizer(object):
    def __init__(self):
        self.pub_marker = rospy.Publisher("~pose_visualizer", Marker, queue_size=1)
        self.sub_pose = rospy.Subscriber("/pozyx_tag_node/pozyx_pose", PoseStamped, self.pose_cb, queue_size=1)
    def pose_cb(self, pose_msg):
        marker_msg = Marker()
	marker_msg.id = 0
        marker_msg.action = Marker.ADD
        marker_msg.pose.position.x = pose_msg.pose.position.x
        marker_msg.pose.position.y = pose_msg.pose.position.y
        marker_msg.pose.position.z = pose_msg.pose.position.z

        marker_msg.pose.orientation.x = 0.0
        marker_msg.pose.orientation.y = 0.0
        marker_msg.pose.orientation.z = 0.0
        marker_msg.pose.orientation.w = 1.0
        marker_msg.scale.x = 1.0
        marker_msg.scale.y = 1.0
        marker_msg.scale.z = 1.0

        marker_msg.color.r = 1.0
        marker_msg.color.g = 0.0
        marker_msg.color.b = 1.0
        marker_msg.color.a = 1.0

        marker_msg.lifetime = rospy.Duration()
        self.pub_marker.publish(marker_msg)



if __name__ == '__main__':
	rospy.init_node('pose_visualization',anonymous=False)
	node = visualizer()
	rospy.spin()
