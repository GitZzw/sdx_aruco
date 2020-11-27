#!/bin/bash
source /home/hjk/Desktop/zzw/cat/devel/setup.sh
roslaunch realsense2_camera rs_t265.launch & sleep 3	
### zzw_nodes_run
roslaunch cat camera_detect.launch 
exit 0
