/*
    協力者
        k22025 大久保 勇希
        k22057 胡麻本 城太郎
*/
#include<iostream>
#include<opencv2/opencv.hpp>

#define HIGHVAL 255
#define LOWVAL 0
#define TH 100
#define FILE_NUM 8

#define STRING_MAX 256

#define FILE_NAME "../drug"
#define FILE_TYPE ".png"

int main(void){
    //変数定義
    cv::Mat src_img, gray_img, bin_img;
    char file[STRING_MAX];
    for(int i = 0; i < FILE_NUM; i++){
        snprintf(file, STRING_MAX, "%s%d%s", FILE_NAME, i, FILE_TYPE);
        //画像入力
        if((src_img = cv::imread(file, 1)).empty()){
            std::cout << "No image found." << std::endl;
            return -1;
        }

        // 輝度画像への変換
        cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

        //二値画像の生成
        bin_img.create(gray_img.size(), gray_img.type());

        //par
        int par = 0, unpar = 0;
        //二値画像への変換
        for(int y = 0; y < gray_img.rows; y++){
            for(int x = 0; x < gray_img.cols; x++){
                if(gray_img.at<unsigned char>(y, x) > TH){
                    par++;
                    bin_img.at<unsigned char>(y, x) = HIGHVAL;
                }else{
                    unpar++;
                    bin_img.at<unsigned char>(y, x) = LOWVAL;
                }
            }
        }

        // printf("%d\n", par);
        // printf("%d\n", unpar);

        float par_rate = (float)par / (par + unpar);
        if(par_rate < 0.17)
            printf("%d:欠損\n",i);
        else if(par_rate > 0.23)
            printf("%d:膨張\n",i);
        else
            printf("%d:正常\n",i);
    }

    return 0;
}