#include<iostream>
#include<opencv2/opencv.hpp>

#define FILE_NAME "../apple_tree.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (3)

int main(int argc, char const *argv[]){
    // 画像をカラーで入力
    cv::Mat src_img = cv::imread(FILE_NAME);
    if(src_img.empty()){
        fprintf(stderr, "Failed to open file.\n");
        return -1;
    }

    // 出力画像の宣言
    cv::Mat dst_img1;

    // グレースケール変換
    cv::Mat gray_img;
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    // 輝度値にガウシアンフィルタ
    cv::GaussianBlur(gray_img, dst_img1, cv::Size(FILTER_SIZE, FILTER_SIZE), 0, 0);

    // プリューウィトフィルタの定義
    double filterP[] = {
        -1., -1., -1.,
        0., 0., 0.,
        1., 1., 1.
    };
    cv::Mat kernel = cv::Mat(3, 3, CV_64F, filterP);

    cv::Mat dst_img2;

    // プリューウィトフィルタ(処理)
    cv::Mat tmp_img;
    cv::filter2D(dst_img1, tmp_img, CV_64F, kernel);
    cv::convertScaleAbs(tmp_img, dst_img2);

    // 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow("output1", dst_img1);
    cv::imshow("output2", dst_img2);
    cv::waitKey();
    
    return 0;
}
