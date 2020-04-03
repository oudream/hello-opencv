/**
 * @function findContours_Demo.cpp
 * @brief Demo code to find contours in an image
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src_gray;
int thresh = 100;
RNG rng(12345);

std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;

/// Function header
void thresh_callback(int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{
    f_fpExec = argv[0][0] != '/' ? (argv[0][0] == '.' ? std::string(getenv("PWD"))+std::string(argv[0]).substr(1) : std::string(std::string(getenv("PWD"))+"/"+std::string(argv[0]))) : std::string(argv[0]);
    replace(f_fpExec.begin(), f_fpExec.end(), '\\', '/');
    f_paBin = f_fpExec.find_last_of("/\\") != std::string::npos ? f_fpExec.substr(0, f_fpExec.find_last_of("/\\")) : std::string();
    f_paOs = f_paBin.find_last_of("/\\") != std::string::npos ? f_paBin.substr(0, f_paBin.find_last_of("/\\")) : std::string();
    f_paDeploy = f_paOs.find_last_of("/\\") != std::string::npos ? f_paOs.substr(0, f_paOs.find_last_of("/\\")) : std::string();
    std::cout << "f_paDeploy: " << f_fpExec << std::endl;

    /// Load source image
    CommandLineParser parser( argc, argv, "{@input | HappyFish.jpg | input image}" );
//    Mat src = imread( samples::findFile( parser.get<String>( "@input" ) ) );
    Mat src = imread( f_paDeploy + "/images/switch/c.jpg" );
    if( src.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    const char* source_window = "Source";
    namedWindow( source_window );
    imshow( source_window, src );

    const int max_thresh = 255;
    createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );

    waitKey();
    return 0;
}

/**
 * @function thresh_callback
 */
void thresh_callback(int, void* )
{
    /// Detect edges using Canny
    Mat canny_output;
    Canny( src_gray, canny_output, thresh, thresh*2 );

    /// Find contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }

    /// Show in a window
    imshow( "Contours", drawing );
}
