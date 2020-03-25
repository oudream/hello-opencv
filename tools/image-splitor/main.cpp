
#include <opencv2/opencv.hpp>
#include <iostream>

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

static const cv::Scalar cs_color_black = cv::Scalar(0, 0, 0);
static const cv::Scalar cs_color_green = cv::Scalar(0, 255, 0);
static const cv::Scalar cs_color_blue = cv::Scalar(255, 0, 0);
static const cv::Scalar cs_color_cyan = cv::Scalar(255, 255, 0);
static const cv::Scalar cs_color_red = cv::Scalar(0, 0, 255);
static const cv::Scalar cs_color_yellow = cv::Scalar(0, 255, 255);
static const cv::Scalar cs_color_magenta = cv::Scalar(255, 0, 255);
static const cv::Scalar cs_color_white = cv::Scalar(255, 255, 255);
static const cv::Scalar cs_color_gray = cv::Scalar(128, 128, 128);
static const cv::Scalar cs_color_mlab = cv::Scalar(255, 128, 128);
static const cv::Scalar cs_color_navy = cv::Scalar(0, 0, 128);
static const cv::Scalar cs_color_olive = cv::Scalar(0, 128, 128);
static const cv::Scalar cs_color_maroon = cv::Scalar(0, 0, 128);
static const cv::Scalar cs_color_teal = cv::Scalar(128, 128, 0);
static const cv::Scalar cs_color_rose = cv::Scalar(128, 0, 255);
static const cv::Scalar cs_color_azure = cv::Scalar(255, 128, 0);
static const cv::Scalar cs_color_lime = cv::Scalar(0, 255, 191);
static const cv::Scalar cs_color_gold = cv::Scalar(0, 215, 255);
static const cv::Scalar cs_color_brown = cv::Scalar(42, 42, 165);
static const cv::Scalar cs_color_orange = cv::Scalar(0, 165, 255);
static const cv::Scalar cs_color_chartreuse = cv::Scalar(0, 255, 128);
static const cv::Scalar cs_color_orange_red = cv::Scalar(0, 69, 255);
static const cv::Scalar cs_color_purple = cv::Scalar(128, 0, 128);
static const cv::Scalar cs_color_indigo = cv::Scalar(130, 0, 75);
static const cv::Scalar cs_color_pink = cv::Scalar(203, 192, 255);
static const cv::Scalar cs_color_cherry = cv::Scalar(99, 29, 222);
static const cv::Scalar cs_color_bluberry = cv::Scalar(247, 134, 79);
static const cv::Scalar cs_color_raspberry = cv::Scalar(92, 11, 227);
static const cv::Scalar cs_color_silver = cv::Scalar(192, 192, 192);
static const cv::Scalar cs_color_violet = cv::Scalar(226, 43, 138);
static const cv::Scalar cs_color_apricot = cv::Scalar(177, 206, 251);
static const cv::Scalar cs_color_turquoise = cv::Scalar(208, 224, 64);
static const cv::Scalar cs_color_celestial_blue = cv::Scalar(208, 151, 73);
static const cv::Scalar cs_color_amethyst = cv::Scalar(204, 102, 153);
static const cv::Scalar cs_color_not_set = cv::Scalar(-1, -1, -1);

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

//### var
std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;
//
int f_iLineWidth = 10;

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
#define GX(y) round(double(p2.x - p1.x)/(p2.y - p1.y)*(y-p1.y)+p1.x)
    bool bv = abs(p1.x - p2.x) < 3;
    int ySkip = f_iLineWidth * 2;
    for (int y = p1.y + ySkip; y < p2.y - ySkip; ++y)
    {
        int x0 = bv ? p1.x : GX(y);
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
#define GX(y) round(double(p2.x - p1.x)/(p2.y - p1.y)*(y-p1.y)+p1.x)
    bool bv = abs(p1.x - p2.x) < 3;
    int ySkip = f_iLineWidth * 2;
    for (int y = p1.y + ySkip; y < p2.y - ySkip; ++y)
    {
        int x0 = bv ? p1.x : GX(y);
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

Mat getCanny( const std::string& fp)
{
    Mat src, src_gray;
    Mat dst, detected_edges;

    src = imread( fp, IMREAD_COLOR );
    dst.create( src.size(), src.type() );
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    blur( src_gray, detected_edges, Size(3,3) );
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold * ::ratio, kernel_size );
    dst = Scalar::all(0);
    src.copyTo( dst, detected_edges);

    return dst;
}

int helloDrawLine1(const std::string &fp)
{
//    initCorner();

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
//    line(src, pTopLeft1, pBottomLeft1, cs_color_green);
//    line(src, pTopRight1, pBottomRight1, cs_color_green);
    Mat matCanny = getCanny(fp);
    Mat matThreshold(matCanny.size(), CV_8UC1);
    threshold(matCanny, matThreshold, 30.0, 200.0, THRESH_BINARY);

    vector<Scalar> leftCorners = findLeft(matInrange, pTopLeft1, pBottomLeft1);
    vector<Scalar> rightCorners = findRight(matInrange, pTopRight1, pBottomRight1);

//### debug
//    rectangle(src, Point(scTopLeft.val[1], scTopLeft.val[0]), Point(scTopLeft.val[3], scTopLeft.val[2]), cs_color_yellow);
//    rectangle(src, Point(scBottomLeft.val[1], scBottomLeft.val[0]), Point(scBottomLeft.val[3], scBottomLeft.val[2]), cs_color_yellow);
//    rectangle(src, Point(scTopRight.val[1], scTopRight.val[0]), Point(scTopRight.val[3], scTopRight.val[2]), cs_color_yellow);
//    rectangle(src, Point(scBottomRight.val[1], scBottomRight.val[0]), Point(scBottomRight.val[3], scBottomRight.val[2]), cs_color_yellow);

//### debug
//    line(src, pTopLeft1, pBottomLeft1, cs_color_green);
//    line(src, pBottomLeft1, pBottomRight1, cs_color_green);
//    line(src, pBottomRight1, pTopRight1, cs_color_green);
//    line(src, pTopRight1, pTopLeft1, cs_color_green);
//
//    line(src, pTopLeft2, pBottomLeft2, cs_color_green);
//    line(src, pBottomLeft2, pBottomRight2, cs_color_green);
//    line(src, pBottomRight2, pTopRight2, cs_color_green);
//    line(src, pTopRight2, pTopLeft2, cs_color_green);
//
    if (leftCorners.size() == rightCorners.size())
    {
        for (int i = 0; i < leftCorners.size(); ++i)
        {
            Scalar scl = leftCorners[i];
            Scalar scr = rightCorners[i];
            Point pl1(scl.val[1], scl.val[0]), pl2(scl.val[3], scl.val[2]);
            Point pr1(scr.val[1], scr.val[0]), pr2(scr.val[3], scr.val[2]);
            line(src, pl1, pr1, cs_color_green);
            line(src, pl2, pr2, cs_color_green);
        }
    }
    imshow("src", src);
    imshow("matInrange", matInrange);
    imshow("matCanny", matCanny);
    imshow("matThreshold", matThreshold);

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
    helloDrawLine1(f_paDeploy + "/images/switch/a.jpeg");

    waitKey(0);

    destroyAllWindows();
}
