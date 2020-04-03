/**
 (y-y1)/(y2-y1)=(x-x1)/(x2-x1)
 y=round(double(x-x1)/(x2-x1)*(y2-y1)+y1)
 x=round(double(y-y1)/(y2-y1)*(x2-x1)+x1)
 */
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

//### const
// color threshold
static const int CT = 0x7F;
// Accuracy
static const double ACC = 0.8;
// const Canny
static const int lowThreshold = 15;
static const int ratio = 3;
static const int kernel_size = 3;
// corner color value
static Mat CORNER_TOP_LEFT(Size(15, 15), CV_8UC1, Scalar());
static Mat CORNER_BOTTOM_LEFT(Size(15, 15), CV_8UC1, Scalar());
static Mat CORNER_TOP_RIGHT(Size(15, 15), CV_8UC1, Scalar());
static Mat CORNER_BOTTOM_RIGHT(Size(15, 15), CV_8UC1, Scalar());

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

static const cv::Scalar RED_LOW1 = cv::Scalar(0, 80, 60);
static const cv::Scalar RED_HIGH1 = cv::Scalar(18, 255, 255);
static const cv::Scalar RED_LOW2 = cv::Scalar(160, 80, 60);
static const cv::Scalar RED_HIGH2 = cv::Scalar(179, 255, 255);
//static const cv::Scalar RED_LOW = cv::Scalar(162, 170, 135);
//static const cv::Scalar RED_HIGH = cv::Scalar(185, 225, 220);
//static const cv::Scalar RED_LOW1 = cv::Scalar(0, 110, 125);
//static const cv::Scalar RED_HIGH1 = cv::Scalar(35, 255, 255);
//static const cv::Scalar RED_LOW2 = cv::Scalar(145, 110, 115);
//static const cv::Scalar RED_HIGH2 = cv::Scalar(181, 255, 255);

static const cv::Scalar BLUE_LIGHT_LOW = cv::Scalar(85, 45, 55);
static const cv::Scalar BLUE_LIGHT_HIGH = cv::Scalar(110, 255, 255);
// static const  cv::Scalar BLUE_DARK_LOW = cv::Scalar(97, 80, 90);
// static const  cv::Scalar  BLUE_DARK_HIGH = 	cv::Scalar(115, 105, 120);
static const cv::Scalar BLUE_DARK_LOW = cv::Scalar(70, 30, 30);
static const cv::Scalar BLUE_DARK_HIGH = cv::Scalar(130, 255, 255);

// static const cv::Scalar GREEN_DARK_LOW = cv::Scalar(54, 108, 100);
// static const cv::Scalar GREEN_DARK_HIGH = cv::Scalar(65, 155, 140);
static const cv::Scalar GREEN_DARK_LOW = cv::Scalar(40, 40, 40);
static const cv::Scalar GREEN_DARK_HIGH = cv::Scalar(75, 255, 255);
// static const cv::Scalar GREEN_FL_LOW = cv::Scalar(29, 145, 165);
// static const cv::Scalar GREEN_FL_HIGH = cv::Scalar(65, 255, 255);
static const cv::Scalar GREEN_FL_LOW = cv::Scalar(29, 55, 85);
static const cv::Scalar GREEN_FL_HIGH = cv::Scalar(65, 255, 255);

// from gmm model
// static const cv::Scalar VIOLET_LOW = cv::Scalar(138, 55, 90);
// static const cv::Scalar VIOLET_HIGH = cv::Scalar(165, 100, 150);
static const cv::Scalar VIOLET_LOW = cv::Scalar(120, 60, 100);
static const cv::Scalar VIOLET_HIGH = cv::Scalar(165, 190, 255);

//static const cv::Scalar YELLOW_LOW = cv::Scalar(15, 25, 25);
//static const cv::Scalar YELLOW_HIGH = cv::Scalar(32, 250, 255);
// static const cv::Scalar YELLOW_LOW = cv::Scalar(14, 165, 185);
// static const cv::Scalar YELLOW_HIGH = cv::Scalar(30, 195, 225);
static const cv::Scalar YELLOW_LOW = cv::Scalar(10, 160, 160);
static const cv::Scalar YELLOW_HIGH = cv::Scalar(40, 255, 255);

static const cv::Scalar ORANGE_LOW = cv::Scalar(0, 130, 130);
static const cv::Scalar ORANGE_HIGH = cv::Scalar(40, 255, 255);

#define SWITCH_NONE  -1
#define SWITCH_OPEN  1
#define SWITCH_CLOSE 0

//### var
std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;
//
int f_iLineWidth = 10;

Scalar bgr2hsv(Scalar bgr)
{
    Mat b(1, 1, CV_8UC3, bgr);
    Mat h(1, 1, CV_8UC3, Scalar());
    cvtColor(b, h, COLOR_BGR2HSV);
    return Scalar(h.data[0], h.data[1], h.data[2]);
}

Scalar hsv2bgr(Scalar hsv)
{
    Mat h(1, 1, CV_8UC3, hsv);
    Mat b(1, 1, CV_8UC3, Scalar());
    cvtColor(h, b, COLOR_BGR2HSV);
    return Scalar(b.data[0], b.data[1], b.data[2]);
}

