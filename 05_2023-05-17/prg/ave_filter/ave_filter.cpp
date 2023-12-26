#include<iostream>
#include<opencv2/opencv.hpp>

#define FILE_NAME "../apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT1 "output1"
#define WINDOW_NAME_OUTPUT2 "output2"

int main(int argc, char const *argv[]){
    // 画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if(src_img.empty()){
        fprintf(stderr, "Failed to open file.\n");
        return -1;
    }

    // 出力画像の宣言
    cv::Mat dst_img1, dst_img2;

    // フィルタの宣言と設計(入力と正規化)
    double filter_3x3[] = {
        1./9., 1./9., 1./9.,
        1./9., 1./9., 1./9.,
        1./9., 1./9., 1./9.
    };
    double filter_5x5[] = {
        1./25., 1./25., 1./25., 1./25., 1./25.,
        1./25., 1./25., 1./25., 1./25., 1./25.,
        1./25., 1./25., 1./25., 1./25., 1./25.,
        1./25., 1./25., 1./25., 1./25., 1./25.,
        1./25., 1./25., 1./25., 1./25., 1./25.
    };

    // 3x3の処理
    cv::Mat kernel1 = cv::Mat(3, 3, CV_64FC1, filter_3x3);
    cv::normalize(kernel1, kernel1, 1.0, 0.0, cv::NORM_L1);
    cv::filter2D(src_img, dst_img1, -1, kernel1);

    // 5x5の処理
    cv::Mat kernel2 = cv::Mat(5, 5, CV_64FC1, filter_5x5);
    cv::normalize(kernel2, kernel2, 1.0, 0.0, cv::NORM_L1);
    cv::filter2D(src_img, dst_img2, -1, kernel2);

    // 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT1, dst_img1);
    cv::imshow(WINDOW_NAME_OUTPUT2, dst_img2);
    cv::waitKey();
    
    return 0;
}
