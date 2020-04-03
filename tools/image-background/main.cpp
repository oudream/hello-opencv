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

void check_background_range(const Mat &in, const Mat &out)
{
    cv::Mat hsv_image;
    cv::cvtColor(in, hsv_image, cv::COLOR_BGR2HSV);
    cv::inRange(hsv_image, YELLOW_LOW, YELLOW_HIGH, out);
}

int helloBackground1(const std::string &fp)
{
    clock_t t = clock();

    Mat src = imread(fp);
    if (src.empty())
    {
        cout << "Could not load source image " << fp << endl;
        return -1;
    }

    t = clock() - t;
    printf("It took me %lu clicks (%f seconds).\n", t, double(t) / CLOCKS_PER_SEC);

    imshow("src", src);

    return 0;
}

//组装样本数据
Mat HandleImgData(Mat &img)
{
    int width = img.cols;
    int height = img.rows;
    int count1 = width * height;
    int channels1 = img.channels();

    Mat points(count1, channels1, CV_32F, Scalar(10));
    int index = 0;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            index = row * width + col;
            Vec3b bgr = img.at<Vec3b>(row, col);
            points.at<float>(index, 0) = static_cast<int>(bgr[0]);
            points.at<float>(index, 1) = static_cast<int>(bgr[1]);
            points.at<float>(index, 2) = static_cast<int>(bgr[2]);

        }

    }
    return points;
}

/*
图片背景替换
知识点：分水岭分割、高斯模糊
处理步骤：数据组装-KMeans分割-背景消除-生成遮罩-模糊-输出
*/
int helloBackground2(const std::string &fp)
{
    clock_t t = clock();

    Mat img1 = imread(fp);
    if (img1.empty())
    {
        cout << "Could not load source image " << fp << endl;
        return -1;
    }

    char win1[] = "window1";
    char win2[] = "window2";
    char win3[] = "window3";
    char win4[] = "window4";
    char win5[] = "window5";
    char win6[] = "window6";
    namedWindow(win1, WINDOW_AUTOSIZE);//创建窗口 win1
    namedWindow(win2, WINDOW_AUTOSIZE);//创建窗口 win2
    namedWindow(win3, WINDOW_AUTOSIZE);//创建窗口 win3
    namedWindow(win4, WINDOW_AUTOSIZE);//创建窗口 win4
    namedWindow(win5, WINDOW_AUTOSIZE);//创建窗口 win5
    namedWindow(win6, WINDOW_AUTOSIZE);//创建窗口 win6

    Mat img2 = img1.clone();
    //显示原始图片
    imshow(win1, img1);
    //组装数据
    Mat points = HandleImgData(img1);

    //Kmeans处理
    int numCluster = 3;
    Mat labels;
    Mat centers;
    TermCriteria termCriteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);

    kmeans(points, numCluster, labels, termCriteria, 3, KMEANS_PP_CENTERS, centers);
    //遮罩
    Mat mask = Mat::zeros(img1.size(), CV_8UC1);
    int index = img1.rows * 2 + 2;
    int cindex = labels.at<int>(index, 0);//背景设置为0
    int height = img1.rows;
    int width = img1.cols;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            index = row * width + col;
            int label = labels.at<int>(index, 0);
            if (label == cindex)
            {
                img2.at<Vec3b>(row, col)[0] = 0;
                img2.at<Vec3b>(row, col)[1] = 0;
                img2.at<Vec3b>(row, col)[2] = 0;
                mask.at<uchar>(row, col) = 0;
            }
            else
            {
                mask.at<uchar>(row, col) = 255;
            }
        }
    }

    //腐蚀
    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    erode(mask, mask, k);
    imshow(win4, mask);

    //高斯模糊
    GaussianBlur(mask, mask, Size(3, 3), 0, 0);
    imshow(win5, mask);

    //通道混合
    RNG rng(12345);
    Vec3b color;
    color[0] = rng.uniform(0, 255);
    color[1] = rng.uniform(0, 255);
    color[2] = rng.uniform(0, 255);
    Mat result(img1.size(), img1.type());

    double d1 = 0.0;
    int r = 0, g = 0, b = 0;
    int r1 = 0, g1 = 0, b1 = 0;
    int r2 = 0, g2 = 0, b2 = 0;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int m = mask.at<uchar>(row, col);
            if (m == 255)
            {
                result.at<Vec3b>(row, col) = img1.at<Vec3b>(row, col);//前景
            }
            else if (m == 0)
            {
                result.at<Vec3b>(row, col) = color;//背景
            }
            else
            {
                d1 = m / 255.0;
                b1 = img1.at<Vec3b>(row, col)[0];
                g1 = img1.at<Vec3b>(row, col)[1];
                r1 = img1.at<Vec3b>(row, col)[2];

                b2 = color[0];
                g2 = color[1];
                r2 = color[2];

                b = b1 * d1 + b2 * (1.0 - d1);
                g = g1 * d1 + g2 * (1.0 - d1);
                r = r1 * d1 + r2 * (1.0 - d1);

                result.at<Vec3b>(row, col)[0] = b;
                result.at<Vec3b>(row, col)[1] = g;
                result.at<Vec3b>(row, col)[2] = r;
            }
        }
    }

    //输出
    imshow(win2, mask);
    imshow(win3, img2);
    imshow(win6, result);
    //保存处理后的图片
    imwrite("result-2.jpg", result);

    t = clock() - t;
    printf("It took me %lu clicks (%f seconds).\n", t, double(t) / CLOCKS_PER_SEC);

    imshow("img1", img1);

    return 0;
}