//### fun
void check_red_range(const Mat &in, const Mat &out)
{
    cv::Mat hsv_image;
    //cv::Mat out;
    cv::cvtColor(in, hsv_image, cv::COLOR_BGR2HSV);
    cv::Mat lower_red_hue_range;
    cv::Mat upper_red_hue_range;

    // in hsv red is splitted in two areals. This function checks both of them...
    cv::inRange(hsv_image, RED_LOW1, RED_HIGH1, lower_red_hue_range);
    cv::inRange(hsv_image, RED_LOW2, RED_HIGH2, upper_red_hue_range);

    //...and merges them.
    cv::addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, out);
}

void check_red_range(const UMat &in, const UMat &out)
{
    cv::UMat hsv_image;
    //cv::Mat out;
    cv::cvtColor(in, hsv_image, cv::COLOR_BGR2HSV);
    cv::UMat lower_red_hue_range;
    cv::UMat upper_red_hue_range;

    // in hsv red is splitted in two areals. This function checks both of them...
    cv::inRange(hsv_image, RED_LOW1, RED_HIGH1, lower_red_hue_range);
    cv::inRange(hsv_image, RED_LOW2, RED_HIGH2, upper_red_hue_range);

    //...and merges them.
    cv::addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, out);
}

void check_yellow_range(const Mat &in, const Mat &out)
{
    cv::Mat hsv_image;
    cv::cvtColor(in, hsv_image, cv::COLOR_BGR2HSV);
    cv::inRange(hsv_image, YELLOW_LOW, YELLOW_HIGH, out);
}

void check_yellow_range(const UMat &in, const UMat &out)
{
    cv::UMat hsv_image;
    cv::cvtColor(in, hsv_image, cv::COLOR_BGR2HSV);
    cv::inRange(hsv_image, YELLOW_LOW, YELLOW_HIGH, out);
}

void fn_outFile(const cv::Mat &m, const string &fp)
{
    std::ofstream fs(fp);
    if (!fs.is_open())
    {
        std::cout << "open file error!" << std::endl;
        return;
    }

    for (int r = 0; r < m.rows; ++r)
    {
        for (int c = 0; c < m.cols; ++c)
        {
            fs << std::setfill('0') << std::setw(3) << (int) *m.ptr(r, c) << ' ';
        }
        fs << std::endl;
    }

    fs.close();
}

void fn_outFile(const cv::Mat &m, Rect roi, const string &fp)
{
    std::ofstream fs(fp);
    if (!fs.is_open())
    {
        std::cout << "open file error!" << std::endl;
        return;
    }

    for (int r = roi.y; r < roi.y + roi.height; r++)
    {
        for (int c = roi.x; c < roi.x + roi.width; c++)
        {
            fs << std::setfill('0') << std::setw(3) << (int) *m.ptr(r, c) << ' ';
        }
        fs << std::endl;
    }

    fs.close();
}

int helloInRange1(const std::string &fp)
{
    Mat src = imread(fp);
    if (src.empty())
    {
        cout << "Could not load source image " << fp << endl;
        return -1;
    }
    Mat hsvImg, mask, maskImg;
    cvtColor(src, hsvImg, COLOR_RGB2HSV);
//    inRange(hsvImg, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
    Scalar lower_red(20, 20, 20);
    Scalar upper_red(200, 200, 200);

    inRange(hsvImg, lower_red, upper_red, mask);
//    inRange(hsvImg, Scalar(156, 43, 46), Scalar(180, 255, 255), mask);
    bitwise_and(src, src, maskImg, mask);

    FileStorage f1(f_paDeploy + "/tmp/001.mat", FileStorage::WRITE);
    f1 << "maskImg" << maskImg;

    imshow("mastk", maskImg);

    return 0;
}

int helloInRange2(const std::string &fp)
{
    Mat src = imread(fp);
    if (src.empty())
    {
        cout << "Could not load source image " << fp << endl;
        return -1;
    }
    Mat dst(src.size(), CV_8UC1);
    check_red_range(src, dst);

    FileStorage f1(f_paDeploy + "/tmp/001.mat", FileStorage::WRITE);
    f1 << "dst" << dst;

    imshow("mastk", dst);

    return 0;
}

inline int sum33(const uchar *r0, const uchar *r1, const uchar *r2)
{
    return
        r0[0] + r0[1] + r0[2]
        + r1[0] + r1[1] + r1[2]
        + r2[0] + r2[1] + r2[2];
}

inline bool checkROIFull(const Mat &img, Rect rect)
{
    for (int i = rect.x; i < rect.x + rect.width; ++i)
    {
        for (int j = rect.y; j < rect.y + rect.height; ++j)
        {
            if (*(img.ptr<uchar>(i, j)) < 0x7F)
            {
                return false;
            }
        }
    }
    return true;
}

inline Rect getFullXRect(const Mat &img, int y, int xEnd)
{
    Rect r(0, y, 0, 1);
    for (int x1 = 0; x1 < xEnd; ++x1)
    {
        if (*(img.ptr(y, x1)) > CT)
        {
            for (int x2 = x1 + 1; x2 < xEnd; ++x2)
            {
                if (*(img.ptr(y, x2)) < CT)
                {
                    r.x = x1;
                    r.width = x2 - x1;
                }
            }
        }
    }
    return r;
}

