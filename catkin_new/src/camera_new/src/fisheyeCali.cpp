#include "stdio.h"
#include <iostream>
#include <fstream>

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
    vector<string> files;
    for(auto count =2;count<=25;count++){
        files.push_back("/home/hjk/Desktop/zzw/catkin_new/pic/pic"+to_string(count)+".png");
    }
    const int board_w = 11;
    const int board_h = 8;
    const int NPoints = board_w * board_h;//棋盘格内角点总数
    const int boardSize = 20; //mm
    Mat image,grayimage;
    Size ChessBoardSize = cv::Size(board_w, board_h);
    vector<Point2f> tempcorners;

    int flag = 0;
    flag |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
    //flag |= cv::fisheye::CALIB_CHECK_COND;
    flag |= cv::fisheye::CALIB_FIX_SKEW;
    //flag |= cv::fisheye::CALIB_USE_INTRINSIC_GUESS;

    vector<Point3f> object;
    for (int j = 0; j < NPoints; j++)
    {
        object.push_back(Point3f((j % board_w) * boardSize, (j / board_w) * boardSize, 0));
    }

    cv::Matx33d intrinsics;//z:相机内参
    cv::Vec4d distortion_coeff;//z:相机畸变系数

    vector<vector<Point3f> > objectv;
    vector<vector<Point2f> > imagev;

    Size corrected_size(1280, 720);
    Mat mapx, mapy;
    Mat corrected;

    ofstream intrinsicfile("intrinsics_front1103.txt");
    ofstream disfile("dis_coeff_front1103.txt");
    int num = 0;
    bool bCalib = false;
    while (num < files.size())
    {
        image = imread(files[num]);

        if (image.empty())
            break;
        imshow("corner_image", image);
        waitKey(10);
        cvtColor(image, grayimage, CV_BGR2GRAY);
        IplImage tempgray = grayimage;
        bool findchessboard = cvCheckChessboard(&tempgray, ChessBoardSize);

        if (findchessboard)
        {
            bool find_corners_result = findChessboardCorners(grayimage, ChessBoardSize, tempcorners, 3);
            if (find_corners_result)
            {
                cornerSubPix(grayimage, tempcorners, cvSize(5, 5), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
                drawChessboardCorners(image, ChessBoardSize, tempcorners, find_corners_result);
                imshow("corner_image", image);
                cvWaitKey(100);

                objectv.push_back(object);
                imagev.push_back(tempcorners);
                cout << "capture " << num << " pictures" << endl;
            }
        }
        tempcorners.clear();
        num++;
    }

    cv::fisheye::calibrate(objectv, imagev, cv::Size(image.cols,image.rows), intrinsics, distortion_coeff, cv::noArray(), cv::noArray(), flag, cv::TermCriteria(3, 20, 1e-6));
    fisheye::initUndistortRectifyMap(intrinsics, distortion_coeff, cv::Matx33d::eye(), intrinsics, corrected_size, CV_16SC2, mapx, mapy);

    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            intrinsicfile<<intrinsics(i,j)<<"\t";
        }
        intrinsicfile<<endl;
    }
    for(int i=0; i<4; ++i)
    {
        disfile<<distortion_coeff(i)<<"\t";
    }
    intrinsicfile.close();
    disfile.close();

    num = 0;
    while (num < files.size())
    {
        image = imread(files[num++]);

        if (image.empty())
            break;
        remap(image, corrected, mapx, mapy, INTER_LINEAR, BORDER_TRANSPARENT);

        imshow("corner_image", image);
        imshow("corrected", corrected);
        cvWaitKey(200);
    }

    cv::destroyWindow("corner_image");
    cv::destroyWindow("corrected");

    image.release();
    grayimage.release();
    corrected.release();
    mapx.release();
    mapy.release();

    return 0;
}

