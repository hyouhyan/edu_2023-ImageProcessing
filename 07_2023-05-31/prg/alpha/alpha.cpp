#include<iostream>
#include<opencv2/opencv.hpp>

#define FILE_NAME1 "../input1.jpg"
#define FILE_NAME2 "../input2.jpg"

// 透明度
#define ALPHA 0.3

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[]){
    // 画像をグレースケールで入力
    cv::Mat src_img1 = cv::imread(FILE_NAME1, 0);
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0);
    if(src_img2.empty() || src_img1.empty()){
        fprintf(stderr, "Failed to open file.\n");
        return -1;
    }

    // 出力画像の宣言
    cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC1);
    int x, y;

    for(y = 0; y < src_img1.rows; y++){
        for(x = 0; x < src_img1.cols; x++){
            double s1 = (double)src_img1.at<unsigned char>(y, x);
            double s2 = (double)src_img2.at<unsigned char>(y, x);

            int s_result = ALPHA * s1 + (1.0 - ALPHA) * s2;
            result_img.at<unsigned char>(y, x) = (unsigned char)s_result;
        }
    }

    // 出力
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey();
    
    return 0;
}