inline Rect getFullYRect(const Mat &img, int x, int yEnd)
{
    Rect r(x, 0, 1, 0);
    for (int y1 = 0; y1 < yEnd; ++y1)
    {
        if (*(img.ptr(y1, x)) > CT)
        {
            for (int y2 = y1 + 1; y2 < yEnd; ++y2)
            {
                if (*(img.ptr(y2, x)) < CT)
                {
                    r.y = y1;
                    r.height = y2 - y1;
                }
            }
        }
    }
    return r;
}

inline void initCorner()
{
    // corner ( L ) fill 0x00
    for (int r = 0; r < 15; ++r)
    {
        for (int c = 0; c < 15; ++c)
        {
            *CORNER_TOP_LEFT.ptr(r, c) = (r < 5 || c < 5) ? 0x00 : 0xFF;
            *CORNER_BOTTOM_LEFT.ptr(r, c) = (r > 10 || c < 5) ? 0x00 : 0xFF;
            *CORNER_TOP_RIGHT.ptr(r, c) = (r < 5 || c > 10) ? 0x00 : 0xFF;
            *CORNER_BOTTOM_RIGHT.ptr(r, c) = (r > 10 || c > 10) ? 0x00 : 0xFF;
        }
    }

    fn_outFile(CORNER_TOP_LEFT, f_paDeploy + "/images/switch/CORNER_TOP_LEFT.txt");
    fn_outFile(CORNER_BOTTOM_LEFT, f_paDeploy + "/images/switch/CORNER_BOTTOM_LEFT.txt");
    fn_outFile(CORNER_TOP_RIGHT, f_paDeploy + "/images/switch/CORNER_TOP_RIGHT.txt");
    fn_outFile(CORNER_BOTTOM_RIGHT, f_paDeploy + "/images/switch/CORNER_BOTTOM_RIGHT.txt");
}

inline void xorBlock(const Mat &img, Point p, const Mat &block, Mat &result)
{
    for (int y = 0; y < block.rows; ++y)
    {
        for (int x = 0; x < block.cols; ++x)
        {
            *result.ptr(y, x) = (*img.ptr(p.y + y, p.x + x)) ^ (*block.ptr(y, x));
        }
    }
}

inline void xorBlock2(const Mat &img, Point p, const Mat &block, Mat &result)
{
    fn_outFile(img, Rect(p.x, p.y, 15, 15), f_paDeploy + "/tmp/d-img0.txt");
    fn_outFile(block, f_paDeploy + "/tmp/d-block0.txt");
    for (int y = 0; y < block.rows; ++y)
    {
        for (int x = 0; x < block.cols; ++x)
        {
            uchar a = (*img.ptr(p.y + y, p.x + x));
            uchar b = (*block.ptr(y, x));
            uchar v = a ^b;
            *result.ptr(y, x) = v;
        }
    }
    fn_outFile(img, Rect(p.x, p.y, 15, 15), f_paDeploy + "/tmp/d-img1.txt");
    fn_outFile(block, f_paDeploy + "/tmp/d-block1.txt");
    fn_outFile(result, f_paDeploy + "/tmp/d-result1.txt");
}

//*CORNER_TOP_LEFT.ptr(r, c) = (r < 5 || c < 5) ? 0x00 : 0xFF;
inline Scalar findTopLeft(const Mat &img)
{
    if (img.rows < 1080 / 2)
    {
        return Scalar();
    }
    // er : end row, ec : end col
    int er = img.rows / 2;
    int ec = img.cols / 2;
//    Mat cornerXor(Size(15, 15), CV_8UC1);
    for (int y = 0; y < er; ++y)
    {
        for (int x = 0; x < ec; ++x)
        {
            // sum corner : L |_
            int sumCor = 0;
            int sumCon = 0;
            for (int r = 0; r < 15; ++r)
            {
                for (int c = 0; c < 15; ++c)
                {
                    // sum corner : L |_
                    if (r < 5 || c < 5)
                    {
                        if (*img.ptr(y + r, x + c) > CT)
                            ++sumCor;
                    }
                    else
                    {
                        if (*img.ptr(y + r, x + c) < CT)
                            ++sumCon;
                    }
                }
            }
            if (sumCor > 125 * ACC && sumCon > 100 * ACC)
            {
                // fn_outFile(cornerXor, f_paDeploy + "/tmp/cornerXor1.txt");
                // fn_outFile(img, Rect(x, y, 15, 15), f_paDeploy + "/tmp/img1.txt");
                // std::cout << "y: " << y << ", x: " << x << std::endl;
                // std::cout << "sumCor: " << sumCor << ", sumCon: " << sumCon << std::endl;
                return Scalar(y + 5, x + 5, y - 5, x - 5);
            }
        }
    }
    return Scalar();
}

//*CORNER_BOTTOM_LEFT.ptr(r, c) = (r > 10 || c < 5) ? 0x00 : 0xFF;
inline Scalar findBottomLeft(const Mat &img)
{
    if (img.rows < 1080 / 2)
    {
        return Scalar();
    }
    // color threshold
    // er : end row, ec : end col
    int er = img.rows / 2;
    int ec = img.cols / 2;
    for (int y = img.rows - 1 - 15; y > er; --y)
    {
        for (int x = 0; x < ec; ++x)
        {
            // sum corner : L |_
            int sumCor = 0;
            int sumCon = 0;
            for (int r = 0; r < 15; ++r)
            {
                for (int c = 0; c < 15; ++c)
                {
                    // sum corner : L |_
                    if (r > 10 || c < 5)
                    {
                        if (*img.ptr(r + y, c + x) > CT)
                            ++sumCor;
                    }
                    else
                    {
                        if (*img.ptr(r + y, c + x) < CT)
                            ++sumCon;
                    }
                }
            }
            if (sumCor > 125 * ACC && sumCon > 100 * ACC)
            {
                return Scalar(y + 10, x + 5, y + 20, x - 5);
            }
        }
    }
    return Scalar();
}

