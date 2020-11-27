## OpenCV ArUco二维码生成和识别 
[官方](https://docs.opencv.org/3.1.0/d9/d6a/group__aruco.html#gafdd609e5c251dc7b8197323657a874c3)
[参考](https://blog.csdn.net/u010260681/article/details/77089657)  

本质pnp求解，rvec和tvec分别返回是相机相对于二维码中心的旋转矩阵和平移向量

> 其中cv::aruco::DetectorParameters::DetectorParameters参数可以修改阈值化、滤波、角落细化等检测参数



## 获取到相机相对于二维码的位姿之后，参考李jy师兄的代码，并进行ros pose发布(四元数)，进行坐标系转换，转换为uav东北天坐标系
其中用到了仿射变换(埋坑)

#### 注意:以下代码中matx44d矩阵初始化方法不对，改写为`cv::Matx44d world_to_cam_mtx;world_to_cam_mtx<<0, 0, 1, 0, -1, 0, 0, 0, 0, -1, 0, 0.611, 0, 0, 0, 1;`才能成功初始化
```c++
cv::solvePnP(objectPts, ImagePts, cameraMatrix, distcoeffs, rvec, tvec);                           
cv::Affine3d cam_to_drone = cv::Affine3d(rvec, tvec);
cv::Matx44d world_to_cam_mtx( 0, 0, 1, 0, -1, 0, 0, 0, 0, -1, 0, 0.611, 0, 0, 0, 1); 
cv::Affine3d world_to_cam(world_to_cam_mtx);
cv::Affine3d world_to_drone = cam_to_drone.concatenate(world_to_cam);
tf::Quaternion q;
double theta = sqrt(world_to_drone.rvec()[0] * world_to_drone.rvec()[0] + world_to_drone.rvec()[1] * world_to_drone.rvec()[1] + world_to_drone.rvec()[2] * world_to_drone.rvec()[2]);
tf::Vector3 axis = tf::Vector3(world_to_drone.rvec()[0]/theta,  world_to_drone.rvec()[1]/theta, world_to_drone.rvec()[2]/theta);
q.setRotation(axis,theta);
// tf::Transform transform;                
// transform.setOrigin(tf::Vector3(pose_raw.translation()[0],pose_raw.translation()[1],pose_raw.translation()[2]));                
// transform.setRotation(q);
// br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "drone"));
geometry_msgs::PoseStamped world_to_drone_posestamped;
world_to_drone_posestamped.header.stamp = ros::Time::now();
world_to_drone_posestamped.pose.position.x = world_to_drone.translation()[0] / 1000.0;
world_to_drone_posestamped.pose.position.y = world_to_drone.translation()[1] / 1000.0; 
world_to_drone_posestamped.pose.position.z = world_to_drone.translation()[2] / 1000.0;
world_to_drone_posestamped.pose.orientation.w = q.w();
world_to_drone_posestamped.pose.orientation.x = q.x();
world_to_drone_posestamped.pose.orientation.y = q.y();
world_to_drone_posestamped.pose.orientation.z = q.z();
pose_pub.publish(world_to_drone_posestamped);
```



