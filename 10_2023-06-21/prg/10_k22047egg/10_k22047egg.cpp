#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME "../challenge.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

//二値化しきい値
#define BIN_TH (200)

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

    //輪郭を取得
    std::vector< std::vector< cv::Point > > contours;
    cv::findContours(bin_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    //50画素以上の個数を求める
    int count = 0;
    for (int i = 0; i < contours.size(); i++) {
        if (cv::contourArea(contours[i]) >= 50) {
            count++;
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, bin_img);
    cv::waitKey();

    printf("count = %d\n", count);
    cv::imwrite("../10_k22047egg.jpg", bin_img);
        
    return 0;
}

