#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


using namespace std;
using namespace cv;

std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;

int helloLogicOperation1(const string & sFilePath)
{
    Mat srcImage = imread(sFilePath,IMREAD_UNCHANGED);

    Mat matAnd(srcImage.size(), srcImage.type(), Scalar(0xF0, 0x0F, 0xF0));

    Mat matOut;
    bitwise_and(srcImage, matAnd, matOut);

    FileStorage f1(f_paDeploy + "/tmp/001.mat", FileStorage::WRITE);
    f1 << "srcImage" << srcImage;

    FileStorage f2(f_paDeploy + "/tmp/002.mat", FileStorage::WRITE);
    f2 << "matAnd" << matAnd;

    FileStorage f3(f_paDeploy + "/tmp/003.mat", FileStorage::WRITE);
    f3 << "matOut" << matOut;

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

    FileStorage f1(f_paDeploy + "/tmp/001.mat", FileStorage::WRITE);
    f1 << srcImage;

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
//    helloImageMatInfo1(f_paDeploy+"/images/p10x10-black-white.png");

    helloLogicOperation1(f_paDeploy+"/images/p10x10-black-white.png");

    return 0;
}