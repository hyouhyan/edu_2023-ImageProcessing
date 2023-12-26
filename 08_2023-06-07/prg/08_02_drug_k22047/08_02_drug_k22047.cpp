#include<iostream>
#include<opencv2/opencv.hpp>

#define HIGHVAL 255
#define LOWVAL 0
#define TH 100
#define FILE_NUM 8

#define ERROR_RANGE 3

// #define DEBUG 1

#define FILE_NAME1 "../drug0.png"
#define FILE_NAME2 "../drug11.png"

int main(void){
    //変数定義
    cv::Mat src_img, gray_img;
    //画像入力
    if((src_img = cv::imread(FILE_NAME1, 1)).empty()){
        std::cout << "No image found." << std::endl;
        return -1;
    }

    // 判定用プログラム
    // RGBの各色が何回出るか判定するための配列
    int numOfR[256] = {0}, numOfG[256] = {0}, numOfB[256] = {0};

    for(int y = 0; y < src_img.rows; y++){
        for(int x = 0; x < src_img.cols; x++){
            cv::Vec3b bgr = src_img.at<cv::Vec3b>(y, x);
            if(bgr[0] != 0 && bgr[1] != 0 && bgr[2] != 0){
                numOfB[bgr[0]]++;
                numOfG[bgr[1]]++;
                numOfR[bgr[2]]++;
            }
        }
    }

    //RGBの最大値と最頻値を取得
    int maxR = 0, maxG = 0, maxB = 0;
    int maxRValue = 0, maxGValue = 0, maxBValue = 0;

    for(int i = 0; i < 256; i++){
        if(numOfR[i] > maxR){
            maxR = numOfR[i];
            maxRValue = i;
        }
        if(numOfG[i] > maxG){
            maxG = numOfG[i];
            maxGValue = i;
        }
        if(numOfB[i] > maxB){
            maxB = numOfB[i];
            maxBValue = i;
        }
    }

    //drug11.pngの読み込み
    if((src_img = cv::imread(FILE_NAME2, 1)).empty()){
        std::cout << "No image found." << std::endl;
        return -1;
    }

    // gray_imgのメモリ確保
    gray_img.create(src_img.size(), CV_8UC1);

    //maxRGBValueを元に二値化
    //結果計算用の変数
    int par = 0, unpar = 0;
    //ただし+-ERROR_RANGEの誤差を許容する
    for(int y = 0; y < src_img.rows; y++){
        for(int x = 0; x < src_img.cols; x++){
            cv::Vec3b bgr = src_img.at<cv::Vec3b>(y, x);
            if(
                bgr[0] > (maxBValue - ERROR_RANGE) && bgr[0] < (maxBValue + ERROR_RANGE) &&
                bgr[1] > (maxGValue - ERROR_RANGE) && bgr[1] < (maxGValue + ERROR_RANGE) &&
                bgr[2] > (maxRValue - ERROR_RANGE) && bgr[2] < (maxRValue + ERROR_RANGE)
            ){
                gray_img.at<unsigned char>(y, x) = HIGHVAL;
                par++;
            }else{
                gray_img.at<unsigned char>(y, x) = LOWVAL;
                unpar++;
            }
        }
    }

    //結果計算及び表示
    float par_rate = (float)par / (par + unpar);
    if(par_rate < 0.17)
        printf("欠損\n");
    else if(par_rate > 0.23)
        printf("膨張\n");
    else
        printf("正常\n");

    // デバッグ用に画像を表示
    #if DEBUG
    cv::imshow("src image", src_img);
    cv::imshow("bin image", gray_img);

    cv::waitKey(0);
    #endif

    return 0;
}