#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME1 "../input_img1.png"
#define FILE_NAME3 "../input_img3.png"
#define FILE_NAME4 "../input_img4.png"
#define FILE_NAME5 "../input_img5.png"

#define KING_UPPER "../king1.png"
#define PAWN_UPPER "../pawn1.png"
#define PROM_PAWN_UPPER "../prom_pawn1.png"

#define KING_LOWER "../king2.png"
#define PAWN_LOWER "../pawn2.png"
#define PROM_PAWN_LOWER "../prom_pawn2.png"

void templateMatchAndStatus(cv::Mat src_img, cv::Mat template_img, float threshold, int status[9][9], int height, int width, int stNum);
void printDiff(int beforeStatus[9][9], int afterStatus[9][9]);

int main(void){
    cv::Mat before_img = cv::imread(FILE_NAME3, cv::IMREAD_COLOR);
    cv::Mat after_img = cv::imread(FILE_NAME4, cv::IMREAD_COLOR);

    cv::Mat template_img_king_upper = cv::imread(KING_UPPER, cv::IMREAD_COLOR);
    cv::Mat template_img_pawn_upper = cv::imread(PAWN_UPPER, cv::IMREAD_COLOR);
    cv::Mat template_img_prom_pawn_upper = cv::imread(PROM_PAWN_UPPER, cv::IMREAD_COLOR);

    cv::Mat template_img_king_lower = cv::imread(KING_LOWER, cv::IMREAD_COLOR);
    cv::Mat template_img_pawn_lower = cv::imread(PAWN_LOWER, cv::IMREAD_COLOR);
    cv::Mat template_img_prom_pawn_lower = cv::imread(PROM_PAWN_LOWER, cv::IMREAD_COLOR);
    
    int flg = before_img.empty() || after_img.empty() || template_img_king_upper.empty() || template_img_pawn_upper.empty() || template_img_prom_pawn_upper.empty() || template_img_king_lower.empty() || template_img_pawn_lower.empty() || template_img_prom_pawn_lower.empty();

    if (flg) {
        fprintf(stderr, "ファイルひらけんかったわ\n");
        return (-1);
    }

    //盤面の状態を配列に保存
    //11: 王(Upper), 12: 歩(Upper), 13: 成歩(Upper)
    //21: 王(Lower), 22: 歩(Lower), 23: 成歩(Lower)
    int beforeStatus[9][9] = {0};

    //1マスの縦横を求める
    int height = before_img.rows / 9;
    int width = before_img.cols / 9;

    //王の処理(Upper)
    templateMatchAndStatus(before_img, template_img_king_upper, 0.2, beforeStatus, height, width, 11);
    //歩の処理(Upper)
    templateMatchAndStatus(before_img, template_img_pawn_upper, 0.2, beforeStatus, height, width, 12);
    //成歩の処理(Upper)
    templateMatchAndStatus(before_img, template_img_prom_pawn_upper, 0.2, beforeStatus, height, width, 13);

    //王の処理(Lower)
    templateMatchAndStatus(before_img, template_img_king_lower, 0.2, beforeStatus, height, width, 21);
    //歩の処理(Lower)
    templateMatchAndStatus(before_img, template_img_pawn_lower, 0.2, beforeStatus, height, width, 22);
    //成歩の処理(Lower)
    templateMatchAndStatus(before_img, template_img_prom_pawn_lower, 0.2, beforeStatus, height, width, 23);


    //Afterの処理
    int afterStatus[9][9] = {0};

    //王の処理(Upper)
    templateMatchAndStatus(after_img, template_img_king_upper, 0.2, afterStatus, height, width, 11);
    //歩の処理(Upper)
    templateMatchAndStatus(after_img, template_img_pawn_upper, 0.2, afterStatus, height, width, 12);
    //成歩の処理(Upper)
    templateMatchAndStatus(after_img, template_img_prom_pawn_upper, 0.2, afterStatus, height, width, 13);

    //王の処理(Lower)
    templateMatchAndStatus(after_img, template_img_king_lower, 0.2, afterStatus, height, width, 21);
    //歩の処理(Lower)
    templateMatchAndStatus(after_img, template_img_pawn_lower, 0.2, afterStatus, height, width, 22);
    //成歩の処理(Lower)
    templateMatchAndStatus(after_img, template_img_prom_pawn_lower, 0.2, afterStatus, height, width, 23);

    //差異を出力
    printf("before\n");
    printDiff(beforeStatus, afterStatus);

    printf("after\n");
    printDiff(afterStatus, beforeStatus);


    return 0;
}

void templateMatchAndStatus(cv::Mat src_img, cv::Mat template_img, float threshold, int status[9][9], int height, int width, int stNum){
    cv::Mat compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);
    cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);

    int flg = 0;

    for(int y = 0; y < compare_img.rows; y++){
        for(int x = 0; x < compare_img.cols; x++){
            float s = compare_img.at<float>(y, x);
            if(s < threshold){
                //状態をstatusに反映
                status[y / height][x / width] = stNum;
                x += 5;
                flg++;
            }
        }
        if(flg) y += 5;
        flg = 0;
    }
}

void printDiff(int beforeStatus[9][9], int afterStatus[9][9]){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            if(beforeStatus[y][x] != afterStatus[y][x]){
                if(beforeStatus[y][x] == 0) continue;

                if(beforeStatus[y][x] % 10 == 1) printf("king ");
                if(beforeStatus[y][x] % 10 == 2) printf("pawn ");
                if(beforeStatus[y][x] % 10 == 3) printf("prow_pawn ");

                if(beforeStatus[y][x] / 10 == 1) printf("(upper):");
                if(beforeStatus[y][x] / 10 == 2) printf("(lower):");

                printf("%d-%d\n", 9 - x, y + 1);
            }
        }
    }
}