//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void colorPacmanGreen(Mat frame);
//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);

//int main()
//{
//    char keyPress;
//    cout << "p1b_opencv_code\n";

//    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part1b\\input1b1.avi");
//    processVideo(cap1, "input1b1.avi", "p1b_output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part1b\\input1b2.avi");
//    processVideo(cap2, "input1b2.avi", "p1b_output2.avi");

//    while(1)
//    {
//        keyPress = waitKey();
//        // Press q key to close window
//        if (keyPress == 'q')
//        {
//            destroyAllWindows();
//            break;
//        }
//    }
//    return 0;
//}

//// Processes the video by converting it to grayscale and writing it to the output
//// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
//// The code from the source was modified to support the functionality of this assignment
//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName) {
//    // Check if camera opened successfully
//    if(!cap.isOpened())
//    {
//      cout << "Error opening video stream" << endl;
//      return;
//    }

//    // Default resolution of the frame is obtained.The default resolution is system dependent.
//    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
//    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

//    // Create a video writer and process the input video frame by frame
//    printf("Processing video %s...\n", inputVideoName.c_str());
//    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height));
//    while(1)
//    {
//      // Ready in a frame at a time
//      Mat frame;
//      cap >> frame;

//      // If the frame is empty, break immediately
//      if (frame.empty())
//        break;

//      // Apply green color to Pacman in the frame
//      colorPacmanGreen(frame);

//      // Write the frame into the output video file
//      video.write(frame);

//      // Press  ESC on keyboard to  exit
//      char c = (char)waitKey(1);
//      if( c == 27 )
//        break;
//    }

//    // Clean up video capture and writer
//    cap.release();
//    video.release();

//    // Closes all the windows
//    destroyAllWindows();

//    printf("Video processing complete for %s!\n", outputVideoName.c_str());
//}

//// Colors Pacman green
//void colorPacmanGreen(Mat frame) {
//    // Create the mask to isolate the Pacman colors
//    Mat yellowMask;
//    inRange(frame, Scalar(0, 200, 200), Scalar(210, 255, 255), yellowMask);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    yellowMask.convertTo(resb, CV_8U, 255);

//    // Find the contours that could correspond to Pacman
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Only draw the contours that are large enough (e.g. remove the noise of smaller objects with similar colors to Pacman)
//    for (int i = 0; i < contours.size(); i++) {
//        if (contourArea(contours[i]) > 25) {
//            drawContours(frame, contours, i, Scalar(0, 255, 0), -1);
//        }
//    }
//}
