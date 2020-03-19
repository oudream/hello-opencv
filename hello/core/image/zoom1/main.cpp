#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


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

const char* window_name = "Pyramids Demo";
int helloZoom1( const std::string& fp )
{
    /// General instructions
    cout << "\n Zoom In-Out demo \n "
            "------------------  \n"
            " * [i] -> Zoom in   \n"
            " * [o] -> Zoom out  \n"
            " * [ESC] -> Close program \n" << endl;

    // Loads an image
    Mat src = imread( fp );

    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default chicky_512.png] \n");
        return EXIT_FAILURE;
    }
    //![load]

    //![loop]
    for(;;)
    {
        //![show_image]
        imshow( window_name, src );
        //![show_image]
        char c = (char)waitKey(0);

        if( c == 27 )
        { break; }
            //![pyrup]
        else if( c == 'i' )
        { pyrUp( src, src, Size( src.cols*2, src.rows*2 ) );
            printf( "** Zoom In: Image x 2 \n" );
        }
            //![pyrup]
            //![pyrdown]
        else if( c == 'o' )
        { pyrDown( src, src, Size( src.cols/2, src.rows/2 ) );
            printf( "** Zoom Out: Image / 2 \n" );
        }
        //![pyrdown]
    }
    //![loop]

    return EXIT_SUCCESS;
}

int f_zoom2_times=1;
Mat f_zoom2_src2, f_zoom2_src1;

void zoom_trackbar( int , void* )
{
    f_zoom2_src2 = Mat::zeros(f_zoom2_src1.rows * f_zoom2_times, f_zoom2_src1.cols * f_zoom2_times, CV_8UC3);
    for (int i=0; i < f_zoom2_src1.cols ; i++)
    {
        for (int j=0 ; j < f_zoom2_src1.rows ; j++)
        {
            Vec3b color1 = f_zoom2_src1.at<Vec3b>(Point(i, j));
            for(int p=0; p < f_zoom2_times; p++)
            {
                for(int q=0; q < f_zoom2_times; q++)
                {
                    Vec3b color2 = f_zoom2_src2.at<Vec3b>(Point(i, j));
                    color2.val[0] = color1.val[0];
                    color2.val[1] = color1.val[1];
                    color2.val[2] = color1.val[2];

                    f_zoom2_src2.at<Vec3b>(Point(i * f_zoom2_times + p, j * f_zoom2_times + q)) = color2;
                }
            }
        }
    }
    imshow("Scaled Image", f_zoom2_src2);
    cout << "Image Got Processed for Zoom factor=" << f_zoom2_times << endl;
}

int helloZoom2(const std::string& fp)
{
    f_zoom2_src1 = imread(fp);

    if( !f_zoom2_src1.data ) { printf("Error loading src1 \n"); }

    const int zoom_slider_max = 50;

    namedWindow("Scaled Image",WINDOW_AUTOSIZE);
    createTrackbar("Magnify", "Scaled Image", &f_zoom2_times, zoom_slider_max, zoom_trackbar );
    zoom_trackbar(f_zoom2_times, 0 );

    //imwrite("C:\\Users\\arjun\\Desktop\\zoomed.jpg",src2);

    namedWindow("Original Image",WINDOW_AUTOSIZE);
    imshow("Original Image", f_zoom2_src1);

    waitKey(0);
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

    // helloZoom1(f_paDeploy+"/images/p10x10-black-white.png");

    helloZoom2(f_paDeploy+"/images/fruit.jpg");
//    helloZoom2(f_paDeploy+"/images/p10x10-black-white.png");

    return 0;
}

