/*二値化処理のプログラム*/
#include<iostream>
#include<opencv2/opencv.hpp>

#define HIGHVAL 255
#define TH 127

#define FILENAME "../canvas.jpg"

int main(void){
    //変数定義
    cv::Mat src_img, gray_img, bin_img;
    //画像入力
    if((gray_img = cv::imread(FILENAME, 1)).empty()){
        std::cout << "No image found." << std::endl;
        return -1;
    }

    //二値化
    cv::threshold(gray_img, bin_img, TH, HIGHVAL, cv::THRESH_BINARY);

    //画像表示
    cv::imshow("grayscale image", gray_img);
    cv::imshow("binary image", bin_img);

    cv::waitKey(0);
    return 0;
}