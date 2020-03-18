#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;

int helloVideoPlay1(const std::string& fp)
{
    //【1】读入视频
    VideoCapture capture(fp);
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open file!" << endl;
        return 0;
    }

    //【2】循环显示每一帧
    while(1)
    {
        Mat frame;//定义一个Mat变量，用于存储每一帧的图像
        capture>>frame;  //读取当前帧

        //若视频播放完成，退出循环
        if (frame.empty())
        {
            break;
        }

        imshow("读取视频",frame);  //显示当前帧
        waitKey(30);  //延时30ms
    }
    return 0;
}

int helloVideoCapture1()
{
    //【1】从摄像头读入视频
    VideoCapture capture(0);

    //【2】循环显示每一帧
    while(1)
    {
        Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
        capture>>frame;  //读取当前帧
        imshow("读取视频",frame);  //显示当前帧
        if (waitKey(30)>0)
            break;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    f_fpExec = argv[0][0] != '/' ? (argv[0][0] == '.' ? string(getenv("PWD"))+string(argv[0]).substr(1) : string(string(getenv("PWD"))+"/"+string(argv[0]))) : string(argv[0]);
    replace(f_fpExec.begin(), f_fpExec.end(), '\\', '/');
    f_paBin = f_fpExec.find_last_of("/\\") != string::npos ? f_fpExec.substr(0, f_fpExec.find_last_of("/\\")) : string();
    f_paOs = f_paBin.find_last_of("/\\") != string::npos ? f_paBin.substr(0, f_paBin.find_last_of("/\\")) : string();
    f_paDeploy = f_paOs.find_last_of("/\\") != string::npos ? f_paOs.substr(0, f_paOs.find_last_of("/\\")) : string();
    cout << "f_paDeploy: " << f_fpExec << endl;

    helloVideoPlay1(f_paDeploy + "/videos/peoples.avi");

    helloVideoCapture1();

    return 0;
}