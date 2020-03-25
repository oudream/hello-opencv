#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"


using namespace std;
using namespace cv;


std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;

//! [declare]
/// Global Variables
bool use_mask;
Mat img; Mat templ; Mat mask; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;
//! [declare]


/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
    //! [copy_source]
    /// Source image to display
    Mat img_display;
    img.copyTo( img_display );
    //! [copy_source]

    //! [create_result_matrix]
    /// Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create( result_rows, result_cols, CV_32FC1 );
    //! [create_result_matrix]

    //! [match_template]
    /// Do the Matching and Normalize
    bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);
    if (use_mask && method_accepts_mask)
    { matchTemplate( img, templ, result, match_method, mask); }
    else
    { matchTemplate( img, templ, result, match_method); }
    //! [match_template]

    //! [normalize]
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    //! [normalize]

    //! [best_match]
    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    //! [best_match]

    //! [match_loc]
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
    else
    { matchLoc = maxLoc; }
    //! [match_loc]

    //! [imshow]
    /// Show me what you got
    rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

    imshow( image_window, img_display );
    imshow( result_window, result );
    //! [imshow]

    return;
}

/**
 * @function main
 */
int helloTemplate1( int argc, char** argv )
{
    string fpImg = f_paDeploy + "/images/switch1.jpeg";
    string fpTemp = f_paDeploy + "/images/switch-single-000001.png";
    if (argc>1)
    {
        if (argv[1][0] == '2')
            fpTemp = f_paDeploy + "/images/switch-single-000002.png";
        else if (argv[1][0] == '3')
            fpTemp = f_paDeploy + "/images/switch-single-000003.png";
        else if (argv[1][0] == '4')
            fpTemp = f_paDeploy + "/images/switch-single-000004.png";
    }

    //! [load_image]
    /// Load image and template
    img = imread( fpImg, IMREAD_COLOR );
    templ = imread( fpTemp, IMREAD_COLOR );

    if(argc > 3) {
        use_mask = true;
        mask = imread( argv[3], IMREAD_COLOR );
    }

    if(img.empty() || templ.empty() || (use_mask && mask.empty()))
    {
        cout << "Can't read one of the images" << endl;
        return EXIT_FAILURE;
    }
    //! [load_image]

    //! [create_windows]
    /// Create windows
    namedWindow( image_window, WINDOW_AUTOSIZE );
    namedWindow( result_window, WINDOW_AUTOSIZE );
    //! [create_windows]

    //! [create_trackbar]
    /// Create Trackbar
    const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );
    //! [create_trackbar]

    MatchingMethod( 0, 0 );

    //! [wait_key]
    waitKey(0);
    return EXIT_SUCCESS;
    //! [wait_key]
}

int main(int argc, char *argv[])
{
    f_fpExec = argv[0][0] != '/' ? (argv[0][0] == '.' ? string(getenv("PWD"))+string(argv[0]).substr(1) : string(string(getenv("PWD"))+"/"+string(argv[0]))) : string(argv[0]);
    replace(f_fpExec.begin(), f_fpExec.end(), '\\', '/');
    f_paBin = f_fpExec.find_last_of("/\\") != string::npos ? f_fpExec.substr(0, f_fpExec.find_last_of("/\\")) : string();
    f_paOs = f_paBin.find_last_of("/\\") != string::npos ? f_paBin.substr(0, f_paBin.find_last_of("/\\")) : string();
    f_paDeploy = f_paOs.find_last_of("/\\") != string::npos ? f_paOs.substr(0, f_paOs.find_last_of("/\\")) : string();
    cout << "f_paDeploy: " << f_fpExec << endl;

//    helloCanny1(f_paDeploy + "/images/fruit.jpg");

    helloTemplate1(argc, argv);

    return 0;
}