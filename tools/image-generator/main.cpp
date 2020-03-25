#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


using namespace std;
using namespace cv;

std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;


int helloSaveImage1(const string & fp)
{
    Mat mat1 = imread(fp);
    mat

/*
    Mat mat1 = (Mat_<double>(4,4)
        << 0, 0.2588190734386444, 0.0, 1.5529145002365112,
        0.08852133899927139, -0.3303661346435547, -0.9396926164627075, -0.10281121730804443,
        -0.24321036040782928, 0.9076734185218811, -0.342020183801651, 6.130080699920654,
        0, 0, 0, 1);
*/
    imwrite()
    return 0;
}

int helloImageMatInfo1(const string & sFilePath)
{
    Mat srcImage = imread(sFilePath,IMREAD_UNCHANGED);
//    bitwise_and()
    cout << srcImage.size << endl;
    cout << srcImage.type() << endl;
    cout << srcImage.depth() << endl;
    cout << srcImage.total() << endl;
    cout << srcImage.elemSize() << endl;
    cout << srcImage.elemSize1() << endl;
    cout << srcImage.depth() << endl;
    cout << srcImage.channels() << endl;
    fn_outFile(srcImage, f_paDeploy + "/tmp/001.txt");

    return 0;
}

int helloImageRepeat1(const std::string& fp, int nx, int ny)
{
    Mat3b img = imread(fp);

    Mat dst(img.rows * ny, img.cols * nx, img.type());

    for (int iy = 0; iy < ny; ++iy)
    {
        for (int ix = 0; ix < nx; ++ix)
        {
            Rect roi(img.cols * ix, img.rows * iy, img.cols, img.rows);
            img.copyTo(dst(roi));
        }
    }

    imshow("img", img);
    imshow("res", dst);
    waitKey();

    return 0;
}

int helloToImage1(const string & sFilePath)
{
//    Mat grHistogram(260, 301, CV_8UC3, Scalar(0, 0, 0));
//    line(grHistrogram,pt1,pt2,Scalar(255,255,255),1,8,0);
//    imwrite()
    return 0;
}

int main(int argc, char *argv[])
{
    f_fpExec = argv[0][0] != '/' ? (argv[0][0] == '.' ? std::string(getenv("PWD"))+std::string(argv[0]).substr(1) : std::string(std::string(getenv("PWD"))+"/"+std::string(argv[0]))) : std::string(argv[0]);
    replace(f_fpExec.begin(), f_fpExec.end(), '\\', '/');
    f_paBin = f_fpExec.find_last_of("/\\") != std::string::npos ? f_fpExec.substr(0, f_fpExec.find_last_of("/\\")) : std::string();
    f_paOs = f_paBin.find_last_of("/\\") != std::string::npos ? f_paBin.substr(0, f_paBin.find_last_of("/\\")) : std::string();
    f_paDeploy = f_paOs.find_last_of("/\\") != std::string::npos ? f_paOs.substr(0, f_paOs.find_last_of("/\\")) : std::string();
    cout << "f_paDeploy: " << f_fpExec << endl;

//    helloFromImage1(f_paDeploy+"/images/fruit.jpg");
//
//    helloImageMatInfo1(f_paDeploy+"/images/fruit.jpg");
    helloImageMatInfo1(f_paDeploy+"/images/p10x10-black-white.png");

//    helloImageRepeat1(f_paDeploy+"/images/p10x10-black-white.png", 150,100);

    return 0;
}