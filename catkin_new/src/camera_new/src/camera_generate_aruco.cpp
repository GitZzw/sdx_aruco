/***
 * Used to detect aruco
 * generate aruco marker
 * 
 *
 * By Tonser
 *
 */
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/aruco.hpp>

using namespace cv;
using namespace std;
#define SIZE 1000

int main(int argc, char** argv) {
    Mat makerImage;
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_4X4_50);
    for (int i = 0; i < 20; ++i) {
        aruco::drawMarker(dictionary,i,SIZE,makerImage,1);
        string out = "../maker"+to_string(i)+".png";
        imwrite(out, makerImage);
    }
    imshow("marker", makerImage);
    waitKey(0);
}