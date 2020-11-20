//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//Mat createGridMask(Mat frame);
//void colorRedBricksOrange(Mat frame, Mat mask);
//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);

//int main()
//{
//    char keyPress;
//    cout << "p1b_opencv_code\n";

////    Mat frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1b\\frame484.png");
////    imshow("frame", frame);

//    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1b\\L1_clip1_12s.m4v");
//    processVideo(cap1, "L1_clip1_12s.m4v", "p1b_output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1b\\L2_clip2_16s.m4v");
//    processVideo(cap2, "L2_clip1_16s.m4v", "p1b_output2.avi");

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
//    int frameNum = 0;
//    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),60, Size(frame_width,frame_height));
//    while(1)
//    {
//      // Ready in a frame at a time
//      Mat frame;
//      cap >> frame;

//      // If the frame is empty, break immediately
//      if (frame.empty())
//        break;

//      // Color red bricks orange
//      Mat mask = createGridMask(frame);
//      colorRedBricksOrange(frame, mask);
////      imwrite("frame" + std::to_string(frameNum++) + ".png", frame);
////      imshow("frame", frame);

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

//// Create a mask for the board to prevent matching of the Pacman representing the player's lives
//Mat createGridMask(Mat frame) {
//    Mat mask(Size(838, 990), 16);
//    mask = 0;
//    Rect roi(13, 97, 808, 609);
//    Mat temp = mask(roi);
//    temp = Scalar(255, 255, 255);
//    temp.copyTo(mask(roi));

//    Mat result;
//    bitwise_and(frame, mask, result);

//    return result;
//}

//// Colors the red bricks orange
//void colorRedBricksOrange(Mat frame, Mat mask) {
//    // Create the mask to isolate the Pacman colors
//    Mat redMask;
//    inRange(mask, Scalar(0, 0, 40), Scalar(50, 40, 255), redMask);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    redMask.convertTo(resb, CV_8U, 255);

//    // Find the contours that could correspond to Pacman
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Only draw the contours that are large enough (e.g. remove the noise of smaller objects with similar colors to Pacman)
//    for (int i = 0; i < contours.size(); i++) {
//        int area = contourArea(contours[i]);
//        Rect br = boundingRect(contours[i]);
//        // Match only the bricks and not the power ups
////        printf("width = %d\n", br.width);
//        if (area > 100 && br.width < 58) {
//            drawContours(frame, contours, i, Scalar(4, 140, 243), -1);
//        }
//    }
//}
