#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME1 "../input_img1.png"
#define FILE_NAME2 "../input_img2.png"

int main(void){
    cv::Mat src_img1 = cv::imread(FILE_NAME1, cv::IMREAD_COLOR);
    cv::Mat src_img2 = cv::imread(FILE_NAME2, cv::IMREAD_COLOR);
    if (src_img1.empty() || src_img2.empty()) {
        fprintf(stderr, "ファイルひらけんかったわ\n");
        return (-1);
    }

    //二枚の画像をブレンドする
    cv::Mat dst_img = cv::Mat::zeros(src_img1.rows, src_img1.cols, CV_8UC3);
    for(int y = 0; y < src_img1.rows; y++){
        for(int x = 0; x < src_img1.cols; x++){
            dst_img.at<cv::Vec3b>(y, x) = src_img1.at<cv::Vec3b>(y, x) * 0.5 + src_img2.at<cv::Vec3b>(y, x) * 0.5;
        }
    }

    cv::imshow("src_img1", src_img1);
    cv::imshow("src_img2", src_img2);

    cv::imshow("dst_img", dst_img);
    cv::waitKey(0);

    return 0;
}