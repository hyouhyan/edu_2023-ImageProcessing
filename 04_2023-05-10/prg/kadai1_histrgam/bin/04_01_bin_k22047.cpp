#include<iostream>
#include<opencv2/opencv.hpp>

#define COLOR_MAX (256)

#define FILE_NAME "../image1.jpg"

int main(int argc, char* argv[]){
    // 変数の宣言
    // アクセス用の変数
    int i, x, y;

    // ヒストグラム用の変数
    int hist[COLOR_MAX];

    // 画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    // 入力失敗の場合
    if(src_img.empty()){
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    int threshold = 0;
    printf("2値化する際の閾値を入力してください(0～255) ");scanf("%d", &threshold);

    // メモリ確保
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    for(y = 0; y < src_img.rows; y++){
        for(x = 0; x < src_img.cols; x++){
            // 画素値の取得
            unsigned char s = src_img.at<unsigned char>(y, x);
            if(s > threshold){
                dst_img.at<unsigned char>(y, x) = 0;
            }else{
                dst_img.at<unsigned char>(y, x) = 255;
            }
        }
    }

    // 画像の表示
    cv::imshow("src", src_img);
    cv::imshow("dst", dst_img);

    // キー入力待機
    cv::waitKey();

    return 0;
}