/***
 * Used to display FPS in frame
 * tested on usb cam
 *
 * results: about 100+ fps
 *
 * Tonser
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    VideoCapture capture(0);
    if (!capture.isOpened()) {
        printf("[%s][%d]could not load video data...\n", __FUNCTION__, __LINE__);
        return -1;
    }

    Mat frame;
    int last_time = 0;
    double t;
    double fps;
    char disp_fps[10];
    while (true) {
        t = (double)cvGetTickCount();
        if (waitKey(5) == 27) {
            break;
        }
        if (capture.isOpened())
        {
            capture >> frame;
            t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
            fps = 1.0 / t;


            sprintf(disp_fps, "%.2f", fps);      // 帧率保留两位小数
            string fpsString("FPS:");
            fpsString += disp_fps;                    // 在"FPS:"后加入帧率数值字符串
            // 将帧率信息写在输出帧上
            putText(frame, // 图像矩阵
                    fpsString,                  // string型文字内容
                    cv::Point(5, 40),           // 文字坐标，以左下角为原点
                    cv::FONT_HERSHEY_COMPLEX,   // 字体类型
                    1.0, // 字体大小
                    cv::Scalar(255, 0, 0));       // 字体颜色


            imshow("Camera FPS", frame);
        }

    }
    waitKey(0);
    return 0;
}