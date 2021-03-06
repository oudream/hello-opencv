#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


void fn_outFile(const cv::Mat & m, const string & fp)
{
    //使用ofstream来输出mat
    std::ofstream fs(fp);
    if( !fs.is_open() )
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
            fs << (int)m.ptr<uchar>(i)[j] << '\t';
            //不加类型转换用txt打开是字符
        }
        fs << std::endl;
    }

    fs.close();
}

int helloMean1(const string & sFilePath)
{
    cv::Mat   img = (cv::Mat_<float>(3, 1) << 7, 8, 9);
    cv::Scalar     mean;
    cv::Scalar     dev;

    cv::meanStdDev ( img, mean, dev );
    float       m = mean.val[0];
    float       s = dev.val[0];
    std::cout << m << ",\t" << s;
    
    return 0;
}

int main(int argc, char *argv[])
{
    string sExecFilePath = argv[0][0] != '/' ? (argv[0][0] == '.' ? string(getenv("PWD"))+string(argv[0]).substr(1) : string(string(getenv("PWD"))+"/"+string(argv[0]))) : string(argv[0]);
    replace(sExecFilePath.begin(), sExecFilePath.end(), '\\', '/');
    string sBinPath = sExecFilePath.find_last_of("/\\") != string::npos ? sExecFilePath.substr(0, sExecFilePath.find_last_of("/\\")) : string();
    string sOsFilePath = sBinPath.find_last_of("/\\") != string::npos ? sBinPath.substr(0, sBinPath.find_last_of("/\\")) : string();
    string sDeployFilePath = sOsFilePath.find_last_of("/\\") != string::npos ? sOsFilePath.substr(0, sOsFilePath.find_last_of("/\\")) : string();
    cout << sExecFilePath << endl;

    helloMean1(sDeployFilePath+"/images/cars.jpg");

    return 0;
}