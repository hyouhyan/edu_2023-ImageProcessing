#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../fruit_image.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
// 0. 定数の定義
#define HUE_DIFF (90) //Hの変化量
#define SAT_DIFF (50) //Sの変化量
#define VAL_DIFF (50) //Vの変化量
#define HUE_MIN (0) // Hの最小値
#define HUE_MAX (180) // Hの最大値（シフト幅）
#define SAT_MIN (0) // Sの最小値
#define VAL_MIN (0) // Vの最小値


int main(int argc, const char * argv[]) {
    // 1. 変数の宣言
    int x, y;    //走査用
    cv::Vec3b p; //色値(HSV)
    int h,s,v;   //色値(各要素)
    cv::Mat src_img, hsv_img, dst_img; //入力画像，HSV画像，出力画像

    // 2. カラー画像の入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    // 3. 色変換 (BGR → HSV)
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    // 4. 画像処理
    // 明度を下げる
    for (y = 0; y < hsv_img.rows; y++) {
        for (x = 0; x < hsv_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x); //HSV値を取得
            h = p[0]; //Hue(色相)を取得
            s = p[1]; //Saturation(彩度)を取得
            v = p[2]; //Value(明度)を取得
            v = v - VAL_DIFF; //Vを減算
            if (v < VAL_MIN) v = VAL_MIN; //Value値の下限チェック
            p[2] = v; //Value値を設定
            hsv_img.at<cv::Vec3b>(y, x) = p; //HSV値を設定
        }
    }

    // 色相を下げる
    for (y = 0; y < hsv_img.rows; y++) {
        for (x = 0; x < hsv_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x); //HSV値を取得
            h = p[0]; //Hue(色相)を取得
            s = p[1]; //Saturation(彩度)を取得
            v = p[2]; //Value(明度)を取得
            h = h - HUE_DIFF; //Hを減算
            if (h < HUE_MIN) h = h + HUE_MAX; //Hue値の下限チェック
            p[0] = h; //Hue値を設定
            hsv_img.at<cv::Vec3b>(y, x) = p; //HSV値を設定
        }
    }

    // 彩度を下げる
    for (y = 0; y < hsv_img.rows; y++) {
        for (x = 0; x < hsv_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x); //HSV値を取得
            h = p[0]; //Hue(色相)を取得
            s = p[1]; //Saturation(彩度)を取得
            v = p[2]; //Value(明度)を取得
            s = s - SAT_DIFF; //Sを減算
            if (s < SAT_MIN) s = SAT_MIN; //Saturation値の下限チェック
            p[1] = s; //Saturation値を設定
            hsv_img.at<cv::Vec3b>(y, x) = p; //HSV値を設定
        }
    }

    
    // 5. 色変換 (HSV → BGR)
    cv::cvtColor(hsv_img, dst_img, cv::COLOR_HSV2BGR);
    
    // 6. 表示
    cv::imshow(WINDOW_NAME_INPUT , src_img); // 入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 出力画像の表示
    cv::waitKey(); // キー入力待ち (止める)
    return 0;
}
