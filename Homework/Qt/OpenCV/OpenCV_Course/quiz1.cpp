//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//int main()
//{
////    // p1q1
////    Mat source = imread("sample.jpg");
////    imshow("img", source);

////    // p2q9a
////    Mat img = imread("sample.jpg");

////    imshow("image", img);
////    int k = waitKey(25);
////    cout << k;

////    // p2q11
////    Mat image = imread("p3q11.png", 1);
////    // Convert to RGB
////    Mat imageRGB;
////    cvtColor(image, imageRGB, COLOR_BGR2RGB);
////    // Add 200 to image
////    add(imageRGB,200,imageRGB);

////    cvtColor(imageRGB, image, COLOR_RGB2BGR);

////    imshow("image", image);
////    waitKey(0);

//    // p4q13
//    Mat im = imread("p4q13a.png", 0);

//    SimpleBlobDetector::Params params;

//    // Filter by Area.
//    params.filterByArea = false;

//    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
//    std::vector<KeyPoint> keypoints;
//    detector->detect( im, keypoints );

//    int x,y;
//    int radius;
//    double diameter;
//    cvtColor(im, im, COLOR_GRAY2BGR);
//    for (int i=0; i < keypoints.size(); i++){
//        KeyPoint k = keypoints[i];
//        Point keyPt;
//        keyPt = k.pt;
//        x=(int)keyPt.x;
//        y=(int)keyPt.y;
//        // Mark center in BLACK
//        circle(im,Point(x,y),5,Scalar(255,0,0),-1);
//        // Get radius of coin
//        diameter = k.size;
//        radius = (int)diameter/2.0;
//        // Mark blob in GREEN
//        circle(im, Point(x,y),radius,Scalar(0,255,0),2);
//    }

//    imshow("image", im);
//    waitKey(0);

//    std::cout << "#Blobs = " << keypoints.size() << std::endl;


//    return 0;
//}
