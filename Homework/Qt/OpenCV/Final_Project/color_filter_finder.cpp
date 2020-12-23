//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/videoio.hpp"
//#include <iostream>
//using namespace cv;
//const int max_value_H = 360/2;
//const int max_value = 255;
//const String window_capture_name = "Video Capture";
//const String window_detection_name = "Object Detection";
//int low_H = 0, low_S = 160, low_V = 180;
//int high_H = 12, high_S = 200, high_V = 200;
//static void on_low_H_thresh_trackbar(int, void *)
//{
//    low_H = min(high_H-1, low_H);
//    setTrackbarPos("Low H", window_detection_name, low_H);
//}
//static void on_high_H_thresh_trackbar(int, void *)
//{
//    high_H = max(high_H, low_H+1);
//    setTrackbarPos("High H", window_detection_name, high_H);
//}
//static void on_low_S_thresh_trackbar(int, void *)
//{
//    low_S = min(high_S-1, low_S);
//    setTrackbarPos("Low S", window_detection_name, low_S);
//}
//static void on_high_S_thresh_trackbar(int, void *)
//{
//    high_S = max(high_S, low_S+1);
//    setTrackbarPos("High S", window_detection_name, high_S);
//}
//static void on_low_V_thresh_trackbar(int, void *)
//{
//    low_V = min(high_V-1, low_V);
//    setTrackbarPos("Low V", window_detection_name, low_V);
//}
//static void on_high_V_thresh_trackbar(int, void *)
//{
//    high_V = max(high_V, low_V+1);
//    setTrackbarPos("High V", window_detection_name, high_V);
//}
//int main()
//{
//    VideoCapture cap(1);
//    namedWindow(window_capture_name);
//    namedWindow(window_detection_name);
//    // Trackbars to set thresholds for HSV values
//    createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
//    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
//    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
//    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
//    createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
//    createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
//    Mat frame, frame_HSV, frame_threshold;
//    while (true) {
//        cap >> frame;
//        if(frame.empty())
//        {
//            break;
//        }
//        // Convert from BGR to HSV colorspace
//        cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
//        // Detect the object based on HSV Range Values
//        inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);

////        // Dilate to fill in the detected body more
////        int width = 20;
////        Mat element = getStructuringElement( MORPH_RECT,
////                           Size( 2*(width+1) + 1, 2*width+1 ),
////                           Point( width+1, width ) );
////        dilate( frame_threshold, frame_threshold, element );

//        // Show the frames
//        imshow(window_capture_name, frame);
//        imshow(window_detection_name, frame_threshold);
//        char key = (char) waitKey(30);
//        if (key == 'q' || key == 27)
//        {
//            break;
//        }
//    }
//    return 0;
//}
