#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../gem2.jpg"

int main(int argc, const char * argv[]) {
    //1. 入力画像をカラーで入力
    cv::Mat src_img;
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    cv::Mat dst_img = src_img.clone();

    //black_gemの処理
    //グレースケール
    cv::Mat gray_img;
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

    //2値化
    //閾値 20
    cv::Mat bin_img;
    cv::threshold(gray_img, bin_img, 20, 255, cv::THRESH_BINARY_INV);

    //op cl
    //回数 15
    cv::Mat tmp_img;
    cv::dilate(bin_img, tmp_img, cv::Mat(), cv::Point(-1,-1), 15);
    cv::erode(tmp_img, bin_img, cv::Mat(), cv::Point(-1,-1), 15);

    //輪郭追跡
    std::vector< std::vector< cv::Point > > contours;
    cv::findContours(bin_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    //個数
    int black_count = contours.size();
    printf("black gem count = %d\n", black_count);

    // 黒曜石(Black gem)は赤で外接長方形
    for (int i=0; i<contours.size(); i++) {
        cv::Rect rect = cv::boundingRect(contours[i]);
        cv::rectangle(dst_img, rect, cv::Scalar(0,0,255), 2);
    }

    //green_gemの処理
    //G 50 ~ 100
    int g_min = 50, g_max = 100;
    //R 0 ~ 50
    int r_max = 50;

    bin_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    for(int y = 0; y < src_img.rows; y++){
        for(int x = 0; x < src_img.cols; x++){
            cv::Vec3b bgr = src_img.at<cv::Vec3b>(y, x);
            if(g_min < bgr[1] && bgr[1] < g_max && bgr[2] < r_max){
                bin_img.at<uchar>(y, x) = 255;
            }
        }
    }

    //cl op
    //回数 5
    cv::dilate(bin_img, tmp_img, cv::Mat(), cv::Point(-1,-1), 5);
    cv::erode(tmp_img, bin_img, cv::Mat(), cv::Point(-1,-1), 5);

    //op cl
    //回数 15
    cv::erode(bin_img, tmp_img, cv::Mat(), cv::Point(-1,-1), 15);
    cv::dilate(tmp_img, bin_img, cv::Mat(), cv::Point(-1,-1), 15);

    //輪郭追跡
    contours.clear();
    cv::findContours(bin_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    //個数
    int green_count = contours.size();
    printf("green gem count = %d\n", green_count);

    // トルコ石(Green gem)は緑で塗りつぶし
    for (int i=0; i<contours.size(); i++) {
        cv::drawContours(dst_img, contours, i, cv::Scalar(0,255,0), -1);
    }


    //golden_gemの処理
    cv::Mat hsv_img;

    //HSVに変換
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    //H 20 ~ 60
    int h_min = 20, h_max = 60;
    //S 100 ~ 200
    int s_min = 100, s_max = 200;

    bin_img = cv::Mat::zeros(hsv_img.size(), CV_8UC1);
    for(int y = 0; y < hsv_img.rows; y++){
        for(int x = 0; x < hsv_img.cols; x++){
            cv::Vec3b hsv = hsv_img.at<cv::Vec3b>(y, x);
            if(h_min < hsv[0] && hsv[0] < h_max && s_min < hsv[1] && hsv[1] < s_max){
                bin_img.at<uchar>(y, x) = 255;
            }
        }
    }

    //cl op
    //回数 5
    cv::dilate(bin_img, tmp_img, cv::Mat(), cv::Point(-1,-1), 5);
    cv::erode(tmp_img, bin_img, cv::Mat(), cv::Point(-1,-1), 5);

    //op cl
    //回数 15
    cv::erode(bin_img, tmp_img, cv::Mat(), cv::Point(-1,-1), 15);
    cv::dilate(tmp_img, bin_img, cv::Mat(), cv::Point(-1,-1), 15);

    //輪郭追跡
    contours.clear();
    cv::findContours(bin_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    //個数
    int golden_count = contours.size();
    printf("golden gem count = %d\n", golden_count);

    // 黄金(Golden gem)は白で外接円
    for (int i=0; i<contours.size(); i++) {
        cv::Point2f center; //外接円の中心座標
        float radius;       //外接円の半径
        cv::minEnclosingCircle(contours[i], center, radius); //外接円を求める
        cv::circle(dst_img, center, radius, cv::Scalar(255,255,255), 2); //外接円を描画  
    }


    cv::imshow("dst", dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}