//*CORNER_TOP_RIGHT.ptr(r, c) = (r < 5 || c > 10) ? 0x00 : 0xFF;
inline Scalar findTopRight(const Mat &img)
{
    if (img.rows < 1080 / 2)
    {
        return Scalar();
    }
    // er : end row, ec : end col
    int er = img.rows / 2;
    int ec = img.cols / 2;
    for (int y = 0; y < er; ++y)
    {
        for (int x = img.cols - 1 - 15; x > ec; --x)
        {
            // sum corner : L |_
            int sumCor = 0;
            int sumCon = 0;
            for (int r = 0; r < 15; ++r)
            {
                for (int c = 0; c < 15; ++c)
                {
                    // sum corner : L |_
                    if (r < 5 || c > 10)
                    {
                        if (*img.ptr(y + r, x + c) > CT)
                            ++sumCor;
                    }
                    else
                    {
                        if (*img.ptr(y + r, x + c) < CT)
                            ++sumCon;
                    }
                }
            }
            if (sumCor > 125 * ACC && sumCon > 100 * ACC)
            {
                return Scalar(y + 5, x + 10, y - 5, x + 20);
            }
        }
    }
    return Scalar();
}

//*CORNER_BOTTOM_RIGHT.ptr(r, c) = (r > 10 || c > 10) ? 0x00 : 0xFF;
inline Scalar findBottomRight(const Mat &img)
{
    if (img.rows < 1080 / 2)
    {
        return Scalar();
    }
    // color threshold
    // er : end row, ec : end col
    int er = img.rows / 2;
    int ec = img.cols / 2;
    for (int y = img.rows - 1 - 15; y > er; --y)
    {
        for (int x = img.cols - 1 - 15; x > ec; --x)
        {
            // sum corner : L |_
            int sumCor = 0;
            int sumCon = 0;
            for (int r = 0; r < 15; ++r)
            {
                for (int c = 0; c < 15; ++c)
                {
                    // sum corner : L |_
                    if (r > 10 || c > 10)
                    {
                        if (*img.ptr(r + y, c + x) > CT)
                            ++sumCor;
                    }
                    else
                    {
                        if (*img.ptr(r + y, c + x) < CT)
                            ++sumCon;
                    }
                }
            }
            if (sumCor > 125 * ACC && sumCon > 100 * ACC)
            {
                return Scalar(y + 10, x + 10, y + 20, x + 20);
            }
        }
    }
    return Scalar();
}

//*CORNER_BOTTOM_LEFT.ptr(r, c) = (r > 10 || c < 5) ? 0x00 : 0xFF;
inline vector<Scalar> findLeft(const Mat &img, Point p1, Point p2)
{
    vector<Scalar> rs;
#define findLeft_GX(y) round(double(p2.x - p1.x)/(p2.y - p1.y)*(y-p1.y)+p1.x)
    bool bv = abs(p1.x - p2.x) < 3;
    int ySkip = f_iLineWidth * 2;
    for (int y = p1.y + ySkip; y < p2.y - ySkip; ++y)
    {
        int x0 = bv ? p1.x : findLeft_GX(y);
        for (int x = x0 - f_iLineWidth; x < x0 + f_iLineWidth; ++x)
        {
            // sum corner : L |_
            int sumCor = 0;
            int sumCon = 0;
            for (int r = 0; r < 15; ++r)
            {
                for (int c = 0; c < 15; ++c)
                {
                    // sum corner : L |_
                    if (r < 5 || c < 5)
                    {
                        if (*img.ptr(y + r, x + c) > CT)
                            ++sumCor;
                    }
                    else
                    {
                        if (*img.ptr(y + r, x + c) < CT)
                            ++sumCon;
                    }
                }
            }
            if (sumCor > 125 * ACC && sumCon > 100 * ACC)
            {
                // fn_outFile(cornerXor, f_paDeploy + "/tmp/cornerXor1.txt");
                // fn_outFile(img, Rect(x, y, 15, 15), f_paDeploy + "/tmp/img1.txt");
                // std::cout << "y: " << y << ", x: " << x << std::endl;
                // std::cout << "sumCor: " << sumCor << ", sumCon: " << sumCon << std::endl;
                rs.push_back(Scalar(y + 5, x + 5, y - 5, x - 5));
                y += ySkip;
                break;
            }
        }
    }
    return rs;
}

