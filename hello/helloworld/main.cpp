#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    //创建一个2*2 类型为8位的uchar类型三通道的 颜色为黄色
    Mat img(2, 2, CV_8UC3, Scalar(0, 255, 255));
    cout << "矩阵元素" << endl << img << endl;

    /*Mat srcImage = imread("G:\\group.jpg");
    cout << "图片矩阵" << endl << srcImage << endl;*/

    return 0;
}
