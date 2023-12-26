#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../input_img1.png"

#define TH 50

int main(void){
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) {
        fprintf(stderr, "ファイルひらけんかったわ\n");
        return (-1);
    }

    cv::Mat gray_img;
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

    //2値化
    cv::Mat bin_img;
    cv::threshold(gray_img, bin_img, TH, 255, cv::THRESH_BINARY_INV);

    cv::Mat dst_img = src_img.clone();

    int peak = 0;
    for(int y = 0; y < bin_img.rows; y++){
        for(int x = 0; x < bin_img.cols; x++){
            if(bin_img.at<uchar>(y, x) == 255) peak++;
        }
        if(peak > 200){
            //横方向に直線を引く
            cv::line(dst_img, cv::Point(0, y), cv::Point(bin_img.cols, y), cv::Scalar(0, 0, 255), 2);
            //線の太さ分ずらす
            y += 2;
        }
        peak = 0;
    }

    for(int x = 0; x < bin_img.cols; x++){
        for(int y = 0; y < bin_img.rows; y++){
            if(bin_img.at<uchar>(y, x) == 255) peak++;
        }
        if(peak > 200){
            //縦方向に直線を引く
            cv::line(dst_img, cv::Point(x, 0), cv::Point(x, bin_img.rows), cv::Scalar(0, 0, 255), 2);
            //線の太さ分ずらす
            x += 2;
        }
        peak = 0;
    }

    cv::imshow("dst", dst_img);
    cv::waitKey(0);

    return 0;
}