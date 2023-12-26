#include<iostream>
#include<opencv2/opencv.hpp>

#define FILE_NAME1 "../input1.jpg"
#define FILE_NAME2 "../input2.jpg"

// 閾値
#define THREDHOLD 20

#define WINDOW_NAME_SUB "sub"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[]){
    // 画像をグレースケールで入力
    cv::Mat src_img1 = cv::imread(FILE_NAME1, 0);
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0);
    if(src_img2.empty() || src_img1.empty()){
        fprintf(stderr, "Failed to open file.\n");
        return -1;
    }

    cv::Mat sub_img = cv::Mat(src_img1.size(), CV_8UC1);
    cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC1);
    int x, y;

    for(y = 0; y < src_img1.rows; y++){
        for(x = 0; x < src_img2.cols; x++){
            int s1 = (int)src_img1.at<uchar>(y, x);
            int s2 = (int)src_img2.at<uchar>(y, x);

            int s_result = abs(s1 - s2);
            sub_img.at<uchar>(y, x) = (uchar)s_result;

            if(s_result > THREDHOLD)
                s_result = 255;
            else
                s_result = 0;
            
            result_img.at<uchar>(y, x) = s_result;
        }
    }

    // 出力
    cv::imshow(WINDOW_NAME_SUB, sub_img);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey();
    
    return 0;
}
