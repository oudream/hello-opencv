#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void fn_outFile1(const cv::Mat & m)
{
    //使用ofstream来输出mat
    std::ofstream Fs("test.txt");
    if( !Fs.is_open() )
    {
        std::cout<<"open file error!"<<std::endl;
        return;
    }

    //循环输出
    int height = m.rows;
    int width = m.cols;
    for( int i=0; i<height; i++ )
    {
        for( int j=0; j<width; j++ )
        {
            Fs<<(int)m.ptr<uchar>(i)[j]<<'\t';
            //不加类型转换用txt打开是字符
        }
        Fs<<std::endl;
    }

    Fs.close();
}

int helloFromLiteral()
{
    cv::Mat m = (cv::Mat_<uchar>(3,3) << 1,2,3,
        4,5,6,
        7,8,9);
    cout << "helloFromLiteral.mat: " << endl << m << endl;
    fn_outFile1(m);
    return 0;
}

int helloFromImage1()
{
    //创建一个2*2 类型为8位的uchar类型三通道的 颜色为黄色
    Mat img(2, 2, CV_8UC3, Scalar(0, 255, 255));
    cout << "helloFromImage1.mat: " << endl << img << endl;
    return 0;
}

int helloMultDims1()
{
    int sz[3] = { 2, 2, 2 };
    //3维的  为2*2*2的   元素全部为0
    Mat array2(3, sz, CV_8UC1, Scalar(0));
    // *** 因为是三维的，所以不能用DOS界面显示
    // cout << "矩阵元素" << endl << array2 << endl;
    return 0;
}

int main(int argc, char *argv[])
{
    helloFromLiteral();

    helloFromImage1();

    helloMultDims1();

}