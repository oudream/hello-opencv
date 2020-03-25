#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


using namespace std;
using namespace cv;

std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;


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

int helloImageSplit1(const std::string& fp, const std::string& pa)
{
    Mat src = imread(fp); //load  image

    Mat bgr[3];   //destination array
    split(src,bgr);//split source

//Note: OpenCV uses BGR color order
    imwrite(pa+"/blue.png",bgr[0]); //blue channel
    imwrite(pa+"/green.png",bgr[1]); //green channel
    imwrite(pa+"/red.png",bgr[2]); //red channel
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

    helloImageRepeat1(f_paDeploy+"/images/p10x10-black-white.png", 150,100);
    helloImageSplit1(f_paDeploy+"/images/p10x10-black-white.png", f_paDeploy+"/tmp");

    return 0;
}