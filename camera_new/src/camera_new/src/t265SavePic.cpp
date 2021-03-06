#include <ros/ros.h>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "Image window";

int count = 0;
int i = 0;
class ImageConverter
{
ros::NodeHandle nh_;
image_transport::ImageTransport it_;
image_transport::Subscriber image_sub_;
image_transport::Publisher image_pub_;

public:
ImageConverter()
: it_(nh_)
{
// Subscrive to input video feed and publish output video feed
image_sub_ = it_.subscribe("/cali_image", 1,
&ImageConverter::imageCb, this);
image_pub_ = it_.advertise("/image_converter/output_video", 1);

cv::namedWindow(OPENCV_WINDOW);
}

~ImageConverter()
{
cv::destroyWindow(OPENCV_WINDOW);
}

void imageCb(const sensor_msgs::ImageConstPtr& msg)
{
cv_bridge::CvImagePtr cv_ptr;
try
{
cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
}
catch (cv_bridge::Exception& e)
{
ROS_ERROR("cv_bridge exception: %s", e.what());
return;
}


// Update GUI Window
cv::imshow(OPENCV_WINDOW, cv_ptr->image);

if(cv::waitKey(3)=='w'){
    cv::imwrite("./pic"+std::to_string(count)+".png",cv_ptr->image);
    count ++;
}

//cv::waitKey(3);
//cv::imwrite("./pic"+std::to_string(count)+".png",cv_ptr->image);
//count ++;

// Output modified video stream
image_pub_.publish(cv_ptr->toImageMsg());
}
};

int main(int argc, char** argv)
{
ros::init(argc, argv, "image_converter");
ImageConverter ic;
ros::spin();
return 0;
}
