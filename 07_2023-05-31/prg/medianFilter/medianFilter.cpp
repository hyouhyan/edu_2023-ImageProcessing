#include<iostream>
#include<opencv2/opencv.hpp>

#define FILE_NAME "../apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define FILTER_SIZE 11 // フィルタサイズ(3以上の奇数)

int main(int argc, char const *argv[]){
    // 画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if(src_img.empty()){
        fprintf(stderr, "Failed to open file.\n");
        return -1;
    }

    // 出力画像の宣言
    cv::Mat median_img;

    // メディアンフィルタ
    cv:medianBlur(src_img, median_img, FILTER_SIZE);

    // 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, median_img);
    cv::waitKey();
    
    return 0;
}
