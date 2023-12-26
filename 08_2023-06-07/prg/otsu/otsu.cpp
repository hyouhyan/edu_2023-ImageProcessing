/*二値化処理のプログラム*/
#include<iostream>
#include<opencv2/opencv.hpp>

#define HIGHVAL 255
#define TH 127

#define FILENAME "../canvas.jpg"

int main(void){
    //変数定義
    cv::Mat src_img, dst_img;
    //画像入力
    if((src_img = cv::imread(FILENAME, 0)).empty()){
        std::cout << "No image found." << std::endl;
        return -1;
    }

    cv::threshold(src_img, dst_img, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    //画像表示
    cv::imshow("src image", src_img);
    cv::imshow("dst image", dst_img);

    cv::waitKey(0);
    return 0;
}