double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 ) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// https://stackoverflow.com/questions/8667818/opencv-c-obj-c-detecting-a-sheet-of-paper-square-detection
// Detecting a sheet of paper / Square Detection
void find_squares(Mat& image, vector<vector<Point> >& squares)
{
    // blur will enhance edge detection
    Mat blurred(image);
    medianBlur(image, blurred, 9);

    Mat gray0(blurred.size(), CV_8U), gray;
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for (int c = 0; c < 3; c++)
    {
        int ch[] = {c, 0};
        mixChannels(&blurred, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        const int threshold_level = 2;
        for (int l = 0; l < threshold_level; l++)
        {
            // Use Canny instead of zero threshold level!
            // Canny helps to catch squares with gradient shading
            if (l == 0)
            {
                Canny(gray0, gray, 10, 20, 3); //

                // Dilate helps to remove potential holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                gray = gray0 >= (l+1) * 255 / threshold_level;
            }

            // Find contours and store them in a list
            findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

            // Test contours
            vector<Point> approx;
            for (size_t i = 0; i < contours.size(); i++)
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if (approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)))
                {
                    double maxCosine = 0;

                    for (int j = 2; j < 5; j++)
                    {
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    if (maxCosine < 0.3)
                        squares.push_back(approx);
                }
            }
        }
    }
}

//
int helloFindSquares(const std::string &fp)
{
    clock_t t = clock();

    Mat img1 = imread(fp);
    if (img1.empty())
    {
        cout << "Could not load source image " << fp << endl;
        return -1;
    }

    vector<vector<Point> > squares;
    find_squares(img1, squares);

    t = clock() - t;
    printf ("It took me %lu clicks (%f seconds).\n",t,double(t)/CLOCKS_PER_SEC);
}

