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

    //2. グレースケール画像に変換
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    //3. エッジ検出（cannyオペレータ)
    cv::Canny(gray_img, dst_img, TH1, TH2);

    //4. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_GRAYSCALE, gray_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}
