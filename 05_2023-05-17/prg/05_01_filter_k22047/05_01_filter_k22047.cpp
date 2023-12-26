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
    // tmp_img: 一時的な画像(forループのため)
    cv::Mat dst_img, tmp_img = src_img.clone();

    int kernelSize = 3, n = 0;
    printf("Input number: ");scanf("%d", &n);
    for(int i = 0; i < n; i++) cv::blur(tmp_img, tmp_img, cv::Size(kernelSize, kernelSize));

    // 出力画像のコピー
    dst_img = tmp_img.clone();

    // 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
