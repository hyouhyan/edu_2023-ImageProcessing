#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME "../a_img3.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

//二値化しきい値
#define BIN_TH (100)

int main(int argc, const char * argv[]) {
    //グレースケールで読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if(src_img.empty()){
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    //二値化
    cv::Mat bin_img;
    cv::threshold(src_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

    cv::Mat dst_img = bin_img.clone();
    cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 7);
    cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 7);
    cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 10);
    cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 10);

    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}

