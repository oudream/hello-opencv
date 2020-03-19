/*
1.基于颜色跟踪的实现步骤
2.使用inRange的方法过滤出绿色，
3.形态学造作提取
4.轮廓查找
5.外界矩形获取
6.位置标定
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;

/** Global Variables */
const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;

/** Matrices to store images */
Mat f_zoom2_src1;
Mat f_zoom2_src2;
Mat dst;

typedef void (*AddFun)(const uchar *, const uchar *, const uchar *, int, int, double, double, double);

static void
ADD8u_(const uchar *src1, const uchar *src2, uchar *dst, int len, int cn, double aplha, double beta, double gamma)
{
    for (int i = 0; i < len * cn; i++)
        dst[i] = src1[i] * aplha + src2[i] * beta + gamma;
}

static AddFun AddFunTable[] =
    {
        (AddFun) ADD8u_, 0
    };

void MyaddWeight(InputArray _src1, double alpha, InputArray _src2, double beta, double gamma, OutputArray _dst)
{
    CV_Assert(_src1.depth() == CV_8U && _src2.depth() == CV_8U);
    CV_Assert(_src1.channels() == _src2.channels() && _src1.size() == _src2.size());
    _dst.create(_src1.size(), _src1.type());

    Mat src1 = _src1.getMat();
    Mat src2 = _src2.getMat();
    Mat dst = _dst.getMat();

    int rows = src1.rows;
    int cols = src1.cols * src1.channels();

    if (src1.isContinuous() && src2.isContinuous() && dst.isContinuous())
    {
        cols *= rows;
        rows = 1;
    }

    uchar *pSrc1 = NULL;
    uchar *pSrc2 = NULL;
    uchar *pDst = NULL;
    for (int i = 0; i < rows; i++)
    {
        pSrc1 = src1.ptr<uchar>(i);
        pSrc2 = src2.ptr<uchar>(i);
        pDst = dst.ptr<uchar>(i);
        for (int j = 0; j < cols; j++)
        {
            pDst[j] = saturate_cast<uchar>(pSrc1[j] * alpha + pSrc2[j] * beta + gamma);
        }
    }
}

void MyaddWeight2(InputArray _src1, double alpha, InputArray _src2, double beta, double gamma, OutputArray _dst)
{
    CV_Assert(_src1.depth() == CV_8U && _src2.depth() == CV_8U);
    CV_Assert(_src1.channels() == _src2.channels() && _src1.size() == _src2.size());
    _dst.create(_src1.size(), _src1.type());

    Mat src1 = _src1.getMat();
    Mat src2 = _src2.getMat();
    Mat dst = _dst.getMat();

    int cn = src1.channels();

    AddFun fun = AddFunTable[src1.depth()];   //  通过数据类型，从函数指针数组中选择相应的函数进行调用

    const Mat *arrays[] = {&src1, &src2, &dst, 0};   // 注意需要在最后加一个0，作为指针数组结束的标志，以确定数组中有效指针的个数
    uchar *ptrs[3];
    NAryMatIterator it(arrays, ptrs);
    int len = (int) it.size;
    for (size_t i = 0; i < it.nplanes; i++, ++it)
        fun(ptrs[0], ptrs[1], ptrs[2], len, cn, alpha, beta, gamma);
}

//![on_trackbar]
/**
 * @function on_trackbar
 * @brief Callback for trackbar
 */
static void on_trackbar(int, void *)
{
    alpha = (double) alpha_slider / alpha_slider_max;
    beta = (1.0 - alpha);
    MyaddWeight2(f_zoom2_src1, alpha, f_zoom2_src2, beta, 0.0, dst);
//    addWeighted(src1, alpha, src2, beta, 0.0, dst);
    imshow("Linear Blend", dst);
}
//![on_trackbar]

int main(int argc, char *argv[])
{
    f_fpExec = argv[0][0] != '/' ? (argv[0][0] == '.' ? string(getenv("PWD")) + string(argv[0]).substr(1) : string(
        string(getenv("PWD")) + "/" + string(argv[0]))) : string(argv[0]);
    replace(f_fpExec.begin(), f_fpExec.end(), '\\', '/');
    f_paBin =
        f_fpExec.find_last_of("/\\") != string::npos ? f_fpExec.substr(0, f_fpExec.find_last_of("/\\")) : string();
    f_paOs = f_paBin.find_last_of("/\\") != string::npos ? f_paBin.substr(0, f_paBin.find_last_of("/\\")) : string();
    f_paDeploy = f_paOs.find_last_of("/\\") != string::npos ? f_paOs.substr(0, f_paOs.find_last_of("/\\")) : string();
    cout << "f_paDeploy: " << f_fpExec << endl;

    //![load]
    /// Read images ( both have to be of the same size and type )
    f_zoom2_src1 = imread(samples::findFile(f_paDeploy + "/data/pic3.png"));
    f_zoom2_src2 = imread(samples::findFile(f_paDeploy + "/data/pic5.png"));
    //![load]

    if (f_zoom2_src1.empty())
    {
        cout << "Error loading src1 \n";
        return -1;
    }
    if (f_zoom2_src2.empty())
    {
        cout << "Error loading src2 \n";
        return -1;
    }

    /// Initialize values
    alpha_slider = 0;

    //![window]
    namedWindow("Linear Blend", WINDOW_AUTOSIZE); // Create Window
    //![window]

    //![create_trackbar]
    char TrackbarName[50];
    sprintf(TrackbarName, "Alpha x %d", alpha_slider_max);
    createTrackbar(TrackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar);
    //![create_trackbar]

    /// Show some stuff
    on_trackbar(alpha_slider, 0);

    /// Wait until user press some key
    waitKey(0);
    return 0;

}




