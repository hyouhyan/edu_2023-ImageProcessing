#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME "../issue1.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

//二値化しきい値
#define BIN_TH (100)

int main(int argc, const char * argv[]) {
    //グレースケールで読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if(src_img.empty()){
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    //二値化
    cv::Mat bin_img;
    cv::threshold(src_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

    //輪郭を取得
    std::vector< std::vector< cv::Point > > contours;
    cv::findContours(bin_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    //円形度を求める
    for (int i = 0; i < contours.size(); i++) {
        double L, S, circularity;
        L = cv::arcLength(contours[i], true);
        S = cv::contourArea(contours[i]);
        circularity = (4 * CV_PI * S) / (L * L);
        //円形度が0.8以上の対象を黒で塗りつぶす
        if (circularity > 0.8) {
            cv::drawContours(bin_img, contours, i, CV_RGB(0, 0, 0), -1);
        }
    }

    //円を削除した画像を保存
    cv::Mat nonCircle_img = bin_img.clone();

    //膨張
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1, -1), 20);
    //収縮
    cv::erode(bin_img, bin_img, cv::Mat(), cv::Point(-1, -1), 20);

    //bin_imgの輪郭を取得
    cv::findContours(bin_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    //カラフルに塗りつぶし
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
    cv::Scalar color[] = {
        CV_RGB(255,0,0),
        CV_RGB(0,255,0),
        CV_RGB(0,0,255),
        CV_RGB(255,0,255)
        };

    for (int i = 0; i < contours.size(); i++) {
        cv::drawContours(dst_img, contours, i, color[i % 4], -1);
    }

    //src_imgのcolsとrowsをもとに走査
    //(nonCircle_img == 0)のとき、dst_imgをRGB(0, 0, 0)で塗りつぶす
    for (int y = 0; y < src_img.rows; y++) {
        for (int x = 0; x < src_img.cols; x++) {
            if (nonCircle_img.at<uchar>(y, x) == 0) {
                dst_img.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
            }
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    cv::imwrite("../10_k22047.jpg", dst_img);

    return 0;
}

