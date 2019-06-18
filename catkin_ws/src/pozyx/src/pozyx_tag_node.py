#!/usr/bin/env python
import rospy
import rospkg
from geometry_msgs.msg import PoseStamped
from pypozyx import *
from pypozyx.tools.device_list import *
from pypozyx.tools.discovery import *
from pypozyx.tools.version_check import *
from tf.transformations import quaternion_from_euler
from math import radians
from visualization_msgs.msg import Marker

import csv

sample_pts = 1
sample_rate = 10 #hz

serial_port = get_first_pozyx_serial_port()
print(serial_port)
pozyx = PozyxSerial(serial_port)
pozyx.printDeviceInfo()

def printErrorCode():
    error_code = SingleRegister()
    status = pozyx.getErrorCode(error_code)
    if status == POZYX_SUCCESS:
        print pozyx.getErrorMessage(error_code)

def pozyx_setup():


    pozyx.clearDevices()
    status = pozyx.doDiscovery(discovery_type=PozyxConstants.DISCOVERY_ALL_DEVICES, slots=4)

    # list_size = SingleRegister()
    # pozyx.getNumberOfAnchors(list_size)
    # anchor_list = DeviceList(list_size=list_size[0])
    # pozyx.getAnchorIds(anchor_list)
    # if status == POZYX_SUCCESS:
    #     print anchor_list
    #     print get_device_list(pozyx)

    '''
    status = pozyx.doAnchorCalibration(dimension=PozyxConstants.DIMENSION_3D, num_measurements=10, anchors=anchor_list)
    if status == POZYX_SUCCESS:
        for device_id in anchor_list:
            coordinate = Coordinate()
            pozyx.getDeviceCoordinate(device_id, coordinate)
            print coordinate
    '''
    '''
    Note:
        Remember that the first anchor should be at x=0, y=0,
        and the second anchor should be at y=0,
        the third anchor should have a positive y value
    '''
    anchors = [DeviceCoordinates(0x6754, 1, Coordinates(0, 0, 490)),
               DeviceCoordinates(0x674f, 1, Coordinates(3000, 0, 490)),
               DeviceCoordinates(0x6e5d, 1, Coordinates(0, 3000, 490)),
               DeviceCoordinates(0x6755, 1, Coordinates(3000, 3000, 490))]

    status = pozyx.clearDevices()
    for anchor in anchors:
        status &= pozyx.addDevice(anchor)
    if len(anchors) > 4:
        status &= pozyx.setSelectionOfAnchors(PozyxConstants.ANCHOR_SELECT_AUTO, len(anchors))

    if status == POZYX_SUCCESS:
        for anchor in anchors:
            anchor_coords = Coordinates()
            pozyx.getDeviceCoordinates(anchor, anchor_coords)
            print "Anchor:", anchor, "coordinate:", anchor_coords
        print get_device_list(pozyx)
    else:
        printErrorCode()

