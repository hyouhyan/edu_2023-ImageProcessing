#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../input_img1.png"

#define KING_UPPER "../king2.png"
#define PAWN_UPPER "../pawn2.png"
#define PROM_PAWN_UPPER "../prom_pawn2.png"

#define KING_LOWER "../king1.png"
#define PAWN_LOWER "../pawn1.png"
#define PROM_PAWN_LOWER "../prom_pawn1.png"

int templateMatchAndCount(cv::Mat src_img, cv::Mat template_img, float threshold);

int main(void){
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

    cv::Mat template_img_king_upper = cv::imread(KING_UPPER, cv::IMREAD_COLOR);
    cv::Mat template_img_pawn_upper = cv::imread(PAWN_UPPER, cv::IMREAD_COLOR);
    cv::Mat template_img_prom_pawn_upper = cv::imread(PROM_PAWN_UPPER, cv::IMREAD_COLOR);

    cv::Mat template_img_king_lower = cv::imread(KING_LOWER, cv::IMREAD_COLOR);
    cv::Mat template_img_pawn_lower = cv::imread(PAWN_LOWER, cv::IMREAD_COLOR);
    cv::Mat template_img_prom_pawn_lower = cv::imread(PROM_PAWN_LOWER, cv::IMREAD_COLOR);

    int flg = src_img.empty() || template_img_king_upper.empty() || template_img_pawn_upper.empty() || template_img_prom_pawn_upper.empty() || template_img_king_lower.empty() || template_img_pawn_lower.empty() || template_img_prom_pawn_lower.empty();

    if (flg) {
        fprintf(stderr, "ファイルひらけんかったわ\n");
        return (-1);
    }

    //王の処理(Upper)
    int upKingCount = templateMatchAndCount(src_img, template_img_king_upper, 0.2);
    //歩の処理(Upper)
    int upPawnCount = templateMatchAndCount(src_img, template_img_pawn_upper, 0.2);
    //成歩の処理(Upper)
    upPawnCount += templateMatchAndCount(src_img, template_img_prom_pawn_upper, 0.2);
    //出力(Upper)
    printf("upper\nking: %d\npwan: %d\n\n", upKingCount, upPawnCount);

    //王の処理(Lower)
    int lowKingCount = templateMatchAndCount(src_img, template_img_king_lower, 0.2);
    //歩の処理(Lower)
    int lowPawnCount = templateMatchAndCount(src_img, template_img_pawn_lower, 0.2);
    //成歩の処理(Lower)
    lowPawnCount += templateMatchAndCount(src_img, template_img_prom_pawn_lower, 0.2);
    //出力(Lower)
    printf("lower\nking: %d\npwan: %d\n", lowKingCount, lowPawnCount);

    return 0;
}

int templateMatchAndCount(cv::Mat src_img, cv::Mat template_img, float threshold){
    cv::Mat compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);
    cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);

    int count = 0;
    int flg = 0;

    for(int y = 0; y < compare_img.rows; y++){
        for(int x = 0; x < compare_img.cols; x++){
            float s = compare_img.at<float>(y, x);
            if(s < threshold){
                count++;
                x += 5;
                flg++;
            }
        }
        if(flg) y += 5;
        flg = 0;
    }

    return count;
}