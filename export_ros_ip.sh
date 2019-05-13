#!/usr/bin/env bash
echo "Setting ROS_IP..."
if [ $# -gt 0 ]; then
	export ROS_IP=$1
    echo "ROS_IP set to $ROS_IP"
else
    export ROS_IP=$(hostname -I)
	echo "ROS_IP set to $ROS_IP"
fi
