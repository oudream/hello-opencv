#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static const cv::Scalar BGR_BLACK = cv::Scalar(0, 0, 0);
static const cv::Scalar BGR_GREEN = cv::Scalar(0, 255, 0);
static const cv::Scalar BGR_BLUE = cv::Scalar(255, 0, 0);
static const cv::Scalar BGR_CYAN = cv::Scalar(255, 255, 0);
static const cv::Scalar BGR_RED = cv::Scalar(0, 0, 255);
static const cv::Scalar BGR_YELLOW = cv::Scalar(0, 255, 255);
static const cv::Scalar BGR_MAGENTA = cv::Scalar(255, 0, 255);
static const cv::Scalar BGR_WHITE = cv::Scalar(255, 255, 255);
static const cv::Scalar BGR_GRAY = cv::Scalar(128, 128, 128);
static const cv::Scalar BGR_MLAB = cv::Scalar(255, 128, 128);
static const cv::Scalar BGR_NAVY = cv::Scalar(0, 0, 128);
static const cv::Scalar BGR_OLIVE = cv::Scalar(0, 128, 128);
static const cv::Scalar BGR_MAROON = cv::Scalar(0, 0, 128);
static const cv::Scalar BGR_TEAL = cv::Scalar(128, 128, 0);
static const cv::Scalar BGR_ROSE = cv::Scalar(128, 0, 255);
static const cv::Scalar BGR_AZURE = cv::Scalar(255, 128, 0);
static const cv::Scalar BGR_LIME = cv::Scalar(0, 255, 191);
static const cv::Scalar BGR_GOLD = cv::Scalar(0, 215, 255);
static const cv::Scalar BGR_BROWN = cv::Scalar(42, 42, 165);
static const cv::Scalar BGR_ORANGE = cv::Scalar(0, 165, 255);
static const cv::Scalar BGR_CHARTREuse = cv::Scalar(0, 255, 128);
static const cv::Scalar BGR_ORANGE_red = cv::Scalar(0, 69, 255);
static const cv::Scalar BGR_PURPLE = cv::Scalar(128, 0, 128);
static const cv::Scalar BGR_INDIGO = cv::Scalar(130, 0, 75);
static const cv::Scalar BGR_PINK = cv::Scalar(203, 192, 255);
static const cv::Scalar BGR_CHERRY = cv::Scalar(99, 29, 222);
static const cv::Scalar BGR_BLUBERRy = cv::Scalar(247, 134, 79);
static const cv::Scalar BGR_RASPBERry = cv::Scalar(92, 11, 227);
static const cv::Scalar BGR_SILVER = cv::Scalar(192, 192, 192);
static const cv::Scalar BGR_VIOLET = cv::Scalar(226, 43, 138);
static const cv::Scalar BGR_APRICOT = cv::Scalar(177, 206, 251);
static const cv::Scalar BGR_TURQUOIse = cv::Scalar(208, 224, 64);
static const cv::Scalar BGR_CELESTIal_blue = cv::Scalar(208, 151, 73);
static const cv::Scalar BGR_AMETHYSt = cv::Scalar(204, 102, 153);
static const cv::Scalar BGR_NOT_SET = cv::Scalar(-1, -1, -1);

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
    int arr[3] = {4,3,2};
    Mat L(3, arr, CV_8UC(1), Scalar::all(0));
    return 0;
}

int helloOutMat()
{
    Mat img(5,4, CV_8UC3, Scalar(0,0,255));
    cout << "img = \n"<< " "  << img << "\n\n";
    img.create(3,2, CV_8UC(3));
    cout << "img = \n"<< " "  << img << "\n\n";
    return 0;
}

int helloOutZero()
{
    Mat imgA = Mat::eye(4, 4, CV_64F);
    cout << "imgA = \n " << imgA << "\n\n";

    Mat imgB = Mat::ones(2, 2, CV_32F);
    cout << "imgB = \n " << imgB << "\n\n";

    Mat imgC = Mat::zeros(3,3, CV_8UC1);
    cout << "imgC = \n " << imgC << "\n\n";
}

int helloLiteral()
{
    Mat img = (Mat_<int>(3,3) << 1, 0, 1, 0, -2, 0, 3, 0, 3);
    cout << "img = \n " << img << "\n\n";

    return 0;
}

int helloClone()
{
    Mat img = (Mat_<int>(3,3) << 1, 0, 1, 0, -2, 0, 3, 0, 3);
    cout << "img = \n " << img << "\n\n";

    Mat row_cloned_img = img.row(1).clone();
    cout << "row_cloned_img = \n " << row_cloned_img << "\n\n";

    return 0;
}

int helloPushback()
{
    Mat m1(515,2,5);
    Mat m2(17,12,5);


// 1. make a single *colum* of m1:
    m1 = m1.reshape(1, (int)m1.total());
// same for m2:
    m2 = m2.reshape(1, (int)m2.total());

    m1.push_back(m2);
    Mat final_row = m1.reshape(1,1);
}

int helloCreateImage_8UC1()
{
    //创建一个高400，宽200的灰度图的Mat对象
    Mat M(600, 600, CV_8UC1);
    namedWindow("Test");
//    bgr2hsv(BGR_YELLOW)
    for (int i = 0; i < M.rows; i++)
    {
        for (int j = 0; j < M.cols; j++)
        {
            if (j % 6 > 2)
                M.at<uchar>(i, j) = i * j / 20;
            else
                M.at<uchar>(i, j) = 120;
        }
    }
    imshow("Test", M);   //窗口中显示图像
    return 0;
}

int helloCreateImage_8UC3()
{
    Mat M(Size(600, 600), CV_8UC3, BGR_ORANGE);
    namedWindow("Test");
    for (int i = 0; i < M.rows; i++)
    {
        for (int j = 0; j < M.cols; j++)
        {
            * M.ptr<Vec3b>(i,j) = (j % 6 > 2) ? Vec3d(BGR_ORANGE.val) : Vec3d(BGR_GOLD.val);
        }
    }
    imshow("Test", M);   //窗口中显示图像
    return 0;
}

int helloModifyImage()
{
    Mat img = (Mat_<int>(3,3) << 1, 0, 1, 0, -2, 0, 3, 0, 3);

    for(int y=0;y<img.rows;y++)
    {
        for(int x=0;x<img.cols;x++)
        {
            // get pixel
            Vec3b & color = img.at<Vec3b>(y,x);
            // ... do something to the color ....
            color[0] = 13;
            color[1] = 13;
            color[2] = 13;
            // set pixel
            //image.at<Vec3b>(Point(x,y)) = color;
            //if you copy value
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    helloFromLiteral();

    helloFromImage1();

    helloMultDims1();

}