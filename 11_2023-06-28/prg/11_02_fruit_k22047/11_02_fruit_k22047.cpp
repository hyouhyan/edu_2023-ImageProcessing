#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../fruit_image.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define H_MIN 35
#define H_MAX 40

#define S_MIN 120
#define S_MAX 255

#define V_MIN 0
#define V_MAX 245

int main(void){
    cv::Mat src_img = cv::imread(FILE_NAME);
    if(src_img.empty()){
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    //hsvへ変換
    cv::Mat hsv_img;
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    cv::Mat bin_img;
    cv::inRange(hsv_img, cv::Scalar(H_MIN, S_MIN, V_MIN), cv::Scalar(H_MAX, S_MAX, V_MAX), bin_img);

    //輪郭を取得
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(bin_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    int max_contour_num = 0, max_contour = 0;
    for (int i = 0; i < contours.size(); i++) {
        if (cv::contourArea(contours[i]) > max_contour_num) {
            max_contour_num = cv::contourArea(contours[i]);
            max_contour = i;
        }
    }

    cv::Mat dst_img = src_img.clone();
    cv::drawContours(dst_img, contours, max_contour, CV_RGB(0, 255, 0), -1);

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow("dst_img", dst_img);
    cv::waitKey();

    return 0;
}