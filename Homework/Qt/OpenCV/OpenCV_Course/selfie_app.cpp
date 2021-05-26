//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//// Executes the skin smoothing using Haar Cascades and Histograms
//Mat smoothSkin(Mat image)
//{
//    // Execute Haar Cascades to find the location of the faces


//    // Iterate over the detected faces
//    // Use grabcut to detect the skin region on the face


//        // Create a histogram of colors within the face region


//        // Flatten out the histogram to remove peaks and valleys (smooth)
//        // Can also apply a smoothing filter on the face region

//}

//// Applies the sunglasses filter to the detected face
//// Play around to see how to do it manually first, then implement
//Mat applySunglassesFilter(Mat image, Mat sunglasses)
//{
//    // Use Haar Cascades to find the location of the eyes


//    // Apply math/bitwise operations to place the sunglasses on the face


//    // Use alpha Matting to give transparency effect to sunglasses lens

//}

//int main()
//{
//    // ================================== First Video =================================

//    // TODO: Show sample frame from video and have user select region to use as greenscreen color background
//    Mat source = imread("musk.jpg");
//    Mat sunglasses = imread("sunglass.png");

//    Mat smoothedImage = smoothSkin(source);

//    Mat result = applySunglassesFilter(source, sunglasses);

//    imshow("Smoothed", smoothedImage);
//    imshow("Sunglasses Filter", result);
//    waitKey(0);

//    // TODO: Uncomment when done testing on test image
////    // TODO: Change number to the number camera you have
////    // Read video from webcam
////    VideoCapture cap(1);

////    // Check if camera opened successfully
////    if(!cap.isOpened()){
////        cout << "Error opening video stream or file" << endl;
////    }

////    // Read until video is completed
////    while(cap.isOpened()){

////        Mat frame;

////        // Capture frame-by-frame
////        cap >> frame;

////        // If the frame is empty, break immediately
////        if (frame.empty())
////          break;

////        Mat smoothedImage = smoothSkin(frame);

////        Mat result = applySunglassesFilter(frame, sunglasses);

////        // Write the frame into the file 'outputChaplin.mp4'
////        imshow("Original", frame);
////        imshow("Smoothed", smoothedImage);
////        imshow("Sunglasses Filter", result);

////        // Wait for 25 ms before moving on to the next frame
////        // This will slow down the video
////        waitKey(25);
////    }

//    return 0;
//}
