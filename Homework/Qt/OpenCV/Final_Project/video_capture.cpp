#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

struct vehicle {
    Rect br;
    Point centroid;
    int lastFrameSeen;
};

vector<vehicle> objects;

void processVideo(VideoCapture cap);

int main()
{
    cout << "p2_opencv_code\n";

    // Read input videos
    VideoCapture cap(1);
    processVideo(cap);

    return 0;
}

// Processes the video by converting it to grayscale and writing it to the output
// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
// The code from the source was modified to support the functionality of this assignment
void processVideo(VideoCapture cap) {
    // Check if camera opened successfully
    if(!cap.isOpened())
    {
      cout << "Error opening video stream" << endl;
      return;
    }

    // Default resolution of the frame is obtained.The default resolution is system dependent.
    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorKNN();
    Mat fgMask;

    // Create a video writer and process the input video frame by frame
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Run the background subtraction model
      pBackSub->apply(frame, fgMask);

      // Detect vechicles from the background subtraction mask
      imshow("frame", frame);

      // Write the frame into the output video file
//      video.write(frame);

      // Press  ESC on keyboard to  exit
      char c = (char)waitKey(1);
      if( c == 27 )
        break;
    }

    // Clean up video capture and writer
    cap.release();

    // Closes all the windows
    destroyAllWindows();
}
