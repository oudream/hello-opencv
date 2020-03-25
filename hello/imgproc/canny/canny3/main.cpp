#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

std::string f_fpExec, f_paBin, f_paOs, f_paDeploy;

//![variables]

int lowThreshold = 15;
const int ratio = 3;
const int kernel_size = 3;
//![variables]

/**
 * @function main
 */
Mat helloCanny2( const std::string& fp , const std::string& sWinName)
{
    Mat src, src_gray;
    Mat dst, detected_edges;

    //![load]
    src = imread( fp, IMREAD_COLOR ); // Load an image

    //![create_mat]
    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );
    //![create_mat]

    //![convert_to_gray]
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    //![convert_to_gray]
    //![reduce_noise]
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );
    //![reduce_noise]

    //![canny]
    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold * ::ratio, kernel_size );
    //![canny]

    /// Using Canny's output as a mask, we display our result
    //![fill]
    dst = Scalar::all(0);
    //![fill]

    //![copyto]
    src.copyTo( dst, detected_edges);
    //![copyto]

    cout << dst.size << endl;
    cout << dst.type() << endl;
    cout << dst.depth() << endl;
    cout << dst.total() << endl;
    cout << dst.elemSize() << endl;
    cout << dst.elemSize1() << endl;
    cout << dst.depth() << endl;
    cout << dst.channels() << endl;

    //![display]
    imshow( sWinName, dst );
    //![display]

    return dst;
}

int main(int argc, char *argv[])
{
    f_fpExec = argv[0][0] != '/' ? (argv[0][0] == '.' ? string(getenv("PWD"))+string(argv[0]).substr(1) : string(string(getenv("PWD"))+"/"+string(argv[0]))) : string(argv[0]);
    replace(f_fpExec.begin(), f_fpExec.end(), '\\', '/');
    f_paBin = f_fpExec.find_last_of("/\\") != string::npos ? f_fpExec.substr(0, f_fpExec.find_last_of("/\\")) : string();
    f_paOs = f_paBin.find_last_of("/\\") != string::npos ? f_paBin.substr(0, f_paBin.find_last_of("/\\")) : string();
    f_paDeploy = f_paOs.find_last_of("/\\") != string::npos ? f_paOs.substr(0, f_paOs.find_last_of("/\\")) : string();
    cout << "f_paDeploy: " << f_fpExec << endl;

    Mat canny1 = helloCanny2(f_paDeploy + "/images/switch/a.jpeg", "switch1");
    Mat canny2 = helloCanny2(f_paDeploy + "/images/switch/a-hook-000001.png", "switch-hook-000001");

    FileStorage f1(f_paDeploy + "/tmp/001.mat", FileStorage::WRITE);
    f1 << "canny1" << canny1;

    FileStorage f2(f_paDeploy + "/tmp/002.mat", FileStorage::WRITE);
    f1 << "canny2" << canny2;

    imshow("canny1", canny1);
    imshow("canny2", canny2);

    /// Wait until user exit program by pressing a key
    waitKey(0);

    return 0;
}