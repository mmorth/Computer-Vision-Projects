//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//int numPellets = 0;
//void processPellet(Mat frame, Mat pellets);
//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);

//int main()
//{
//    char keyPress;
//    cout << "p2a_opencv_code\n";

//    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part2a\\input2a1.avi");
//    processVideo(cap1, "input2a1.avi", "p2a_output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part2a\\input2a2.avi");
//    processVideo(cap2, "input2a2.avi", "p2a_output2.avi");

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

//      Mat pelletMask;
//      inRange(frame, Scalar(165, 165, 200), Scalar(205, 205, 255), pelletMask);

//      processPellet(frame, pelletMask);
//      imshow("frame", frame);

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

//// Counts the number of pellets in the map
//void processPellet(Mat frame, Mat pellets) {
//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    pellets.convertTo(resb, CV_8U, 255);

//    // Each contours corresponds to a pellet
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    int numSquares = 0;
//    for (int i = 0; i < contours.size(); i++) {
//        if (contourArea(contours[i]) > 25) {
//            numSquares++;
//        }
//    }

//    // Handle situation where the pellets are in the off blink state
//    if (numSquares == 0) {
//        numSquares = numPellets;
//    } else {
//        numPellets = numSquares;
//    }

//    // Draw the number of pellets in the top right corner
//    string text = "# Pellets = " + std::to_string(numSquares);
//    putText(frame,  text, Point(150,10), FONT_HERSHEY_TRIPLEX, .25, Scalar(255, 255, 255), 1);
//}
