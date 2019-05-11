#!/usr/bin/env python
import rospy
import math

from sensor_msgs.msg import Joy
#from duckietown_msgs.msg import Twist2DStamped, BoolStamped

class JoyMapper(object):
    def __init__(self):
        self.node_name = rospy.get_name()
        rospy.loginfo("Initializing [%s]" %self.node_name)

        #Publishers
        #self.pub_car_cmd = rospy.Publisher("~car_cmd", Twist2DStamped, queue_size=1)
        
        #Subscribers
        self.sub_joy = rospy.Subscriber("/joy", Joy, self.cbJoy, queue_size=1)

    def cbJoy(self, msg):
        # Button List index of joy.buttons array:
        # 0: A 
        # 1: B 
        # 2: X 
        # 3: Y 
        # 4: Left Back 
        # 5: Right Back
        # 6: Back
        # 7: Start
        # 8: Logitek 
        # 9: Left joystick
        # 10: Right joystick
        print "joy cb"
        if (msg.buttons[0] == 1):
            print "A"
        elif (msg.buttons[1] == 1):
            print "B"
        elif (msg.buttons[2] == 1):
            print "X"
        elif (msg.buttons[3] == 1):
            print "Y"


if __name__ == "__main__":
    rospy.init_node("joy_mapper", anonymous=False)
    joy_mapper = JoyMapper()
    rospy.spin()