
// https://answers.opencv.org/question/70491/matching-hog-images-with-opencv-in-c/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include "opencv2/ocl/ocl.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat image(imread("R2.jpg",1));
    resize(image, image, Size(64,128) );
    Mat img;
    cvtColor(image, img, CV_RGB2GRAY);

    Mat image2(imread("R2-roi.jpg",1));
    resize(image2, image2, Size(64,128) );
    Mat img2;
    cvtColor(image2, img2, CV_RGB2GRAY);

    vector<float> features;
    vector<Point> locations;
    vector<float> features2;
    vector<Point> locations2;

    HOGDescriptor *hog = new HOGDescriptor();
    HOGDescriptor *hog2 = new HOGDescriptor();

    hog->compute(img,features,Size(32,32), Size(0,0),locations);
    cout<<features.size()<<endl;;

    hog2->compute(img2,features2,Size(32,32), Size(0,0),locations2);
    cout<<features2.size()<<endl;

    Mat Hogfeat;
    Hogfeat.create(features.size(),1,CV_32FC1);
    for(int i=0; i<features.size(); i++)
        Hogfeat.at<float>(i,0)=features.at(i);

    Mat Hogfeat2;
    Hogfeat2.create(features2.size(),1,CV_32FC1);
    for(int i=0; i<features2.size(); i++)
        Hogfeat2.at<float>(i,0)=features2.at(i);

    double distance=0;
    for(int i=0; i<Hogfeat.rows; i++)
    {
        distance+= abs(Hogfeat.at<float>(i,0) - Hogfeat2.at<float>(i,0));
    }
    cout << distance <<endl;

    return 0;
}