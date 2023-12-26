#include<iostream>
#include<opencv2/opencv.hpp>

#define COLOR_MAX (256)

#define FILE_NAME "../red_rectangle.jpg"

int main(int argc, char* argv[]){
    // 1、変数の宣言
    // アクセス用の変数
    int i, x, y;

    // ヒストグラム用の変数
    int hist[COLOR_MAX];

    // 2、画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    // 入力失敗の場合
    if(src_img.empty()){
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    // 3、ヒストグラム用配列の初期化
    for(i = 0; i < COLOR_MAX; i++){
        hist[i] = 0;
    }

    // 4、ヒストグラムの作成
    for(y = 0; y < src_img.rows; y++){
        for(x = 0; x < src_img.cols; x++){
            // 画素値の取得
            unsigned char s = src_img.at<unsigned char>(y, x);
            // 画素数の計算
            hist[(int)s]++;
        }
    }

    // 5、出力(Numbers or Excel用に印字)
    for(i = 0; i < COLOR_MAX; i++){
        printf("%d %d\n", i, hist[i]);
    }
}