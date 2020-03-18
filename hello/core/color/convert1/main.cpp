#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;

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

int helloRGB22HSV(const string & fpImg)
{
    Mat srcImage = imread(fpImg);  
    fn_outFile(srcImage, f_paDeploy+"/tmp/mat0.txt");

    while (1) {
        imshow("原图", srcImage);
        if (waitKey(30) > 0) break;
    }

    Mat rgbImg,hsvImg;

    cvtColor( srcImage, hsvImg, COLOR_RGB2HSV);
    fn_outFile(hsvImg, f_paDeploy+"/tmp/mat1.txt");

    while (1) {
        imshow("2HSV", hsvImg);
        if (waitKey(30) > 0) break;
    }

    cvtColor( hsvImg, rgbImg, COLOR_HSV2RGB);
    fn_outFile(rgbImg, f_paDeploy+"/tmp/mat2.txt");

    while (1) {
        imshow("2RGB", rgbImg);
        if (waitKey(30) > 0) break;
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

    helloRGB22HSV(f_paDeploy + "/images/fruit.jpg");

    return 0;
}
