#include<iostream>
#include<opencv2/opencv.hpp>

#define COLOR_MAX (256)

#define FILE_NAME "../image2.jpg"

int main(int argc, char* argv[]){
    // 1、変数の宣言
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

    int threshold = 121;
    int count = 0;

    for(y = 0; y < src_img.rows; y++){
        for(x = 0; x < src_img.cols; x++){
            // 画素値の取得
            unsigned char s = src_img.at<unsigned char>(y, x);
            if(s < threshold){
                count++;
            }
        }
    }

    printf("image2 = %d\n", count);

    return (0);
}