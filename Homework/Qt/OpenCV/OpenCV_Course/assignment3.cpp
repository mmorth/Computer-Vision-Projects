//#include <iostream>
//#include <string>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>

//using namespace std;
//using namespace cv;

//// Set the parameters for the trackbars
//int maxScaleUp = 100;
//int scaleFactor = 1;
//int scaleType = 0;
//int maxType = 1;
//Mat im;

//string windowName = "Resize Image";
//string trackbarValue = "Scale";
//string trackbarType = "Type: \n 0: Scale Up \n 1: Scale Down";

//// Create method stub for callback function
//void scaleImage(int, void*);

//int main(){
//    // load an image
//    im = imread("truth.png");

//    // Create a window to display results
//    namedWindow(windowName, WINDOW_AUTOSIZE);

//    // Create the trackbars for the scaling factor and type
//    createTrackbar(trackbarValue, windowName, &scaleFactor, maxScaleUp, scaleImage);
//    createTrackbar(trackbarType, windowName, &scaleType, maxType, scaleImage);

//    // Display the image with a default value
//    scaleImage(25,0);

//    while (true){
//        // Continue until the escape button is pressed
//        int c;
//        c = waitKey(20);
//        if (static_cast<char>(c) == 27)
//            break;
//    }

//    return 0;
//}

//// Callback function for scaling image
//void scaleImage(int, void*){
//    double scaleFactorDouble = 1.0;
//    if (scaleType == 0) {
//        // Scale up
//        scaleFactorDouble = 1 + scaleFactor/100.0;
//    } else {
//        // Scale down
//        scaleFactorDouble = 1 - scaleFactor/100.0;
//    }

//    // Ensure edge conditions are taken care of
//    if (scaleFactorDouble == 0){
//        scaleFactorDouble = 0.01;
//    }

//    Mat scaledImage;
//    resize(im, scaledImage, Size(), scaleFactorDouble, scaleFactorDouble, INTER_LINEAR);
//    imshow(windowName, scaledImage);
//}

