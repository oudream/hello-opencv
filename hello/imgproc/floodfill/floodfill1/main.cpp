
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>


using namespace std;
using namespace cv;


std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;


int helloToImage1(const string & sFilePath)
{
    Mat grHistogram(260, 301, CV_8UC3, Scalar(0, 0, 0));
//    line(grHistrogram,pt1,pt2,Scalar(255,255,255),1,8,0);
//    imwrite()
    return 0;
}

#define w1 400

/// Function headers
void MyEllipse( Mat img, double angle );
void MyFilledCircle( Mat img, Point center );
void MyPolygon( Mat img );
void MyLine( Mat img, Point start, Point end );

/**
 * @function main
 * @brief Main function
 */
int helloDraw1( void )
{

    //![create_images]
    /// Windows names
    char atom_window[] = "Drawing 1: Atom";
    char rook_window[] = "Drawing 2: Rook";

    /// Create black empty images
    Mat atom_image = Mat::zeros(w1, w1, CV_8UC3 );
    Mat rook_image = Mat::zeros(w1, w1, CV_8UC3 );
    //![create_images]

    /// 1. Draw a simple atom:
    /// -----------------------

    //![draw_atom]
    /// 1.a. Creating ellipses
    MyEllipse( atom_image, 90 );
    MyEllipse( atom_image, 0 );
    MyEllipse( atom_image, 45 );
    MyEllipse( atom_image, -45 );

    /// 1.b. Creating circles
    MyFilledCircle( atom_image, Point(w1 / 2, w1 / 2) );
    //![draw_atom]

    /// 2. Draw a rook
    /// ------------------

    //![draw_rook]
    /// 2.a. Create a convex polygon
    MyPolygon( rook_image );

    //![rectangle]
    /// 2.b. Creating rectangles
    rectangle( rook_image,
               Point( 0, 7 * w1 / 8 ),
               Point(w1, w1),
               Scalar( 0, 255, 255 ),
               FILLED,
               LINE_8 );
    //![rectangle]

    /// 2.c. Create a few lines
    MyLine(rook_image, Point( 0, 15 * w1 / 16 ), Point(w1, 15 * w1 / 16 ) );
    MyLine(rook_image, Point(w1 / 4, 7 * w1 / 8 ), Point(w1 / 4, w1 ) );
    MyLine(rook_image, Point(w1 / 2, 7 * w1 / 8 ), Point(w1 / 2, w1 ) );
    MyLine(rook_image, Point(3 * w1 / 4, 7 * w1 / 8 ), Point(3 * w1 / 4, w1 ) );
    //![draw_rook]

    /// 3. Display your stuff!
    imshow( atom_window, atom_image );
    moveWindow( atom_window, 0, 200 );
    imshow( rook_window, rook_image );
    moveWindow(rook_window, w1, 200 );

    waitKey( 0 );
    return(0);
}

/// Function Declaration

/**
 * @function MyEllipse
 * @brief Draw a fixed-size ellipse with different angles
 */
//![my_ellipse]
void MyEllipse( Mat img, double angle )
{
    int thickness = 2;
    int lineType = 8;

    ellipse( img,
             Point(w1 / 2, w1 / 2 ),
             Size(w1 / 4, w1 / 16 ),
             angle,
             0,
             360,
             Scalar( 255, 0, 0 ),
             thickness,
             lineType );
}
//![my_ellipse]

/**
 * @function MyFilledCircle
 * @brief Draw a fixed-size filled circle
 */
//![my_filled_circle]
void MyFilledCircle( Mat img, Point center )
{
    circle(img,
           center,
           w1 / 32,
           Scalar( 0, 0, 255 ),
           FILLED,
           LINE_8 );
}
//![my_filled_circle]

/**
 * @function MyPolygon
 * @brief Draw a simple concave polygon (rook)
 */
//![my_polygon]
void MyPolygon( Mat img )
{
    int lineType = LINE_8;

    /** Create some points */
    Point rook_points[1][20];
    rook_points[0][0]  = Point(w1 / 4, 7 * w1 / 8 );
    rook_points[0][1]  = Point(3 * w1 / 4, 7 * w1 / 8 );
    rook_points[0][2]  = Point(3 * w1 / 4, 13 * w1 / 16 );
    rook_points[0][3]  = Point(11 * w1 / 16, 13 * w1 / 16 );
    rook_points[0][4]  = Point(19 * w1 / 32, 3 * w1 / 8 );
    rook_points[0][5]  = Point(3 * w1 / 4, 3 * w1 / 8 );
    rook_points[0][6]  = Point(3 * w1 / 4, w1 / 8 );
    rook_points[0][7]  = Point(26 * w1 / 40, w1 / 8 );
    rook_points[0][8]  = Point(26 * w1 / 40, w1 / 4 );
    rook_points[0][9]  = Point(22 * w1 / 40, w1 / 4 );
    rook_points[0][10] = Point(22 * w1 / 40, w1 / 8 );
    rook_points[0][11] = Point(18 * w1 / 40, w1 / 8 );
    rook_points[0][12] = Point(18 * w1 / 40, w1 / 4 );
    rook_points[0][13] = Point(14 * w1 / 40, w1 / 4 );
    rook_points[0][14] = Point(14 * w1 / 40, w1 / 8 );
    rook_points[0][15] = Point(w1 / 4, w1 / 8 );
    rook_points[0][16] = Point(w1 / 4, 3 * w1 / 8 );
    rook_points[0][17] = Point(13 * w1 / 32, 3 * w1 / 8 );
    rook_points[0][18] = Point(5 * w1 / 16, 13 * w1 / 16 );
    rook_points[0][19] = Point(w1 / 4, 13 * w1 / 16 );

    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 20 };

    fillPoly( img,
              ppt,
              npt,
              1,
              Scalar( 255, 255, 255 ),
              lineType );
}
//![my_polygon]

/**
 * @function MyLine
 * @brief Draw a simple line
 */
//![my_line]
void MyLine( Mat img, Point start, Point end )
{
    int thickness = 2;
    int lineType = LINE_8;

    line( img,
          start,
          end,
          Scalar( 0, 0, 0 ),
          thickness,
          lineType );
}
//![my_line]


int main(int argc, char *argv[])
{
    f_fpExec = argv[0][0] != '/' ? (argv[0][0] == '.' ? string(getenv("PWD"))+string(argv[0]).substr(1) : string(string(getenv("PWD"))+"/"+string(argv[0]))) : string(argv[0]);
    replace(f_fpExec.begin(), f_fpExec.end(), '\\', '/');
    f_paBin = f_fpExec.find_last_of("/\\") != string::npos ? f_fpExec.substr(0, f_fpExec.find_last_of("/\\")) : string();
    f_paOs = f_paBin.find_last_of("/\\") != string::npos ? f_paBin.substr(0, f_paBin.find_last_of("/\\")) : string();
    f_paDeploy = f_paOs.find_last_of("/\\") != string::npos ? f_paOs.substr(0, f_paOs.find_last_of("/\\")) : string();
    cout << "f_paDeploy: " << f_fpExec << endl;

//    helloCanny1(f_paDeploy + "/images/fruit.jpg");

    helloDraw1();

    return 0;
}