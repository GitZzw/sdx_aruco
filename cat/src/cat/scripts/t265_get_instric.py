
#!/usr/bin/python
# -*- coding: utf-8 -*-
## License: Apache 2.0. See LICENSE file in root directory.
## Copyright(c) 2019 Intel Corporation. All Rights Reserved.
# Python 2/3 compatibility
from __future__ import print_function

"""
This example shows how to use T265 intrinsics and extrinsics in OpenCV to
asynchronously compute depth maps from T265 fisheye images on the host.
T265 is not a depth camera and the quality of passive-only depth options will
always be limited compared to (e.g.) the D4XX series cameras. However, T265 does
have two global shutter cameras in a stereo configuration, and in this example
we show how to set up OpenCV to undistort the images and compute stereo depth
from them.
Getting started with python3, OpenCV and T265 on Ubuntu 16.04:
First, set up the virtual enviroment:
$ apt-get install python3-venv  # install python3 built in venv support
$ python3 -m venv py3librs      # create a virtual environment in pylibrs
$ source py3librs/bin/activate  # activate the venv, do this from every terminal
$ pip install opencv-python     # install opencv 4.1 in the venv
$ pip install pyrealsense2      # install librealsense python bindings
Then, for every new terminal:
$ source py3librs/bin/activate  # Activate the virtual environment
$ python3 t265_stereo.py        # Run the example
"""

# First import the library
import pyrealsense2 as rs

# Import OpenCV and numpy
import cv2
import numpy as np
from math import tan, pi

"""
In this section, we will set up the functions that will translate the camera
intrinsics and extrinsics from librealsense into parameters that can be used
with OpenCV.
The T265 uses very wide angle lenses, so the distortion is modeled using a four
parameter distortion model known as Kanalla-Brandt. OpenCV supports this
distortion model in their "fisheye" module, more details can be found here:
https://docs.opencv.org/3.4/db/d58/group__calib3d__fisheye.html
"""

"""
Returns R, T transform from src to dst
"""
def get_extrinsics(src, dst):
    extrinsics = src.get_extrinsics_to(dst)
    R = np.reshape(extrinsics.rotation, [3,3]).T
    T = np.array(extrinsics.translation)
    return (R, T)

"""
Returns a camera matrix K from librealsense intrinsics
"""
def camera_matrix(intrinsics):
    return np.array([[intrinsics.fx,             0, intrinsics.ppx],
                     [            0, intrinsics.fy, intrinsics.ppy],
                     [            0,             0,              1]])

"""
Returns the fisheye distortion from librealsense intrinsics
"""
def fisheye_distortion(intrinsics):
    return np.array(intrinsics.coeffs[:4])

# Set up a mutex to share data between threads
from threading import Lock
frame_mutex = Lock()
frame_data = {"left"  : None,
              "right" : None,
              "timestamp_ms" : None
              }

"""
This callback is called on a separate thread, so we must use a mutex
to ensure that data is synchronized properly. We should also be
careful not to do much work on this thread to avoid data backing up in the
callback queue.
"""
def callback(frame):
    global frame_data
    if frame.is_frameset():
        frameset = frame.as_frameset()
        f1 = frameset.get_fisheye_frame(1).as_video_frame()
        f2 = frameset.get_fisheye_frame(2).as_video_frame()
        left_data = np.asanyarray(f1.get_data())
        right_data = np.asanyarray(f2.get_data())
        ts = frameset.get_timestamp()
        frame_mutex.acquire()
        frame_data["left"] = left_data
        frame_data["right"] = right_data
        frame_data["timestamp_ms"] = ts
        frame_mutex.release()

# Declare RealSense pipeline, encapsulating the actual device and sensors
pipe = rs.pipeline()

# Build config object and stream everything
cfg = rs.config()

# Start streaming with our callback
pipe.start(cfg, callback)

try:
    # Set up an OpenCV window to visualize the results
    WINDOW_TITLE = 'Realsense'
    cv2.namedWindow(WINDOW_TITLE, cv2.WINDOW_NORMAL)

    # Configure the OpenCV stereo algorithm. See
    # https://docs.opencv.org/3.4/d2/d85/classcv_1_1StereoSGBM.html for a
    # description of the parameters
    window_size = 5
    min_disp = 0
    # must be divisible by 16
    num_disp = 112 - min_disp
    max_disp = min_disp + num_disp
    stereo = cv2.StereoSGBM_create(minDisparity = min_disp,
                                   numDisparities = num_disp,
                                   blockSize = 16,
                                   P1 = 8*3*window_size**2,
                                   P2 = 32*3*window_size**2,
                                   disp12MaxDiff = 1,
                                   uniquenessRatio = 10,
                                   speckleWindowSize = 100,
                                   speckleRange = 32)

    # Retreive the stream and intrinsic properties for both cameras
    profiles = pipe.get_active_profile()
    streams = {"left"  : profiles.get_stream(rs.stream.fisheye, 1).as_video_stream_profile(),
               "right" : profiles.get_stream(rs.stream.fisheye, 2).as_video_stream_profile()}
    intrinsics = {"left"  : streams["left"].get_intrinsics(),
                  "right" : streams["right"].get_intrinsics()}
    pics = {"left"  : streams["left"].get_intrinsics(),
                  "right" : streams["right"].get_intrinsics()}

    # Print information about both cameras


    # Translate the intrinsics from librealsense into OpenCV
    K_left  = camera_matrix(intrinsics["left"])
    D_left  = fisheye_distortion(intrinsics["left"])
    K_right = camera_matrix(intrinsics["right"])
    D_right = fisheye_distortion(intrinsics["right"])
    print("Left camera:",  K_left)
    print("Right camera:", D_left)
finally:
    print('no')


