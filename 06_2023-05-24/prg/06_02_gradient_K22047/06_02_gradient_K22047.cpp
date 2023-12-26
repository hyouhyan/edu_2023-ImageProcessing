#include<iostream>
#include<opencv2/opencv.hpp>

#define FILE_NAME "../vscode.png"

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

    // グレースケール変換
    cv::Mat gray_img;
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    // ソーベルトフィルタ(縦)
    cv::Mat sobel_img1;
    cv::Sobel(gray_img, sobel_img1, CV_64FC1, 1, 0);

    // ソーベルトフィルタ(横)
    cv::Mat sobel_img2;
    cv::Sobel(gray_img, sobel_img2, CV_64FC1, 0, 1);

    // エッジ強度(勾配)を求める
    cv::Mat tmp_img = cv::Mat(src_img.size(), CV_64FC1);
    for(int y = 0; y < src_img.rows; y++){
        for(int x = 0; x < src_img.cols; x++){
            double dx = sobel_img1.at<double>(y, x);
            double dy = sobel_img2.at<double>(y, x);
            double grad = sqrt(dx * dx + dy * dy);
            tmp_img.at<double>(y, x) = (double)grad;
        }
    }

    // 変換
    cv::Mat grad_img;
    cv::convertScaleAbs(tmp_img, grad_img);
    
    // 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, grad_img);
    cv::waitKey();
    
    return 0;
}
