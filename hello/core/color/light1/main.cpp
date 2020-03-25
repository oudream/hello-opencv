/*
 *
 图像的亮度与对比度调整使用下式
 g(x) = a * f(x) + b
 f(x)为输入图像，g(x)为输出图像，alpha为大于零的参数，beta为偏置参数
 *
 */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;

/** Global Variables */
Mat f_img;
const int alpha_slider_max = 100;
const int light_slider_max = 100;
int alpha_slider;
int light_slider;
double alpha; // 对比度
int light; // 亮度


// 亮度就是每个像素所有通道都加上b
void helloLight1(Mat img, double c, int b)
{
    Mat blank =  Mat::zeros(img.size(), img.type());
    Mat dst;
    // alpha
//    addWeighted(img, c, blank, 1 - c, b, dst);
    addWeighted(img, c, blank, 0, b, dst);
    imshow("original_img", img);
    imshow("contrast_img", dst);
}

// 高对比度 : alpha=2.0;beta=20;
void helloLight2(Mat img, double a, int b)
{
//    Mat img=imread("1.jpg",1);
    Mat out=Mat::zeros(img.size(),img.type());

    for(int y=0;y<img.rows;y++)
    {
        for(int x=0;x<img.cols;x++)
        {
            for(int c=0;c<3;c++)
            {
                //saturate_cast防止溢出
                out.at<Vec3b>(y,x)[c]=saturate_cast<uchar>(a*(img.at<Vec3b>(y,x)[c])+b);
            }
        }
    }

    imshow("original_img",img);
    imshow("contrast_img",out);
}

static void on_trackbar(int, void *)
{
    alpha = (double)alpha_slider / alpha_slider_max * 2.55;
    light = light_slider * 2;
//    helloLight1(f_img, alpha, light);
    helloLight2(f_img, alpha, light);
}
//![on_trackbar]

int main(int argc, char *argv[])
{
    f_fpExec = argv[0][0] != '/' ? (argv[0][0] == '.' ? string(getenv("PWD")) + string(argv[0]).substr(1) : string(
        string(getenv("PWD")) + "/" + string(argv[0]))) : string(argv[0]);
    replace(f_fpExec.begin(), f_fpExec.end(), '\\', '/');
    f_paBin =
        f_fpExec.find_last_of("/\\") != string::npos ? f_fpExec.substr(0, f_fpExec.find_last_of("/\\")) : string();
    f_paOs = f_paBin.find_last_of("/\\") != string::npos ? f_paBin.substr(0, f_paBin.find_last_of("/\\")) : string();
    f_paDeploy = f_paOs.find_last_of("/\\") != string::npos ? f_paOs.substr(0, f_paOs.find_last_of("/\\")) : string();
    cout << "f_paDeploy: " << f_fpExec << endl;

    f_img = imread(samples::findFile(f_paDeploy + "/data/lena.jpg"));
    if (f_img.empty())
    {
        cout << "Error loading src1 \n";
        return -1;
    }

    /// Initialize values
    light_slider = 0;
    alpha_slider = 0;

    //![window]
    namedWindow("original_img", WINDOW_AUTOSIZE); // Create Window
    namedWindow("contrast_img", WINDOW_AUTOSIZE); // Create Window
    //![window]

    char TrackbarName1[50];
    sprintf(TrackbarName1, "alpha x %d", alpha_slider_max);
    createTrackbar(TrackbarName1, "contrast_img", &alpha_slider, alpha_slider_max, on_trackbar);
    char TrackbarName2[50];
    sprintf(TrackbarName2, "light x %d", light_slider_max);
    createTrackbar(TrackbarName2, "contrast_img", &light_slider, light_slider_max, on_trackbar);

    /// Show some stuff
    on_trackbar(0, 0);

    /// Wait until user press some key
    waitKey(0);

    return 0;

}




