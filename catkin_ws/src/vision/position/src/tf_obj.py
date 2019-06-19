#!/usr/bin/env python

import rospy
import tf
import tf.transformations as tr
from geometry_msgs.msg import PoseStamped, PointStamped
import numpy as np

class tf_obj(object):
    """docstring for ClassName"""
    def __init__(self):
        super(tf_obj, self).__init__()

        self.pose_msg = None

        sub_pose = rospy.Subscriber("/pozyx_tag_node/pozyx_pose", PoseStamped, self.pose_callback, queue_size=1)
        sub_obj_pose = rospy.Subscriber("/obj_point", PointStamped, self.point_cb, queue_size=1)

        self.pub_obj_position = rospy.Publisher("/obj_position", PointStamped, queue_size=1)

    def pose_callback(self, msg):
        print "pose cb"
        self.pose_msg = msg
    def point_cb(self, msg):
        print "point cb"
        trans = [self.pose_msg.pose.position.x/1000, self.pose_msg.pose.position.y/1000, self.pose_msg.pose.position.z/1000]
        rot = [self.pose_msg.pose.orientation.x, self.pose_msg.pose.orientation.y, self.pose_msg.pose.orientation.z, self.pose_msg.pose.orientation.w]
        pose_matrix = tr.compose_matrix(angles = tr.euler_from_quaternion(rot), translate = trans)

        pt_trans = [msg.point.x, msg.point.y, msg.point.z]
        pt_rot = [0, 0, 0, 1]
        pt_matrix = tr.compose_matrix(angles= tr.euler_from_quaternion(pt_rot), translate = pt_trans)

        obj_pose = np.dot(pose_matrix, pt_matrix)
        obj_position = tf.transformations.translation_from_matrix(obj_pose)
        print "pose = ", self.pose_msg.pose
        print "point = ", msg.point
        print "obj position = ", obj_position
        point_msg = PointStamped()
        point_msg.header.stamp = rospy.Time()
        point_msg.header.seq = msg.header.seq
        point_msg.header.frame_id = "map"
        point_msg.point.x = obj_position[0]
        point_msg.point.y = obj_position[1]
        point_msg.point.z = obj_position[2]
        self.pub_obj_position.publish(point_msg)
        



if __name__ == '__main__':
    rospy.init_node('tf_obj_node',anonymous=False)
    node = tf_obj()
    rospy.spin()