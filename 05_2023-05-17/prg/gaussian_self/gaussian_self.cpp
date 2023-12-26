#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[]) {
    // 画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty()) {
        fprintf(stderr, "Failed to open file.\n");
        return -1;
    }

    // 出力画像の宣言
    cv::Mat dst_img;

    // フィルタの宣言と設計(入力と正規化)
    double filter_h[] = {
        1./16., 2./16., 1./16.,
        2./16., 4./16., 2./16.,
        1./16., 2./16., 1./16.
    };

    cv::Mat kernel = cv::Mat(3, 3, CV_64FC1, filter_h);
    cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);

    // フィルタ処理
    cv::filter2D(src_img, dst_img, -1, kernel);

    // 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
