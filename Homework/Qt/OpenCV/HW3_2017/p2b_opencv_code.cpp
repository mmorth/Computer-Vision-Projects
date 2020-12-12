#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

int frameNum = 0;

void processVideo(VideoCapture cap, Mat firstFrame, string inputVideoName, string outputVideoName);
void detectBuses(Mat firstFrame, Mat frame, Mat mask);
void drawBusesOnFrame(Mat firstFrame, Mat videoFrame, Rect location);

int main()
{
    cout << "p2b_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip1.avi");
    Mat video1Frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\video1Frame.png");
    processVideo(cap1, video1Frame, "clip1.avi", "output1.avi");

    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip2.avi");
    Mat video2Frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\video2Frame.png");
    processVideo(cap2, video2Frame, "clip2.avi", "output2.avi");

    VideoCapture cap3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip3.avi");
    Mat video3Frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\video3Frame.png");
    processVideo(cap3, video3Frame, "clip3.avi", "output3.avi");

    return 0;
}

// Processes the video by converting it to grayscale and writing it to the output
// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
// The code from the source was modified to support the functionality of this assignment
void processVideo(VideoCapture cap, Mat firstFrame, string inputVideoName, string outputVideoName) {
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
    printf("Processing video %s...\n", inputVideoName.c_str());
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height), true);
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;
      frameNum++;

      Mat backgroundFrame = firstFrame.clone();

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Run the background subtraction model
      pBackSub->apply(frame, fgMask);

      // Detect vechicles from the background subtraction mask
      detectBuses(backgroundFrame, frame, fgMask);
      imshow("backgroundFrame", backgroundFrame);
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
    video.release();

    // Closes all the windows
    destroyAllWindows();

    printf("Video processing complete for %s!\n", outputVideoName.c_str());
}

// Detect vehicles in the frame and count total number
void detectBuses(Mat firstFrame, Mat videoFrame, Mat mask) {
    // Threshold to pull out the main part of the object
    threshold(mask, mask, 200, 255, THRESH_BINARY);
    int width = 1;
    Mat element = getStructuringElement( MORPH_RECT,
                       Size( 2*(width+1) + 1, 2*width+1 ),
                       Point( width+1, width ) );
    dilate( mask, mask, element );
    imshow("mask", mask);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    mask.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Determine whether detected objects are a vehicle or not
    for (int i = 0; i < contours.size(); i++) {
        // Compute the bounding rectangle of the detected contour
        Rect br = boundingRect(contours[i]);

        // Ensure that the detected contour is a bus
        if (contourArea(contours[i]) > 1000 && br.y > 50 && br.height > 60 && br.height < 90) {
            // Draw the bus on the frame
            drawBusesOnFrame(firstFrame, videoFrame, br);
        }
    }
}

// Draws the detected bus on the frame
void drawBusesOnFrame(Mat firstFrame, Mat videoFrame, Rect location) {
    // Filter for the red bus color
    Mat mask;
    inRange(videoFrame, Scalar(50, 55, 150), Scalar(80, 80, 200), mask);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    mask.convertTo(resb, CV_8U, 255);

    // Find the contours of the masked image
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    if (contours.size() > 0) {
        Mat bus = videoFrame(location);
        bus.copyTo(firstFrame(location));
    }
}
