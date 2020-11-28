# aruco  

> 完成sdx师兄的二维码任务时的笔记   
  使用OpenCV ArUco库+usb相机/鱼眼相机进行二维码生成和识别，然后将二维码的位姿转换到uav的坐标系下并发布  

### 1.软件包介绍
* cat/cfg下是鱼眼相机的参数，可以通过cat/scripts/t265_get_instric.py获取(该python文件修改自cat/scripts/t265_demo.py   
[Reference](https://github.com/IntelRealSense/librealsense/blob/master/wrappers/python/examples/t265_stereo.py)   
[标定方法](https://github.com/GitZzw/sdx_aruco/blob/master/notes/T265%E9%B1%BC%E7%9C%BC%E5%9B%BE%E5%83%8F.md#3%E9%B1%BC%E7%9C%BC%E7%9B%B8%E6%9C%BA%E7%9A%84%E6%A0%87%E5%AE%9A)  
或者通过查看t265发布的/camera/fisheye1/camera_info  

* cat/msg为自定义的发布消息类型  
[Reference](https://github.com/GitZzw/sdx_aruco/blob/master/notes/ros%E8%87%AA%E5%AE%9A%E4%B9%89%E6%B6%88%E6%81%AF.md)   

* cat/src/t265SavePic.cpp利用cv::bridge将图像信息进行转换，并且保存图像   
[Reference](https://github.com/GitZzw/sdx_aruco/blob/master/notes/T265%E9%B1%BC%E7%9C%BC%E5%9B%BE%E5%83%8F.md#2%E5%8F%91%E5%B8%83%E7%9A%84ros%E9%B1%BC%E7%9C%BC%E5%9B%BE%E5%83%8Fsensor_msgsimage%E8%BD%AC%E6%8D%A2%E4%B8%BAcv%E7%9A%84image%E4%BD%BF%E7%94%A8cv_bridge)  

* cat/src/opencv_fisheye_cali_demo.cpp是官方鱼眼相机标定例程   
[Reference](https://github.com/GitZzw/sdx_aruco/blob/master/notes/T265%E9%B1%BC%E7%9C%BC%E5%9B%BE%E5%83%8F.md#3%E9%B1%BC%E7%9C%BC%E7%9B%B8%E6%9C%BA%E7%9A%84%E6%A0%87%E5%AE%9A)

* cat/src/fisheyeCali.cpp是实现的鱼眼相机标定程序  
[Reference](https://github.com/GitZzw/sdx_aruco/blob/master/notes/T265%E9%B1%BC%E7%9C%BC%E5%9B%BE%E5%83%8F.md#3%E9%B1%BC%E7%9C%BC%E7%9B%B8%E6%9C%BA%E7%9A%84%E6%A0%87%E5%AE%9A)

* cat/src/camera_generate_aruco.cpp生成二维码

* cat/src/camera_detect_aruco.cpp为二维码识别转换  
[Reference](https://github.com/GitZzw/sdx_aruco/blob/master/notes/OpenCV_ArUco%E4%BD%BF%E7%94%A8.md)


### 2.cat软件包使用鱼眼相机进行二维码获取
[Reference](https://github.com/GitZzw/sdx_aruco/blob/master/notes/T265%E9%B1%BC%E7%9C%BC%E5%9B%BE%E5%83%8F.md#1realsense-t265%E8%8E%B7%E5%8F%96%E9%B1%BC%E7%9C%BC%E7%9B%B8%E6%9C%BA%E6%95%B0%E6%8D%AE)   

> `fish2_once_cali.sh`为sh脚本运行即可  
  主要实现为`roslaunch realsense2_camera rs_t265.launch`运行realsense包,然后直接运行`roslaunch cat camera_detect.launch`获取image消息检测识别转换即可

### 3.camera_new软件包使用鱼眼相机进行二维码获取
> `fish1_double_cali.sh`为sh脚本运行即可
  主要实现为首先运行t265_demo.py将标定转换后的image发布，然后`roslaunch camera_new camera_detect.launch`接收消息检测识别转换即可，注意相当于两次标定，第二次标定为校正后的图像进行标定填入cfg中

### 4.camera_test软件包使用usb相机进行二维码获取
> `usb.sh`为sh脚本运行即可
  主要实现为运行`roslaunch camera_test camera_detect.launch `实时获取usb图像检测识别转换
  相机内参填入cfg中  

[Reference](https://github.com/GitZzw/sdx_aruco/blob/master/notes/matlab%E5%AE%8C%E6%88%90%E5%8D%95%E7%9B%AE%E7%9B%B8%E6%9C%BA%E6%A0%87%E5%AE%9A.md)    
