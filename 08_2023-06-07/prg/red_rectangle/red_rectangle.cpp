/*二値化処理のプログラム*/
#include<iostream>
#include<opencv2/opencv.hpp>

#define HIGHVAL 255
#define LOWVAL 0
#define TH 100
#define FILENAME "../red_rectangle.jpg"

int main(void){
    //変数定義
    cv::Mat src_img, gray_img, bin_img;
    //画像入力
    if((src_img = cv::imread(FILENAME, 1)).empty()){
        std::cout << "No image found." << std::endl;
        return -1;
    }

    // 輝度画像への変換
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

    //二値画像の生成
    bin_img.create(gray_img.size(), gray_img.type());
    //二値画像への変換
    for(int y = 0; y < gray_img.rows; y++){
        for(int x = 0; x < gray_img.cols; x++){
            if(gray_img.at<unsigned char>(y, x) > TH){
                bin_img.at<unsigned char>(y, x) = HIGHVAL;
            }else{
                bin_img.at<unsigned char>(y, x) = LOWVAL;
            }
        }
    }

    //画像表示
    cv::imshow("input image", src_img);
    cv::imshow("grayscale image", gray_img);
    cv::imshow("binary image", bin_img);

    cv::waitKey(0);
    return 0;
}