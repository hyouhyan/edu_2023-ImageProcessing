#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../apple_grayscale.jpg"
// ウィンドウ名

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char *argv[]) {
    // 1. 画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty()) { // 入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    // 2. 画像変数の宣言
    cv::Mat tmp_img; // 一時的な画像
    cv::Mat dst_img; // 結果画像

    // 3. ソーベルフィルタ (結果はfloat)
    cv::Sobel(src_img, tmp_img, CV_32F, 1, 0); // 横方向

    // 4. 適切な出力画像に変換
    cv::convertScaleAbs(tmp_img, dst_img);

    // 5. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); // キー入力待ち (止める)

    return 0;
}