#!/usr/bin/env python
import rospy
import math

from sensor_msgs.msg import Joy
from duckietown_msgs.msg import Twist2DStamped, BoolStamped

class JoyMapper(object):
    def __init__(self):
        
        self.node_name = rospy.get_name()
        self.joy = None
        rospy.loginfo("Initializing [%s]" %self.node_name)

        #Subscribers
        self.sub_joy = rospy.Subscriber("/joy", Joy, self.cbJoy, queue_size=1)
        #Publishers
        self.pub_car_cmd = rospy.Publisher("/car_cmd", Twist2DStamped, queue_size=1)
        #params
        self.v_gain = 5
        self.omega_gain = 5


    def cbJoy(self, msg):
        print "joy cb"
        self.joy = msg
        self.processButtons();
        self.processAxes();

    def processAxes(self):
        # Axes def in X-mode
        # 0: left horizontal
        # 1: left vertical
        # 2: left T
        # 3: right horizontal
        # 4: right vertical
        # 5: right T
        # 6: left/right
        # 7: up/down
        print "axis[0] = ", self.joy.axes[0]
        print "axis[1] = ", self.joy.axes[1]
        print "axis[2] = ", self.joy.axes[2]
        print "axis[3] = ", self.joy.axes[3]
        print "axis[4] = ", self.joy.axes[4]
        print "axis[5] = ", self.joy.axes[5]
        
        car_cmd_msg = Twist2DStamped()
        car_cmd_msg.header.stamp = self.joy.header.stamp
        car_cmd_msg.v = self.joy.axes[1] * self.v_gain
    
        
        car_cmd_msg.omega = self.joy.axes[3] * self.omega_gain
        self.pub_car_cmd.publish(car_cmd_msg)

    def processButtons(self):
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
        if (self.joy.buttons[0] == 1):
            print "A"
        elif (self.joy.buttons[1] == 1):
            print "B"
        elif (self.joy.buttons[2] == 1):
            print "X"
        elif (self.joy.buttons[3] == 1):
            print "Y"


if __name__ == "__main__":
    rospy.init_node("joy_mapper", anonymous=False)
    joy_mapper = JoyMapper()
    rospy.spin()