// Image Segmentation with Distance Transform and Watershed Algorithm
int helloSegmentation1(const std::string& pf1)
{
    // Load the image
    Mat src = imread( pf1 );
    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        return -1;
    }
    // Show source image
    imshow("Source Image", src);
    // Change the background from white to black, since that will help later to extract
    // better results during the use of Distance Transform
    for ( int i = 0; i < src.rows; i++ ) {
        for ( int j = 0; j < src.cols; j++ ) {
            if ( src.at<Vec3b>(i, j) == Vec3b(255,255,255) )
            {
                src.at<Vec3b>(i, j)[0] = 0;
                src.at<Vec3b>(i, j)[1] = 0;
                src.at<Vec3b>(i, j)[2] = 0;
            }
        }
    }
    // Show output image
    imshow("Black Background Image", src);
    // Create a kernel that we will use to sharpen our image
    Mat kernel = (Mat_<float>(3,3) <<
                                   1,  1, 1,
        1, -8, 1,
        1,  1, 1); // an approximation of second derivative, a quite strong kernel
    // do the laplacian filtering as it is
    // well, we need to convert everything in something more deeper then CV_8U
    // because the kernel has some negative values,
    // and we can expect in general to have a Laplacian image with negative values
    // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
    // so the possible negative number will be truncated
    Mat imgLaplacian;
    filter2D(src, imgLaplacian, CV_32F, kernel);
    Mat sharp;
    src.convertTo(sharp, CV_32F);
    Mat imgResult = sharp - imgLaplacian;
    // convert back to 8bits gray scale
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
    // imshow( "Laplace Filtered Image", imgLaplacian );
    imshow( "New Sharped Image", imgResult );
    // Create binary image from source image
    Mat bw;
    cvtColor(imgResult, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("Binary Image", bw);
    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);
    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);
    imshow("Distance Transform Image", dist);
    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects
    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);
    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, kernel1);
    imshow("Peaks", dist);
    // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);
    // Find total markers
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32S);
    // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i)+1), -1);
    }
    // Draw the background marker
    circle(markers, Point(5,5), 3, Scalar(255), -1);
//    imshow("Markers", markers*10000);
//    imshow("Markers", markers);
    // Perform the watershed algorithm
    watershed(imgResult, markers);
    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);
    //    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
    // image looks like at that point
    // Generate random colors
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }
    // Create the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
    // Fill labeled objects with random colors
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
            {
                dst.at<Vec3b>(i,j) = colors[index-1];
            }
        }
    }
    // Visualize the final image
    imshow("Final Result", dst);
    waitKey();
    return 0;
}

int helloBackground3(const std::string& pf)
{
    clock_t t = clock();

    Mat img1 = imread(pf);
    if (img1.empty())
    {
        cout << "Could not load source image " << pf << endl;
        return -1;
    }

    Mat img2(img1.size(), img1.type());
    blur(img1, img2, Size(3, 3));

    vector<Vec3b> crs;
    int crsum[256] = {0};
    for (int i = 0; i < img2.rows; ++i)
    {
        for (int j = 0; j < img2.cols; ++j)
        {
            Vec3b * px = img2.ptr<Vec3b>(i, j);
        }
    }

    imshow("img1", img1);
    imshow("img2",img2);

    t = clock() - t;
    printf ("It took me %lu clicks (%f seconds).\n",t,double(t)/CLOCKS_PER_SEC);
}



int Threshold_Value = 50;
double g_Area = 0;

RNG rng(12345);

Mat input_image, threshold_image, output_image, Middle_image;


void Threshold_Image_Bar(int, void *)
{
    threshold(Middle_image, threshold_image, 90, 255, 3);
    Canny(threshold_image, threshold_image, Threshold_Value, Threshold_Value * 3);
    imshow("Threshold Image", threshold_image);

    vector<vector<Point>> contours;
    vector<Vec4i> hireachy;
    findContours(threshold_image, contours, hireachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(-1, -1));
    char flag_count = 0;
    Mat Show_threImage = Mat::zeros(threshold_image.size(), CV_8UC3);
    RotatedRect MinRect;
    for (size_t i = 0; i < contours.size(); i++)
    {
        const Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(Show_threImage, contours, static_cast<int>(i), color, 2, 8, hireachy, 0, Point());
        //----利用面积进行判断是否为最大区域------//
        double area = contourArea(contours[i]);
        g_Area = g_Area > area ? g_Area : area;
        flag_count = (area == g_Area) ? static_cast<int>(i) : flag_count;//记录最大边界
    }
    imshow("Draw_Image_Contours", Show_threImage);

    Mat gray, Change_image = Mat::zeros(input_image.size(), input_image.type());
    gray.create(input_image.size(), input_image.type());
    drawContours(gray, contours, flag_count, Scalar(255, 255, 255), 2, 8, hireachy, 0, Point());
    Rect s = boundingRect(contours[flag_count]);//为了找内部的一个种子点，自己随便定义也可以
    floodFill(gray, Point(s.x + s.width / 2, s.y + s.height / 2), Scalar(255, 255, 255));//黑色区域变成白色，遇到白色区域停止
    imshow("123", gray);
    bitwise_and(input_image, gray, gray);
    imshow("wjy", gray);
}

