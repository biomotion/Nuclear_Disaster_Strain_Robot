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
from geometry_msgs.msg import PoseArray, PoseStamped, Point32
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


class position(object):
    def __init__(self):
        self.fx = 0
        self.fy = 0
        self.cx = 0
        self.cy = 0
        self.cv_bridge = CvBridge() 
        self.depth_image = 0

        xy_position = rospy.Subscriber("/position", Point32, self.getbb_cb )
        CameraInfo = rospy.Subscriber("/camera/color/camera_info", CameraInfo , self.caminfo_cb )
        Extrinsics = rospy.Subscriber("/camera/extrinsics/depth_to_color", Image , self.depth_img_cb )

        xyz_position = rospy.Publisher("/xyz_position", Point32, queue_size = 1)

    
    def caminfo_cb(self,info_msg):

        self.fx = info_msg.P[0];
        self.fy = info_msg.P[5];
        self.cx = info_msg.P[2];
        self.cy = info_msg.P[6];


  
    def depth_to_point(self, x, y):

        inv_fx = 1.0/self.fx
        inv_fy = 1.0/self.fy

        z = self.depth_image[x, y]

        real_x = (x - self.cx) * z * inv_fx
        real_y = (y - self.cy) * z * inv_fy
        
        xyz_position_msg = Point32()
        xyz_position_msg.x = x
        xyz_position_msg.y = y
        xyz_position_msg.z = z
        self.xyz_position.publish(xyz_position_msg)

        return [x, y, z]
    
    def depth_img_cb(self, img_msg):
        try:
            if self.is_compressed:
                np_arr = np.fromstring(img_msg.data, np.uint8)
                cv_image = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
            else:
                cv_image = self.cv_bridge.imgmsg_to_cv2(img_msg, "bgr8")
        except CvBridgeError as e:
            print(e)
        
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
        if self.depth_image == 0:
            print('depth image is not ready!')
            return

        img_x = msg.x
        img_y = msg.y
        self.depth_to_point(img_x, img_y)
        


if __name__ == '__main__': 
    rospy.init_node('position',anonymous=False)
    position = position()
    #rospy.on_shutdown(position.onShutdown)
    rospy.spin()
