#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../handinwhite.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(void){
    cv::Mat src_img = cv::imread(FILE_NAME);
    if(src_img.empty()){
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    //hsvへ変換
    cv::Mat hsv_img;
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    cv::Mat dst_img = cv::Mat::zeros(src_img.size(), src_img.type());
    cv::Vec3b p;

    for(int y = 0; y < hsv_img.rows; y++){
        for(int x = 0; x < hsv_img.cols; x++){
            p = hsv_img.at<cv::Vec3b>(y, x);
            if(0 <= p[0] && p[0] <= 17 || 170 <= p[0] && p[0] <= 180) {
                if(40 <= p[1]){
                    if(70 <= p[2]) {
                        dst_img.at<cv::Vec3b>(y, x) = src_img.at<cv::Vec3b>(y, x);
                    }
                }
            }
        }
    }


    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
