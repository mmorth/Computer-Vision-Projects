#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
void detectVehicles(Mat frame, Mat mask);

int numBuses = 0;
int numCars = 0;
int numPeople = 0;

int main()
{
    cout << "p1a_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip1.avi");
    processVideo(cap1, "clip1.avi", "output1.avi");
    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip2.avi");
    processVideo(cap2, "clip2.avi", "output2.avi");
    VideoCapture cap3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip3.avi");
    processVideo(cap3, "clip3.avi", "output3.avi");

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

    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorMOG2();
    Mat fgMask;

    // Create a video writer and process the input video frame by frame
    int frameNum = 0;
    printf("Processing video %s...\n", inputVideoName.c_str());
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height), true);
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
      detectVehicles(frame, fgMask);
      imshow("frame", fgMask);

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
void detectVehicles(Mat frame, Mat mask) {
    // Convert result to CV_8U to support finding contours
    Mat resb;
    mask.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Map the brick location to the correct column
    for (int i = 0; i < contours.size(); i++) {
        Rect br = boundingRect(contours[i]);
        if (contourArea(contours[i]) > 500) {
            rectangle(frame, br, Scalar(255, 255, 255), 10);
        }
    }

    string text = "#Buses = " + std::to_string(numBuses);
    putText(frame, text, Point(25, 10), FONT_HERSHEY_TRIPLEX, 2, Scalar(255, 255, 255), 1);
    text = "#Buses = " + std::to_string(numCars);
    putText(frame, text, Point(50, 10), FONT_HERSHEY_TRIPLEX, 2, Scalar(255, 255, 255), 1);
    text = "#Buses = " + std::to_string(numPeople);
    putText(frame, text, Point(75, 10), FONT_HERSHEY_TRIPLEX, 2, Scalar(255, 255, 255), 1);
}

// Part 1
// Classify vehicles based on the height of the contour
// You can mask the top part of the image since vehicles and people there should not be counted (could be reflection or not passing by)
// Need to figure out how to handle counting vehicles only once after moving across the screen
    // Could keep track of each vehicle's position on the screen until they have left the screen in a vector

// Part 2A
// Capture the first frame
// If bus is in frame, draw the actual frame
// If bus is not in frame, draw the first frame
// Will need to consider edge conditions when the bus is leaving the screen not to abruptly stop the video
    // Maybe we can control this by classifying a bus based on its height?

// Part 2B
// Maybe store a list of detected vehicles and their locations frame by frame
// If a car detection is triggered starting on the left side, then we want to show that vehicle across the screen
// Need a way to not show people and buses moving across the screen
    // Maybe we could display the first frame's roi in the detected contour region of the vehicle?
