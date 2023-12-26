#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME_DORA "../gazoDora.jpg"
#define FILE_NAME_GREEN "../green.jpg"
#define FILE_NAME_RED "../red.jpg"
#define FILE_NAME_YELLOW "../yellow.jpg"
#define FILE_NAME_STAR "../star.jpg"

typedef struct imgs{
    cv::Mat template_img;
    cv::Scalar color;
} Imgs;

static Imgs imgs[] = {
    {cv::imread(FILE_NAME_GREEN), CV_RGB(0, 255, 0)},
    {cv::imread(FILE_NAME_RED), CV_RGB(255, 0, 0)},
    {cv::imread(FILE_NAME_YELLOW), CV_RGB(255, 255, 0)},
    {cv::imread(FILE_NAME_STAR), CV_RGB(108, 0, 124)}
};

int main(void){
    cv::Mat src_img = cv::imread(FILE_NAME_DORA);

    int files_num = sizeof(imgs) / sizeof(imgs[0]);

    int flag = 0;
    for(int i = 0; i < files_num; i++){
        if(imgs[i].template_img.empty()){
            flag = 1;
            break;
        }
    }

    if(src_img.empty() || flag){
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    cv::Mat compare_img = cv::Mat(cv::Size(src_img.rows - imgs[0].template_img.rows + 1, src_img.cols - imgs[0].template_img.cols + 1), CV_32F, 1);

    cv::Mat dst_img = src_img.clone();
    
    double s;
    for(int i = 0; i < files_num; i++){
        cv::matchTemplate(src_img, imgs[i].template_img, compare_img, cv::TM_SQDIFF_NORMED);
        for(int y = 0; y < compare_img.rows; y++){
            for(int x = 0; x < compare_img.cols; x++){
                s = compare_img.at<float>(y, x);
                if(s < 0.1){
                    cv::rectangle(dst_img, cv::Point(x, y), cv::Point(x + imgs[i].template_img.cols, y + imgs[i].template_img.rows), imgs[i].color, 2);
                }
            }
        }
    }
    
    cv::imshow("dst_img", dst_img);
    cv::waitKey();

    cv::imwrite("../1201_k22047.jpg", dst_img);

    return 0;
}