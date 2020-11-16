#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);

int main()
{
    char keyPress;
    cout << "p1b_opencv_code\n";

    Mat frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part1a\\frame.png");
    imshow("frame", frame);

    Mat yellowMask;
    inRange(frame, Scalar(0, 200, 200), Scalar(200, 255, 255), yellowMask);
    frame.setTo(Scalar(0, 255, 0), yellowMask);

    // TODO: Need to find the bounding box of Pacman and only filter the colors in the bounding box region

    imshow("after", frame);

    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part1a\\input1a1.avi");
//    processVideo(cap1, "input1a1.avi", "p1a_output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part1a\\input1a2.avi");
//    processVideo(cap2, "input1a2.avi", "p1a_output2.avi");

    while(1)
    {
        keyPress = waitKey();
        // Press q key to close window
        if (keyPress == 'q')
        {
            destroyAllWindows();
            break;
        }
    }
    return 0;
}

// Processes the video by converting it to grayscale and writing it to the output
// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
// The code from the source was modified to support the functionality of this assignment
void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName) {
    // Check if camera opened successfully
    if(!cap.isOpened())
    {
      cout << "Error opening video stream" << endl;
      return;
    }

    // Default resolution of the frame is obtained.The default resolution is system dependent.
    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    // Create a video writer and process the input video frame by frame
    printf("Processing video %s...\n", inputVideoName.c_str());
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height));
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      Mat blueMask;
      inRange(frame, Scalar(65, 0, 0), Scalar(195, 70, 70), blueMask);
      frame.setTo(Scalar(0, 255, 0), blueMask);

      // Write the frame into the output video file
      video.write(frame);

      // Press  ESC on keyboard to  exit
      char c = (char)waitKey(1);
      if( c == 27 )
        break;
    }

    // Clean up video capture and writer
    cap.release();
    video.release();

    // Closes all the windows
    destroyAllWindows();

    printf("Video processing complete for %s!\n", outputVideoName.c_str());
}