//*CORNER_TOP_RIGHT.ptr(r, c) = (r < 5 || c > 10) ? 0x00 : 0xFF;
inline vector<Scalar> findRight(const Mat &img, Point p1, Point p2)
{
    vector<Scalar> rs;
#define findRight_GX(y) round(double(p2.x - p1.x)/(p2.y - p1.y)*(y-p1.y)+p1.x)
    bool bv = abs(p1.x - p2.x) < 3;
    int ySkip = f_iLineWidth * 2;
    for (int y = p1.y + ySkip; y < p2.y - ySkip; ++y)
    {
        int x0 = bv ? p1.x : findRight_GX(y);
        for (int x = x0 + f_iLineWidth - 1; x >= x0 - f_iLineWidth; --x)
        {
            // sum corner : L |_
            int sumCor = 0;
            int sumCon = 0;
            for (int r = 0; r < 15; ++r)
            {
                for (int c = 0; c < 15; ++c)
                {
                    // sum corner : L |_
                    if (r < 5 || c > 10)
                    {
                        if (*img.ptr(y + r, x + c) > CT)
                            ++sumCor;
                    }
                    else
                    {
                        if (*img.ptr(y + r, x + c) < CT)
                            ++sumCon;
                    }
                }
            }
            if (sumCor > 125 * ACC && sumCon > 100 * ACC)
            {
                // fn_outFile(cornerXor, f_paDeploy + "/tmp/cornerXor1.txt");
                // fn_outFile(img, Rect(x, y, 15, 15), f_paDeploy + "/tmp/img1.txt");
                // std::cout << "y: " << y << ", x: " << x << std::endl;
                // std::cout << "sumCor: " << sumCor << ", sumCon: " << sumCon << std::endl;
                rs.push_back(Scalar(y + 5, x + 10, y - 5, x + 20));
                y += ySkip;
                break;
            }
        }
    }
    return rs;
}

Mat getCanny(const std::string &fp)
{
    Mat src, src_gray;
    Mat dst, detected_edges;

    src = imread(fp, IMREAD_COLOR);
    dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ::ratio, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);

    return dst;
}

Mat f_histMat;
int f_histBrightness = 40;
int f_histContrast = 40;

static void updateBrightnessContrast(int, void *)
{
    int histSize = 64;
    double a, b;
    if (f_histContrast > 0)
    {
        double delta = 127. * f_histContrast / 100;
        a = 255. / (255. - delta * 2);
        b = a * (f_histBrightness - delta);
    }
    else
    {
        double delta = -128. * f_histContrast / 100;
        a = (256. - delta * 2) / 255.;
        b = a * f_histBrightness + delta;
    }

    Mat dst, hist;
    f_histMat.convertTo(dst, CV_8U, a, b);
    imshow("image", dst);
    //计算直方图
    calcHist(&dst, 1, 0, Mat(), hist, 1, &histSize, 0);
    Mat histImage = Mat::ones(200, 320, CV_8U) * 255;
    //归一化
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, CV_32F);
    histImage = Scalar::all(255);
    int binW = cvRound((double) histImage.cols / histSize);
    for (int i = 0; i < histSize; i++)
        rectangle(histImage, Point(i * binW, histImage.rows),
                  Point((i + 1) * binW, histImage.rows - cvRound(hist.at<float>(i))), Scalar::all(0), -1, 8, 0);
    imshow("histogram", histImage);
}

int helloHist(const std::string &fp)
{
    f_histMat = imread(fp);
    if (f_histMat.empty())
    {
        printf("Can not read the image...\n");
        return -1;
    }
    namedWindow("image", 0);
    namedWindow("histogram", 0);
    createTrackbar("brightness", "image", &f_histBrightness, 200, updateBrightnessContrast);
    createTrackbar("contrast", "image", &f_histContrast, 200, updateBrightnessContrast);

    updateBrightnessContrast(0, 0);
    return 0;
}

// pb : Point Bottom, pt : Point Top
// Disdance
inline double getDisdance(Point p1, Point p2)
{
    return pow(pow(p2.x - p1.x, 2) + pow(p1.y - p2.y, 2), 0.5);
}

// pb : Point Bottom, pt : Point Top
// coordinate
Point getCoordinate(const Point &pb, const Point &pt, int len)
{
    if (len < 1) return pb;
    bool bv = abs(pt.x - pb.x) < 1;
    int x = pb.x;
    int y = pb.y - len;
    if (!bv)
    {
        double l = pow(pow(pt.x - pb.x, 2) + pow(pb.y - pt.y, 2), 0.5);
        x = round((pt.x - pb.x) / l * len + pb.x);
        y = round(pb.y - (pb.y - pt.y) / l * len);
    }

    return Point(x, y);
}

// pb : Point Bottom, pt : Point Top
int getVPx(const Mat &img, const Point &pb, const Point &pt)
{
    double dis = pow(pow(pt.x - pb.x, 2) + pow(pb.y - pt.y, 2), 0.5);
    Point pb0 = getCoordinate(pb, pt, round(dis * 6 / 20));

#define getVPx_GX(y) round(double(y-pb.y)/(pt.y-pb.y)*(pt.x-pb.x)+pb.x)
    bool bv = abs(pb0.x - pt.x) < 1;
    int iCount = 0;
    for (int y = pb0.y; y > pt.y; --y)
    {
        int x = bv ? pb0.x : getVPx_GX(y);
        if (*img.ptr(y, x) > CT)
        {
            ++iCount;
        }
    }
    return iCount;
}

