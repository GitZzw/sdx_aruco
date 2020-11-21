/***
 * Used to detect aruco
 * generate aruco marker
 * cout mean detect time
 *
 * By Tonser
 *
 */
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <ros/ros.h>
#include <csignal>
#include <tf/transform_broadcaster.h>

using namespace cv;
using namespace std;
#define SIZE 1000

class arucoDetect {
public:
    static arucoDetect *GetInstance();

    static void shutdown_handler(int sig);

    void loadStart(ros::NodeHandle &nh);

    cv::VideoCapture inputVideo;
    bool display = false;
private:
    arucoDetect() = default;

    static arucoDetect *instance;

    void openCamera(int index);

    Ptr<aruco::Dictionary> dictionary;

    cv::Mat cameraMatrix;
    cv::Mat distCoeffs; //摄像机的5个畸变系数：k1,k2,p1,p2,k3
    cv::Mat imageCopy;
    cv::Mat image;

    double totalTime = 0;
    int totalIterations = 0;
    int index = 0;

    void loadCameraParams(const vector<float> &cameraMatrix, const vector<float> &distCoerffs);

    void loadRosParam(ros::NodeHandle &nh);

    bool systemOk();

    void startDetect();

    void setDisplay(bool value);

    void loadDict(int index);

    static void watchSignal();

};

arucoDetect *arucoDetect::instance = nullptr;

int main(int argc, char **argv) {
    ros::init(argc, argv, "aruco_detect");
    ros::NodeHandle nh("aruco_detect");
    arucoDetect *detect = arucoDetect::GetInstance();
    detect->loadStart(nh);
}

/***
 * init camera
 * @param index: camera index
 */
void arucoDetect::loadStart(ros::NodeHandle &nh) {
    instance = this;
    loadRosParam(nh);
    openCamera(index);
    display = false;
    cameraMatrix = (Mat_<float>(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0);
    distCoeffs = (Mat_<float>(1, 5) << 0, 0, 0, 0, 0);
    watchSignal();
    startDetect();
}

void
arucoDetect::openCamera(int index) {
    inputVideo = cv::VideoCapture(index);
    inputVideo.open(index);
}

void
arucoDetect::loadCameraParams(const vector<float> &cameraMatrix,
                              const vector<float> &distCoerffs) {
    for (int j = 0; j < 9; ++j) {
        this->cameraMatrix.at<float>(j) = cameraMatrix[j];
    }
    ROS_INFO_STREAM("\n cameraMatrix:\n" << this->cameraMatrix);
    for (int k = 0; k < 5; ++k) {
        this->distCoeffs.at<float>(k) = distCoerffs[k];
    }
    ROS_INFO_STREAM("distCoeffs :" << this->distCoeffs);
}

void
arucoDetect::setDisplay(bool value) {
    display = value;
}


void
arucoDetect::loadDict(int index) {
    switch (index) {
        case 4:
            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
            break;
        case 5:
            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_50);
            break;
        case 6:
            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);
            break;
        default:
            dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
            break;
    }
}

template<typename T>
T readParam(ros::NodeHandle &n, std::string name) {
    T ans;
    const string& node_name = ros::this_node::getName();
    name = node_name + "/" + name;
    if (!n.getParam(name, ans)) {
        ROS_ERROR_STREAM("Failed to load " << name);
        n.shutdown();
    }
    return ans;
}

void
arucoDetect::loadRosParam(ros::NodeHandle &nh) {
    vector<float> rosParamsCameraMatrix(9);
    vector<float> rosParamsDistCoeffs(5);
    int dict_index = 4;
    bool disp = false;

    rosParamsCameraMatrix = readParam<vector<float>>(nh, "cameraMatrix");
    rosParamsDistCoeffs = readParam<vector<float>>(nh, "cameraDistCoeffs");
    dict_index = readParam<int>(nh, "dict");
    index = readParam<int>(nh, "index");
    disp = readParam<bool>(nh, "display");

    setDisplay(disp);
    loadDict(dict_index);
    loadCameraParams(rosParamsCameraMatrix, rosParamsDistCoeffs);
}

bool
arucoDetect::systemOk() {
    return inputVideo.isOpened();
}

void
arucoDetect::shutdown_handler(int sig) {
    instance->inputVideo.release();
}

void
arucoDetect::watchSignal() {
    signal(SIGINT, arucoDetect::shutdown_handler);
    signal(SIGTERM, arucoDetect::shutdown_handler);
    signal(SIGKILL, arucoDetect::shutdown_handler);
    signal(SIGQUIT, arucoDetect::shutdown_handler);
}

void
arucoDetect::startDetect() {
    tf::TransformBroadcaster br;
    while (systemOk()) {
        if (waitKey(5) == 27) break;
        auto tick = (double) getTickCount();
        inputVideo >> image;
        image.copyTo(imageCopy);
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        vector<Vec3d> rvecs, tvecs;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);
        // if at least one marker detected
        if (!ids.empty()) {
            cv::aruco::estimatePoseSingleMarkers(corners, 0.045, cameraMatrix, distCoeffs, rvecs,
                                                 tvecs); // draw axis for each marker
            double currentTime = ((double) getTickCount() - tick) / getTickFrequency();
            totalTime += currentTime;
            totalIterations++;
            // cout every 3secs
            ROS_INFO_STREAM_THROTTLE(3, "Detection Time = " << currentTime * 1000 << " ms " << "(Mean = "
                                                            << 1000 * totalTime / double(totalIterations) << " ms)");
            for (int j = 0; j < ids.size(); ++j) {
                std::string cameraCoordinateName = "own_camera";
                std::string arucoCoordinateName = "aruco_id_" + to_string(ids[j]);
                tf::Transform trans;
                trans.setOrigin(tf::Vector3(tvecs[j][0], tvecs[j][1], tvecs[j][2]));
                tf::Quaternion q;
                q.setRPY(rvecs[j][0], rvecs[j][1], rvecs[j][2]);
                trans.setRotation(q);
                br.sendTransform(
                        tf::StampedTransform(trans, ros::Time::now(), arucoCoordinateName, cameraCoordinateName));
            }
            if (display) {
                cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
                double meanFps = double(totalIterations) / totalTime;
                for (int i = 0; i < ids.size(); i++)
                    cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
                putText(imageCopy, // 图像矩阵
                        to_string(meanFps),                  // string型文字内容
                        cv::Point(5, 40),           // 文字坐标，以左下角为原点
                        cv::FONT_HERSHEY_COMPLEX,   // 字体类型
                        0.5, // 字体大小
                        cv::Scalar(255, 0, 0));
            }
        } else {
            if (display) {
                putText(imageCopy, // 图像矩阵
                        "Not detected Aruco",                  // string型文字内容
                        cv::Point(5, 40),           // 文字坐标，以左下角为原点
                        cv::FONT_HERSHEY_COMPLEX,   // 字体类型
                        1.0, // 字体大小
                        cv::Scalar(255, 0, 0));
            }
        }
        if (display) cv::imshow("out", imageCopy);
    }
    if (!systemOk())ROS_INFO("Bad camera or ending program");
}

arucoDetect *arucoDetect::GetInstance() {
    if (instance == nullptr) instance = new arucoDetect();
    return instance;
}


