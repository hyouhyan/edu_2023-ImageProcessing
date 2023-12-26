#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME_DORA "../gazoDora.jpg"
#define FILE_NAME_RED "../red.jpg"

int main(void){
    cv::Mat src_img = cv::imread(FILE_NAME_DORA, 0);
    cv::Mat template_red_img = cv::imread(FILE_NAME_RED, 0);

    if(src_img.empty() || template_red_img.empty()){
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    cv::Mat compare_img = cv::Mat(cv::Size(src_img.rows - template_red_img.rows + 1, src_img.cols - template_red_img.cols + 1), CV_32F);
    cv::matchTemplate(src_img, template_red_img, compare_img, cv::TM_SQDIFF_NORMED);

    //compare_imgを出力できるようにする(正規化)
    // cv::Mat dst_img = cv::Mat(cv::Size(compare_img.cols, compare_img.rows), CV_8U);
    cv::Mat dst_img = cv::Mat(compare_img.size(), CV_8U);
    for(int y = 0; y < compare_img.rows; y++){
        for(int x = 0; x < compare_img.cols; x++){
            dst_img.at<uchar>(y, x) = compare_img.at<float>(y, x) * 255;
        }
    }

    cv::imshow("compare_img", dst_img);
    cv::waitKey();

    cv::imwrite("../1202_k22047.jpg", dst_img);

    return 0;
}