// ptl : Point Top Left
// ptr : Point Top Right
// pbl : Point Bottom Left
// pbl : Point Bottom Right
vector<int>
getVPxHist(const Mat &img, const Point &ptl, const Point &ptr, const Point &pbl, const Point &pbr, vector<Point> &pts, vector<Point> &pbs)
{
    vector<int> vpxes;
    int lt = ptr.x - ptl.x;
    int lb = pbr.x - pbl.x;
#define getVPxHist_GTY(x0) round(double(x0-ptl.x)/(ptr.x-ptl.x)*(ptr.y-ptl.y)+ptl.y)
#define getVPxHist_GBY(x0) round(double(x0-pbl.x)/(pbr.x-pbl.x)*(pbr.y-pbl.y)+pbl.y)
    // CV_8UC1
    int tLen = ptr.x - ptl.x;
    // bvt : bool vertical top, bvb : bool vertical bottom
    bool bvt = abs(ptr.y - ptl.y) < 3;
    bool bvb = abs(pbr.y - pbl.y) < 3;
    for (int tStep = 0; tStep < tLen; ++tStep)
    {
        int xt = ptl.x + tStep;
        int yt = bvt ? ptl.y : getVPxHist_GTY(xt);
        Point pt(xt, yt);
        // bStep/tStep=lb/lt 
        int bStep = round(double(lb) / lt * tStep);
        int xb = pbl.x + bStep;
        int yb = bvb ? pbl.y : getVPxHist_GBY(xb);
        Point pb(xb, yb);
        // p1 : Top Point, p2 : Bottom Point
        int vpx = getVPx(img, pb, pt);
        vpxes.push_back(vpx);
        pts.push_back(pt);
        pbs.push_back(pb);
    }
    return vpxes;
}

// pb : Point Bottom, pt : Point Top
void lineHist(Mat &img, Point pb, Point pt, int len)
{
    if (len < 1) return;
    bool bv = abs(pt.x - pb.x) < 1;
    int x = pb.x;
    int y = pb.y - len;
    if (!bv)
    {
        double l = pow(pow(pt.x - pb.x, 2) + pow(pb.y - pt.y, 2), 0.5);
        x = round((pt.x - pb.x) / l * len + pb.x);
        y = round(pb.y - (pb.y - pt.y) / l * len);
    }

    line(img, pb, Point(x, y), BGR_GREEN);
}

int sumVpx(const vector<int> &vpxes, int start, int end)
{
    int r = 0;
    for (int i = start; i < end; ++i)
    {
        r += vpxes[i];
    }
    return r;
}

// ses : [ (Start, End), (Start, End) ... ]
void flagGradle(const vector<int> &vpxes, vector<pair<int, int> > &ses)
{
    if (vpxes.size() > 0)
    {
        int emptyStart = 0;
        int emptyEnd = 0;
        for (int i = 30; i < vpxes.size() - 30; ++i)
        {
            int l = sumVpx(vpxes, i, i + 10);
            if (l < 30)
            {
                if (emptyStart == 0)
                {
                    if (sumVpx(vpxes, i, i + 5) > 30)
                        emptyStart = i + 5;
                    else
                        emptyStart = i;
                    emptyEnd = 0;
                }
            }
            else
            {
                if (emptyEnd == 0)
                {
                    if (sumVpx(vpxes, i, i + 5) < 30)
                        emptyEnd = i + 5;
                    else
                        emptyEnd = i;
                    if (emptyStart > 0)
                    {
                        ses.push_back(pair<int, int>(emptyStart, emptyEnd));
                    }
                    emptyStart = 0;
                }
            }
        }
    }
}

// Switch State : [ (index, state), (index, state) ... ]
void detectiveSwitch(const vector<pair<int, int> > &ses, vector<pair<int, int>> &ss)
{
    if (ses.size() < 3) return;
    int s0 = 0;
    int s1 = ses[0].first;
    int s2 = ses[1].first;
    int startIndex;
    if (s1 - s0 < round(double(s2 - s1) / 0.7))
    {
        startIndex = 1;
        ss.push_back(pair<int, int>(s2, SWITCH_CLOSE));
    }
    else
    {
        startIndex = 0;
        ss.push_back(pair<int, int>(s1, SWITCH_OPEN));
    }
    for (int i = startIndex; i < ses.size()-1; ++i)
    {
        int s1 = ses[i].first;
        int e1 = ses[i].second;
        int s2 = ses[i+1].first;
        // M : empty area, M : empty area
        double M = e1 - s1;
        double N = s2 - e1;
        if (M<(N*0.7))
        {
            ss.push_back(pair<int, int>(s2, SWITCH_OPEN));
        }
        else
        {
            ss.push_back(pair<int, int>(s2, SWITCH_CLOSE));
        }
    }
}

int sumVpx_(const vector<int> &vpxes, int start, int end)
{
    int r = 0;
    for (int i = start; i < end; ++i)
    {
        r += vpxes[i] * vpxes[i];
    }
    return r;
}

void flagGradle_(const vector<int> &vpxes, vector<pair<int, double> > &ps)
{
    if (vpxes.size() > 0)
    {
        for (int i = 10; i < vpxes.size() - 10; ++i)
        {
            int l = sumVpx(vpxes, i - 10, i);
            int r = sumVpx(vpxes, i, i + 10);
            int a = min(l, r);
            int b = max(l, r);
            double bi = double(b) / a;
            if (bi > 2)
            {
                ps.push_back(pair<int, double>(i, bi));
                i += 10;
            }
        }
    }
}

