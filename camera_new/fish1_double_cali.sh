#!/bin/bash
source /home/hjk/Desktop/zzw/catkin_new/devel/setup.sh
roscore & sleep 2	
### zzw_nodes_run
cd /home/hjk/Desktop/zzw/catkin_new/src/camera_new/scripts
python /home/hjk/Desktop/zzw/catkin_new/src/camera_new/scripts/t265_demo.py & sleep 2

roslaunch camera_new camera_detect.launch 
exit 0
