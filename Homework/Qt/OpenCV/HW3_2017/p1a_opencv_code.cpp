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
    cout << "p1a_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2017\\template\\Where_is_the_ball\\input1.m4v");
    processVideo(cap1, "input1.m4v", "output1.avi");
    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2017\\template\\Where_is_the_ball\\input2.m4v");
    processVideo(cap2, "input2.m4v", "output2.avi");
    VideoCapture cap3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2017\\template\\Where_is_the_ball\\input3.m4v");
    processVideo(cap3, "input3.m4v", "output3.avi");

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
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),60, Size(frame_width,frame_height), false);
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Convert the frame to grayscale
      cvtColor(frame, frame, COLOR_BGR2GRAY);

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

// Determine color of ball to match in the image
// If orange ball is not visible, determine color of cup near location last seen
// Track that cup until the ball becomes visible again
// Continue until the end of the video

// Note: tracking the ball means showing the orange highlighted ball even when its in the cup