int helloDrawLine1(const std::string &fp)
{
//    initCorner();

    clock_t t = clock();

    Mat src = imread(fp);
    if (src.empty())
    {
        cout << "Could not load source image " << fp << endl;
        return -1;
    }
    f_iLineWidth = round(10.0 * src.rows / 1080);

    Mat matInrange(src.size(), CV_8UC1);
    check_red_range(src, matInrange);

    FileStorage f1(f_paDeploy + "/tmp/001.mat", FileStorage::WRITE);
    f1 << "dst" << matInrange;

    Scalar scTopLeft = findTopLeft(matInrange);
    Scalar scBottomLeft = findBottomLeft(matInrange);
    Scalar scTopRight = findTopRight(matInrange);
    Scalar scBottomRight = findBottomRight(matInrange);
    // 1 : inter, 2 : outer
    Point pTopLeft1(scTopLeft.val[1], scTopLeft.val[0]), pTopLeft2(scTopLeft.val[3], scTopLeft.val[2]);
    Point pBottomLeft1(scBottomLeft.val[1], scBottomLeft.val[0]), pBottomLeft2(scBottomLeft.val[3], scBottomLeft.val[2]);
    Point pTopRight1(scTopRight.val[1], scTopRight.val[0]), pTopRight2(scTopRight.val[3], scTopRight.val[2]);
    Point pBottomRight1(scBottomRight.val[1], scBottomRight.val[0]), pBottomRight2(scBottomRight.val[3], scBottomRight.val[2]);

//### debug
//    line(src, pTopLeft1, pBottomLeft1, BGR_GREEN);
//    line(src, pTopRight1, pBottomRight1, BGR_GREEN);
    Mat matCanny = getCanny(fp);
    Mat matThreshold(matCanny.size(), CV_8UC1);
    threshold(matCanny, matThreshold, 30.0, 200.0, THRESH_BINARY);

    vector<Scalar> leftCorners = findLeft(matInrange, pTopLeft1, pBottomLeft1);
    vector<Scalar> rightCorners = findRight(matInrange, pTopRight1, pBottomRight1);

//### debug
//    rectangle(src, Point(scTopLeft.val[1], scTopLeft.val[0]), Point(scTopLeft.val[3], scTopLeft.val[2]), BGR_yellow);
//    rectangle(src, Point(scBottomLeft.val[1], scBottomLeft.val[0]), Point(scBottomLeft.val[3], scBottomLeft.val[2]), BGR_yellow);
//    rectangle(src, Point(scTopRight.val[1], scTopRight.val[0]), Point(scTopRight.val[3], scTopRight.val[2]), BGR_yellow);
//    rectangle(src, Point(scBottomRight.val[1], scBottomRight.val[0]), Point(scBottomRight.val[3], scBottomRight.val[2]), BGR_yellow);

//### debug
//    line(src, pTopLeft1, pBottomLeft1, BGR_GREEN);
//    line(src, pBottomLeft1, pBottomRight1, BGR_GREEN);
//    line(src, pBottomRight1, pTopRight1, BGR_GREEN);
//    line(src, pTopRight1, pTopLeft1, BGR_GREEN);
//
//    line(src, pTopLeft2, pBottomLeft2, BGR_GREEN);
//    line(src, pBottomLeft2, pBottomRight2, BGR_GREEN);
//    line(src, pBottomRight2, pTopRight2, BGR_GREEN);
//    line(src, pTopRight2, pTopLeft2, BGR_GREEN);
//
    leftCorners.insert(leftCorners.begin(), scTopLeft);
    rightCorners.insert(rightCorners.begin(), scTopRight);
    leftCorners.push_back(scBottomLeft);
    rightCorners.push_back(scBottomRight);
    if (leftCorners.size() == rightCorners.size())
    {
        for (int i = 0; i < leftCorners.size(); ++i)
        {
            Scalar scl = leftCorners[i];
            Scalar scr = rightCorners[i];
            Point pl1(scl.val[1], scl.val[0]), pl2(scl.val[3], scl.val[2]);
            Point pr1(scr.val[1], scr.val[0]), pr2(scr.val[3], scr.val[2]);
            line(src, pl1, pr1, BGR_GREEN);
            line(src, pl2, pr2, BGR_GREEN);
        }

        Point p1(scTopLeft.val[1], scTopLeft.val[0]);
        Point p2(scTopRight.val[1], scTopRight.val[0]);
        for (int i = 1; i < leftCorners.size(); ++i)
        {
            Scalar scl = leftCorners[i];
            Scalar scr = rightCorners[i];
            Point ptl(p1), ptr(p2);
            p1.x = scl.val[1];
            p1.y = scl.val[0];
            p2.x = scr.val[1];
            p2.y = scr.val[0];
            // pts : Point Top , pbs : Point Bottom
            vector<Point> pts, pbs;
            vector<int> vpxes = getVPxHist(matThreshold, ptl, ptr, p1, p2, pts, pbs);
            if (vpxes.size() > 0 && vpxes.size() == pts.size() && vpxes.size() == pbs.size())
            {
                // [ (Start, End), (Start, End) ... ]
                vector<pair<int, int>> ses;
                flagGradle(vpxes, ses);
                for (int j = 0; j < ses.size(); ++j)
                {
                    line(src, pts[ses[j].first], pbs[ses[j].first], BGR_BLUE);
                    line(src, pts[ses[j].second], pbs[ses[j].second], BGR_RED);
//                    cout << ps[j].first << " = " << ps[j].second << endl;
                }
                // Switch State : [ (index, state), (index, state) ... ]
                vector<pair<int, int>> ss;
                detectiveSwitch(ses, ss);
                for (int j = 0; j < ss.size(); ++j)
                {
                    int index = ss[j].first;
                    int state = ss[j].second;
                    Point pt = pts[index];
                    pt.y += f_iLineWidth * 4;
                    pt.x -= f_iLineWidth * 10;
                    string s = (state == SWITCH_OPEN) ? "O" : "C";
                    putText(src, s, pt, FONT_HERSHEY_SIMPLEX, 1, BGR_BLACK, 2);
                }
                std::ofstream fs(f_paDeploy + "/tmp/hist" + char(30 + i) + ".txt");
                if (!fs.is_open())
                {
                    std::cout << "open file error!" << std::endl;
                }
                else
                {
                    std::stringstream ss1, ss2, ss3, ss4, ss5;
                    for (int k = 0; k < vpxes.size(); ++k)
                    {
                        ss1 << std::setfill('0') << std::setw(4) << vpxes[k] << " ";
                        ss2 << std::setfill('0') << std::setw(4) << pts[k].y << " ";
                        ss3 << std::setfill('0') << std::setw(4) << pts[k].x << " ";
                        ss4 << std::setfill('0') << std::setw(4) << pbs[k].y << " ";
                        ss5 << std::setfill('0') << std::setw(4) << pbs[k].x << " ";
                        lineHist(src, pbs[k], pts[k], vpxes[k]);
                    }
                    fs << ss1.str() << std::endl;
                    fs << ss2.str() << std::endl;
                    fs << ss3.str() << std::endl;
                    fs << ss4.str() << std::endl;
                    fs << ss5.str() << std::endl;
                }
            }
        }
    }

//    vector<Point> pts, pbs;
//    vector<int> vpxes = getVPxHist(matThreshold, pTopLeft1, pTopRight1, pBottomLeft1, pBottomRight1, pts, pbs);
//    if (vpxes.size() > 0 && vpxes.size() == pts.size() && vpxes.size() == pbs.size())
//    {
//        std::ofstream fs(f_paDeploy + "/tmp/hist.txt");
//        if (!fs.is_open())
//        {
//            std::cout << "open file error!" << std::endl;
//        }
//        else
//        {
//            std::stringstream ss1;
//            std::stringstream ss2;
//            std::stringstream ss3;
//            std::stringstream ss4;
//            std::stringstream ss5;
//            for (int i = 0; i < vpxes.size(); ++i)
//            {
//                ss1 << std::setfill('0') << std::setw(4) << vpxes[i] << " ";
//                ss2 << std::setfill('0') << std::setw(4) << pts[i].y << " ";
//                ss3 << std::setfill('0') << std::setw(4) << pts[i].x << " ";
//                ss4 << std::setfill('0') << std::setw(4) << pbs[i].y << " ";
//                ss5 << std::setfill('0') << std::setw(4) << pbs[i].x << " ";
//
//                lineHist(src, pbs[i], pts[i], vpxes[i]);
//            }
//            fs << ss1.str() << std::endl;
//            fs << ss2.str() << std::endl;
//            fs << ss3.str() << std::endl;
//            fs << ss4.str() << std::endl;
//            fs << ss5.str() << std::endl;
//        }
//    }

    t = clock() - t;
    printf ("It took me %lu clicks (%f seconds).\n",t,double(t)/CLOCKS_PER_SEC);

    imshow("src", src);
    imshow("matInrange", matInrange);
    imshow("matCanny", matCanny);
    imshow("matThreshold", matThreshold);

    return 0;
}