// 不规则ROI的提取
// https://www.cnblogs.com/my-c-world/p/7650367.html
int helloROI1(const std::string& fp)
{
    input_image = imread(fp );
    if (input_image.data == NULL) {
        return -1; cout << "can't open image.../";
    }
    imshow("Sourse Image", input_image);
    blur(input_image, Middle_image, Size(3, 3), Point(-1, -1), 4);
    imshow("Blur Image", Middle_image);
    cvtColor(Middle_image, Middle_image, COLOR_RGB2GRAY);
    imshow("Gray Image", Middle_image);
    namedWindow("Threshold Image", 1);
    createTrackbar("阈值调整", "Threshold Image", &Threshold_Value, 255, Threshold_Image_Bar);
    Threshold_Image_Bar(0, 0);
    waitKey(0);
    return 0;
}




int blur_Threshold_Value = 3;
Mat blur_img_src, blur_img_target;

void blur_Threshold_Image_Bar(int, void *)
{
    blur(blur_img_src, blur_img_target, Size(blur_Threshold_Value, blur_Threshold_Value), Point(-1, -1), 4);
    imshow("Blur Image", blur_img_target);
}

// 不规则ROI的提取
// https://www.cnblogs.com/my-c-world/p/7650367.html
int helloBlur1(const std::string& fp)
{
    blur_img_src = imread( fp );
    if (blur_img_src.data == NULL) {
        return -1; cout << "can't open image.../";
    }
    imshow("Sourse Image", blur_img_src);
    namedWindow("Blur Image", 1);
    createTrackbar("阈值调整", "Blur Image", &blur_Threshold_Value, 100, blur_Threshold_Image_Bar);
    blur_Threshold_Image_Bar(0, 0);
    waitKey(0);
    return 0;
}

void helloSegmentation2(const std::string& fp)
{
    Mat src = imread(fp); // "E://bird.jpg"
    Rect rect(84, 84, 406, 318);//左上坐标（X,Y）和长宽
    Mat result, bg, fg;

    grabCut(src, result, rect, bg, fg, 1, GC_INIT_WITH_RECT);
    imshow("grab", result);
    /*threshold(result, result, 2, 255, CV_THRESH_BINARY);
    imshow("threshold", result);*/

    compare(result, GC_PR_FGD, result, CMP_EQ);//result和GC_PR_FGD对应像素相等时，目标图像该像素值置为255
    imshow("result",result);
    Mat foreground(src.size(), CV_8UC3, Scalar(255, 255, 255));
    src.copyTo(foreground, result);//copyTo有两种形式，此形式表示result为mask
    imshow("foreground", foreground);
    waitKey(0);
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

    string fpa = f_paDeploy + "/images/switch/a.jpeg";
    string fpc = f_paDeploy + "/images/switch/c.jpg";
    string fpDraw1 = f_paDeploy + "/images/draw1.jpg";
    string fpCards = f_paDeploy + "/data/cards.png";

    // 知识点：分水岭分割、高斯模糊
//    helloBackground2(f_paDeploy + "/images/switch/c.jpg");

    // 识别边框 Detecting a sheet of paper / Square Detection
//    helloFindSquares(pc);

    // Segmentation
//    helloSegmentation1(f_paDeploy + "/images/switch/c.jpg");

    // 直方图预测背景色
//    helloBackground3(pc);

    // 不规则ROI的提取
//    helloROI1(fpDraw1);

    //
//    helloBlur1(fpa);

    //
    helloSegmentation2(fpc);

    waitKey(0);

    destroyAllWindows();
}
