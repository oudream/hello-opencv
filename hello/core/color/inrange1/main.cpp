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

void processFrame(Mat &binary, Rect &rect)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hireachy;
    findContours(binary, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
    if (contours.size() > 0)
    {
        double maxArea = 0.0;
        for (size_t t = 0; t < contours.size(); t++)
        {
            double area = contourArea(contours[static_cast<int>(t)]);
            if (area > maxArea)
            {
                maxArea = area;
                rect = boundingRect(contours[static_cast<int>(t)]);
            }
        }
    }
    else
    {
        rect.x = rect.y = rect.width = rect.height = 0;
    }

}

int helloInRange1(const std::string &fpVideo)
{
    // load video
    VideoCapture capture;
    capture.open(fpVideo);
    if (!capture.isOpened())
    {
        printf("could not find video file");
        return -1;
    }

    Mat frame, mask;
    Mat kernel1 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    Mat kernel2 = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

    namedWindow("input video", WINDOW_AUTOSIZE);
    namedWindow("track mask", WINDOW_AUTOSIZE);
    double time0, time1 = 0;

    int Count = 0;
    Rect roi;
    while (capture.read(frame))
    {
        Count++;
        time0 = getTickCount();

        // inRange(frame, Scalar(37, 43, 46), Scalar(77, 255, 255), mask); // 过滤
        inRange(frame, Scalar(0, 127, 0), Scalar(120, 255, 120), mask); // 过滤
        morphologyEx(mask, mask, MORPH_OPEN, kernel1, Point(-1, -1), 1); // 开操作
        dilate(mask, mask, kernel2, Point(-1, -1), 4);// 膨胀
        imshow("track mask", mask);

        processFrame(mask, roi); // 轮廓发现与位置标定
        rectangle(frame, roi, Scalar(0, 0, 255), 3, 8, 0);
        imshow("input video", frame);
        printf("第 %d 次的时间是%lf\n", Count, (getTickCount() - time0) / getTickFrequency());
        time1 += (getTickCount() - time0) / getTickFrequency();
        // trigger exit
        char c = waitKey(1);
        if (c == 27)
        {
            break;
        }
        if (Count == 361)
            break;
    }

    cout << 1.0 * Count / time1 << '\n';
    printf("%lf\n\n", time1);

    capture.release();
    return 0;
}

int helloInRange2(const std::string &fpInVideo, const std::string &fpOutVideo)
{
    // load video
    VideoCapture capture;
    capture.open(fpInVideo);
    if (!capture.isOpened())
    {
        printf("could not find video file");
        return -1;
    }

    namedWindow("video", WINDOW_AUTOSIZE);
    namedWindow("mask", WINDOW_AUTOSIZE);

    int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
    int frame_fps = capture.get(CAP_PROP_FPS);
    VideoWriter video(fpOutVideo, VideoWriter::fourcc('M', 'J', 'P', 'G'), frame_fps, Size(frame_width, frame_height));
    int iCount = 0;
    Mat frame, mask;
    while (1)
    {
        Mat maskImg, hsvImg;
        if (capture.read(frame))
        {
            cvtColor(frame, hsvImg, COLOR_RGB2HSV);
            inRange(hsvImg, Scalar(35, 43, 46), Scalar(77, 255, 255), mask); // 过滤
            stringstream ss1;
            ss1 << f_paDeploy << "/tmp/org-" << iCount << ".jpg";
            imwrite(ss1.str(), frame);
            bitwise_and(frame, frame, maskImg, mask);
            video.write(maskImg);
            stringstream ss2;
            ss2 << f_paDeploy << "/tmp/" << iCount++ << ".jpg";
            imwrite(ss2.str(), maskImg);
        }
        else
        {
            break;
        }
    }
    video.release();
    capture.release();
    return 0;
}

int helloInRange3()
{
    for (int i = 50; i < 150; ++i)
    {
        stringstream ss1;
        ss1 << f_paDeploy << "/tmp/org-"<< i << ".jpg";
        stringstream ss2;
        ss2 << f_paDeploy << "/tmp/img-"<< i << ".jpg";
        Mat frame, hsvImg, mask, maskImg;
        frame = imread(ss1.str());
        cvtColor(frame, hsvImg, COLOR_RGB2HSV);
        inRange(hsvImg, Scalar(35, 43, 46), Scalar(77, 255, 255), mask); // 过滤
        bitwise_and(frame, frame, maskImg, mask);
        imwrite(ss2.str(), maskImg);
    }
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

//    helloInRange1(f_paDeploy + "/videos/video_006.mp4");
    helloInRange2(f_paDeploy + "/videos/video_006.mp4", f_paDeploy + "/videos/video_006-.avi");
//    helloInRange3();
    // Closes all the windows
    destroyAllWindows();
}
