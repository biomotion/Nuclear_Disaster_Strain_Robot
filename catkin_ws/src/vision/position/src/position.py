#!/usr/bin/env python

import numpy as np
import cv2
import roslib
import rospy
import tf
import struct
import math
import time
from sensor_msgs.msg import Image
from sensor_msgs.msg import CameraInfo, CompressedImage
from geometry_msgs.msg import PoseArray, PoseStamped, Point32, PointStamped
from visualization_msgs.msg import Marker, MarkerArray
import rospkg
from nav_msgs.msg import Path
from cv_bridge import CvBridge, CvBridgeError
import torch
import torch.nn as nn
import torch.backends.cudnn as cudnn
from torch.autograd import Variable
from bb_pointnet.msg import * 
import os 
import message_filters
#from ssd_mobile_lite.msg import Position

#print('hi')

class position(object):
    def __init__(self):
        self.fx = 0
        self.fy = 0
        self.cx = 0
        self.cy = 0
        self.cv_bridge = CvBridge() 
        self.depth_image = None
        self.ans_cnt = 0

        xy_position = rospy.Subscriber("/position", Point32, self.getbb_cb )
        cam_info_sb = rospy.Subscriber("/camera/color/camera_info", CameraInfo , self.caminfo_cb )
        depth_image_sb = rospy.Subscriber("/camera/aligned_depth_to_color/image_raw", Image , self.depth_img_cb )

        self.xyz_position = rospy.Publisher("/xyz_position", Point32, queue_size = 1)
        
        self.p_stamp_pb = rospy.Publisher("/obj_point", PointStamped, queue_size = 1)
    
    def caminfo_cb(self,info_msg):

        self.fx = info_msg.P[0];
        self.fy = info_msg.P[5];
        self.cx = info_msg.P[2];
        self.cy = info_msg.P[6];


  
    def depth_to_point(self, x, y):

        inv_fx = 1.0/self.fx
        inv_fy = 1.0/self.fy

        real_z = self.depth_image[y, x]
        
        bound_z = self.depth_image[y, 639]
        bound_x = (639 - self.cx) * bound_z * inv_fx
        
        # print('img_x:{}, img_y:{} z_val:{}'.format(x, y, real_z))

        real_x = (x - self.cx) * real_z * inv_fx
        real_y = (y - self.cy) * real_z * inv_fy
        
        xyz_position_msg = Point32()
        xyz_position_msg.x = real_x
        xyz_position_msg.y = real_y
        xyz_position_msg.z = real_z
        self.xyz_position.publish(xyz_position_msg)

        return [real_x, real_y, real_z]
    
    def depth_img_cb(self, img_msg):
        # try:
        #     if self.is_compressed:
        #         np_arr = np.fromstring(img_msg.data, np.uint8)
        #         cv_image = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
        #     else:
        #         cv_image = self.cv_bridge.imgmsg_to_cv2(img_msg, "bgr8")
        cv_image = self.cv_bridge.imgmsg_to_cv2(img_msg, desired_encoding="passthrough")
        # except CvBridgeError as e:
        #     print(e)
        
        self.depth_image = cv_image
        # (rows, cols, channels) = cv_image.shape
        # self.width = cols
        # self.height = rows
        # predict_img = self.predict(cv_image)
        # try:
        #     self.image_pub.publish(self.cv_bridge.cv2_to_imgmsg(predict_img, "bgr8"))
        # except CvBridgeError as e:
        #     print(e)
    def getbb_cb(self, msg):
        if self.fx == 0:
            print('camera info is not ready!')
            return
        if type(self.depth_image) == 'NoneType':
            print('depth image is not ready!')
            return
        
        # print('img_x:{}, img_y:{}'.format(msg.x, msg.y))

        img_x = int(msg.x)
        img_y = int(msg.y)
        
        pose_msg = PointStamped()
        real_x, real_y, real_z = self.depth_to_point(img_x, img_y)
        pose_msg.point.x = float(real_z)/1000
        pose_msg.point.y = float(-real_x)/1000
        pose_msg.point.z = 0 #float(real_y)/1000
        pose_msg.header.frame_id = '/camera_link'
        pose_msg.header.seq = self.ans_cnt
        self.ans_cnt = self.ans_cnt + 1

        #print('x:{}, y:{} z:{}'.format(pose_msg.point.x, pose_msg.point.y, pose_msg.point.z))
        
        pose_msg.header.stamp = rospy.Time.now()
        self.p_stamp_pb.publish(pose_msg)
         
        


if __name__ == '__main__': 
    rospy.init_node('position',anonymous=False)
    position = position()
    #rospy.on_shutdown(position.onShutdown)
    rospy.spin()
