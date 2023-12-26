#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../aquarium.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    int x, y;

    // 画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) { 
        //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    // 出力画像のメモリ確保
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);

    int n = 0;
    scanf("%d", &n);
    int puc_x = src_img.cols / n, puc_y = src_img.rows / n;

    // 画像の走査
    //横方向
    for(y = 0; y < src_img.rows; y++)
        //縦方向
        for(x = 0; x < src_img.cols; x++){
            // 画素値の取得
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            if((x / puc_x) % 2 == 1 && (y / puc_y) % 2 == 0 || (x / puc_x) % 2 == 0 && (y / puc_y) % 2 == 1){
                s[0] = 255; //B
                s[1] = 255; //G
                s[2] = 255; //R
            }else{
                s[0] = s[0]; //B
                s[1] = s[1]; //G
                s[2] = s[2]; //R
            }
            dst_img.at<cv::Vec3b>(y, x) = s;
        }
    
    cv::imshow(WINDOW_NAME_INPUT, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); //画像の表示
    cv::waitKey(); //キー入力待ち(止める)
    return 0;
}
