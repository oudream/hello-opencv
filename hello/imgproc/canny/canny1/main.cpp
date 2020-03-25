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

int helloCanny1(const string & fpImg)
{
    //【0】载入原始图
    Mat srcImage = imread(fpImg);  //工程目录下应该有一张名为1.jpg的素材图
    fn_outFile(srcImage, f_paDeploy+"/tmp/mat0.txt");

    imshow("【原始图】Canny边缘检测", srcImage); 	//显示原始图
    Mat dstImage,edge,grayImage;	//参数定义

    //【1】创建与src同类型和大小的矩阵(dst)
    dstImage.create( srcImage.size(), srcImage.type() );

    //【2】将原图像转换为灰度图像
    //此句代码的OpenCV2版为：
    //cvtColor( srcImage, grayImage, CV_BGR2GRAY );
    //此句代码的OpenCV3版为：
    cvtColor( srcImage, grayImage, COLOR_BGR2GRAY );
    fn_outFile(grayImage, f_paDeploy+"/tmp/mat1.txt");

    //【3】先用使用 3x3内核来降噪
    blur( grayImage, edge, Size(3,3) );
    fn_outFile(edge, f_paDeploy+"/tmp/mat2.txt");

    //【4】运行Canny算子
    Canny( edge, edge, 3, 9,3 );
    fn_outFile(edge, f_paDeploy+"/tmp/mat3.txt");

    //【5】显示效果图
    imshow("【效果图】Canny边缘检测", edge);

    waitKey(0);

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

    helloCanny1(f_paDeploy + "/images/fruit.jpg");

    return 0;
}