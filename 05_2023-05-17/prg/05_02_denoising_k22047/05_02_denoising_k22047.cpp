#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../dot_gray_kanji.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[]) {
    // 画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty()) {
        fprintf(stderr, "Failed to open file.\n");
        return -1;
    }

    // 出力画像の宣言
    cv::Mat dst_img;

    // 平均化
    int kernelSize = 10;
    cv::blur(src_img, dst_img, cv::Size(kernelSize, kernelSize));

    // 2値化
    cv::Mat bin_img = cv::Mat(src_img.size(), CV_8UC1);
    int threshold = 128;
    for(int y = 0; y < dst_img.rows; y++){
        for(int x = 0; x < dst_img.cols; x++){
            // 画素値の取得
            unsigned char s = dst_img.at<unsigned char>(y, x);
            if(s < threshold){
                bin_img.at<unsigned char>(y, x) = 0;
            }else{
                bin_img.at<unsigned char>(y, x) = 255;
            }
        }
    }

    // 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow("output2", dst_img);
    cv::imshow(WINDOW_NAME_OUTPUT, bin_img);
    cv::waitKey();

    return 0;
}
