#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

bool ledState[26];

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
Mat createGridMask(Mat frame);
void processLEDState(Mat frame, Mat mask);
void drawLEDState(Mat frame);

int main()
{
    char keyPress;
    cout << "p2a_opencv_code\n";

    Mat displayFrame1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\frame2.png");

//    Mat mask;
//    inRange(displayFrame1, Scalar(180,240,220), Scalar(255,255,255), mask);
//    imshow("mask", mask);

//    imshow("dp1", displayFrame1);
//    imshow("mask", mask);

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_2b\\input2b_small.mp4");
    processVideo(cap1, "input2a_small.mp4", "p2b_output1.avi");

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
    int frameNum = 0;
    printf("Processing video %s...\n", inputVideoName.c_str());
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),10, Size(frame_width,frame_height));
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

//      imwrite("frame" + std::to_string(frameNum++) + ".png", frame);

      Mat mask = createGridMask(frame);
      processLEDState(frame, mask);
      drawLEDState(frame);

      imshow("frame", frame);

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

// Create a mask for the board to prevent matching of the Pacman representing the player's lives
Mat createGridMask(Mat frame) {
    Mat mask(Size(852, 240), 16);
    mask = 0;
    Rect roi(0, 122, 852, 40);
    Mat temp = mask(roi);
    temp = Scalar(255, 255, 255);
    temp.copyTo(mask(roi));

    Mat result;
    bitwise_and(frame, mask, result);

    return result;
}

// Determines which LEDs are in the on state and draws their status under them
void processLEDState(Mat frame, Mat regionMask) {
    Mat mask;
    inRange(regionMask, Scalar(180,240,220), Scalar(255,255,255), mask);
    imshow("mask", mask);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    mask.convertTo(resb, CV_8U, 255);

    // Each contours corresponds to a square
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Map the brick location to the correct column
    for (int i = 0; i < contours.size(); i++) {
        Rect br = boundingRect(contours[i]);
        if (contourArea(contours[i]) > 25) {
            printf("x = %d\n", br.x+br.width/2);
            printf("index = %d\n\n", (br.x+br.width/2-40)%30);
            int centerX = br.x+br.width/2;
            if ((centerX-40)%30 < 15) {
                ledState[(centerX-40)%30] = true;
            }
        }
    }
}

// Draws the LED states above each LED on the frame
void drawLEDState(Mat frame) {
    for (int i = 0; i < 26; i++) {
        if (ledState[i]) {
            putText(frame, "1", Point(40+30*i, 122), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 1);
            ledState[i] = 0;
        } else {
            putText(frame, "0", Point(40+30*i, 122), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 1);
        }
    }
}
