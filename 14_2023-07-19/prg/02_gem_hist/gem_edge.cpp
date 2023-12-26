#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../gem1.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_GRAYSCALE "grayscale"
#define WINDOW_NAME_OUTPUT "output"

#define TH1 100
#define TH2 200

int main(int argc, const char * argv[]) {
    //画像変数の宣言
    cv::Mat src_img, gray_img, dst_img;
    
    //1. 入力画像をカラーで入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    // ヒストグラムを作成
    std::vector<int> histgram(256, 0);
    for (int y = 0; y < src_img.rows; y++) {
        for (int x = 0; x < src_img.cols; x++) {
            cv::Vec3b bgr = src_img.at<cv::Vec3b>(y, x);
            int gray = (int)(bgr[0] * 0.114 + bgr[1] * 0.587 + bgr[2] * 0.299);
            histgram[gray]++;
        }
    }

    //csv形式で出力
    for(int i = 0; i < 256; i++){
        std::cout << i << "," << histgram[i] << std::endl;
    }

    
    return 0;
}