def pubPoses():

    pub_poses = rospy.Publisher('~pozyx_pose', PoseStamped, queue_size=1)
    # markerPub = rospy.Publisher('robotMarker', Marker, queue_size=1)
    rate = rospy.Rate(sample_rate)

    # while not rospy.is_shutdown():

    #     # create containers
    #     position = Coordinates()
    #     orientation = EulerAngles()
    #     # getting 3D position and orientation
    #     status = pozyx.doPositioning(position, dimension=PozyxConstants.DIMENSION_3D,algorithm=PozyxConstants.POSITIONING_ALGORITHM_NONE)
    #     status &= pozyx.getEulerAngles_deg(orientation)
    #     if status == POZYX_SUCCESS: # if get pose from pozyx
    #         #print "X:", position.x, ", Y:", position.y, "Z:", position.z
    #         print "Orientation:", str(orientation)
    #         print "Translation:", str(position)
    #         #create pose with stamp
    #         tag_pose = PoseStamped()
    #         tag_pose.header.stamp = rospy.Time.now()
    #         tag_pose.pose.position.x = position.x
    #         tag_pose.pose.position.y = position.y
    #         tag_pose.pose.position.z = position.z
    #         # http://wiki.ros.org/tf2/Tutorials/Quaternions
    #         tag_pose.pose.orientation.x = 0
    #         tag_pose.pose.orientation.y = 0
    #         tag_pose.pose.orientation.z = 0
    #         tag_pose.pose.orientation.w = 1
    #         # rot = quaternion_from_euler(radians(orientation.heading), radians(orientation.roll), radians(orientation.pitch))
    #         # tag_pose.pose.orientation.x = rot[0]
    #         # tag_pose.pose.orientation.y = rot[1]
    #         # tag_pose.pose.orientation.z = rot[2]
    #         # tag_pose.pose.orientation.w = rot[3]
    #         #if not (position.x==0 or position.y==0 or position.z==0):
    #         pub_poses.publish(tag_pose)

    #         # robotMarker = Marker()
    #         # robotMarker.header.frame_id = "Cmap"
    #         # robotMarker.header.stamp    = rospy.Time.now()
    #         # robotMarker.ns = "robot"
    #         # robotMarker.id = 0
    #         # robotMarker.type = Marker.SPHERE
    #         # robotMarker.action = Marker.ADD
    #         # robotMarker.pose.position = position
    #         # robotMarker.pose.orientation = tag_pose.pose.orientation
    #         # robotMarker.scale.x = 0.1
    #         # robotMarker.scale.y = 0.1
    #         # robotMarker.scale.z = 0.1
    #         #
    #         # robotMarker.color.r = 1.0
    #         # robotMarker.color.g = 0.0
    #         # robotMarker.color.b = 1.0
    #         # robotMarker.color.a = 1.0
    #         #
    #         # markerPub.publish(robotMarker)
    #     else:
    #         printErrorCode()

    #     rate.sleep()

    while not rospy.is_shutdown():
        x = []
        y = []
        z = []

        ox = []
        oy = []
        oz = []
        ow = []
        for i in range(sample_pts):
            # start = rospy.Time.now()
            position = Coordinates()
            orientation = EulerAngles()
            status = pozyx.doPositioning(position, dimension=PozyxConstants.DIMENSION_3D, algorithm=PozyxConstants.POSITIONING_ALGORITHM_TRACKING)
            status &= pozyx.getEulerAngles_deg(orientation)
            if status == POZYX_SUCCESS: # if get pose from pozyx
                #print "X:", position.x, ", Y:", position.y, "Z:", position.z
                #print "Orientation:", str(orientation)
                #print "Translation:", str(position)
                #pass
                x.append(float(position.x))
                y.append(float(position.y))
                z.append(float(position.z))
                # http://wiki.ros.org/tf2/Tutorials/Quaternions
                rot = quaternion_from_euler(radians(orientation.heading), radians(orientation.roll), radians(orientation.pitch))
                ox.append(rot[0])
                oy.append(rot[1])
                oz.append(rot[2])
                ow.append(rot[3])
                # tag_pose.pose.orientation.x = rot[0]
                # tag_pose.pose.orientation.y = rot[1]
                # tag_pose.pose.orientation.z = rot[2]
                # tag_pose.pose.orientation.w = rot[3]
            else:
                printErrorCode()
            # end = rospy.Time.now()
            # print "Detection time: ", end-start
    
        if len(x) != 0:
            # print "End for"
            tag_pose = PoseStamped()
            tag_pose.header.stamp = rospy.Time.now()
            tag_pose.pose.position.x = sum(x)/len(x)
            tag_pose.pose.position.y = sum(y)/len(y)
            tag_pose.pose.position.z = sum(z)/len(z)
            # print tag_pose.pose.position
            tag_pose.pose.orientation.x = sum(ox)/len(ox)
            tag_pose.pose.orientation.y = sum(oy)/len(oy)
            tag_pose.pose.orientation.z = sum(oz)/len(oz)
            tag_pose.pose.orientation.w = sum(ow)/len(ow)
            pub_poses.publish(tag_pose)

        rate.sleep()

    # with open(rospkg.RosPack().get_path('pozyx') + "/config/" + 'x.csv', 'wb') as xfile:
    #     wr = csv.writer(xfile, quoting=csv.QUOTE_ALL)
    #     wr.writerow(x)
    # with open(rospkg.RosPack().get_path('pozyx') + "/config/" + 'y.csv', 'wb') as yfile:
    #     wr = csv.writer(yfile, quoting=csv.QUOTE_ALL)
    #     wr.writerow(y)
    # with open(rospkg.RosPack().get_path('pozyx') + "/config/" + 'z.csv', 'wb') as zfile:
    #     wr = csv.writer(zfile, quoting=csv.QUOTE_ALL)
    #     wr.writerow(z)
    # print "End Reading"


if __name__ == '__main__':
    rospy.init_node('pozyx_tag_node',anonymous=False)

    pozyx_setup()
    try:
        pubPoses()
    except rospy.ROSInterruptException:
        pass