void check_color_range(const Mat &in, const Scalar hsv, const Mat &out)
{
    const int thresh = 40;
    Scalar minHSV(hsv.val[0] - thresh, hsv.val[1] - thresh, hsv.val[2] - thresh);
    Scalar maxHSV(hsv.val[0] + thresh, hsv.val[1] + thresh, hsv.val[2] + thresh);
//    Scalar minHSV(0, 230, 230);
//    Scalar maxHSV(25, 255, 255);
    cv::Mat hsv_image;
    cv::cvtColor(in, hsv_image, cv::COLOR_BGR2HSV);
    cv::inRange(hsv_image, minHSV, maxHSV, out);
}

int helloInrange(const std::string &fp)
{
    Mat src = imread(fp);
    if (src.empty())
    {
        cout << "Could not load source image " << fp << endl;
        return -1;
    }

    Mat matInrange(src.size(), CV_8UC1);
    check_color_range(src, bgr2hsv(BGR_SILVER), matInrange);
//    check_color_range(src, Scalar(55, 58.4, 100), matInrange);

    imshow("src", src);
    imshow("helloInrange", matInrange);

    return 0;
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
            *M.ptr<Vec3b>(i, j) = (j % 6 > 2) ? Vec3d(BGR_ORANGE.val) : Vec3d(BGR_GOLD.val);
        }
    }
    imshow("Test", M);   //窗口中显示图像
    return 0;
}

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

//    helloInRange1(f_paDeploy + "/images/switch/a.jpeg");
    helloDrawLine1(f_paDeploy + "/images/switch/c.jpg");
//    helloHist(f_paDeploy + "/images/switch/a.jpeg");
//    helloInrange(f_paDeploy + "/images/switch/a.jpeg");

    waitKey(0);

    destroyAllWindows();
}
