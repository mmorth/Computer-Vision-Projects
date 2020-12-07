#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

bool orangeBallFoundInFrame = false;
bool ballInsideCup = false;
int ballCupLocation = 0;
Rect lastBallLocation;
Rect objectLocations[4];

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
void computeColorDetection(Mat frame);
void determineObjectLocation(Mat frame, Mat mask, int object);
void processBallLocation();

int main()
{
    cout << "p1a_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2017\\template\\Where_is_the_ball\\part_a\\input1.mp4");
    processVideo(cap1, "input1.m4v", "output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2017\\template\\Where_is_the_ball\\part_a\\input2.mp4");
//    processVideo(cap2, "input2.m4v", "output2.avi");
//    VideoCapture cap3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2017\\template\\Where_is_the_ball\\part_a\\input3.mp4");
//    processVideo(cap3, "input3.m4v", "output3.avi");

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
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),15, Size(frame_width,frame_height), false);
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      computeColorDetection(frame);
      imshow("frame", frame);

//      imwrite("frame" + std::to_string(frameNum++) + ".png", frame);

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

void computeColorDetection(Mat frame) {
    // Detect the orange ball color
    Mat orangeMask;
    inRange(frame, Scalar(100,130,210), Scalar(170,220,255), orangeMask);
    determineObjectLocation(frame, orangeMask, 1);

    // Detect the red cup
    Mat redMask;
    inRange(frame, Scalar(40,30,140), Scalar(140,100,220), redMask);
    determineObjectLocation(frame, redMask, 2);

    // Detect the green cup
    Mat greenMask;
    inRange(frame, Scalar(100,180,70), Scalar(200,255,150), greenMask);
    determineObjectLocation(frame, greenMask, 3);

    // Detect the blue cup
    Mat blueMask;
    inRange(frame, Scalar(180,60,0), Scalar(255,130,80), blueMask);
    determineObjectLocation(frame, blueMask, 4);

    // Process the orange ball's location
    processBallLocation();
}

void determineObjectLocation(Mat frame, Mat mask, int object) {
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
            // Based on which object this is detecting, store the bounding rectangle for that object
            if (object == 1) {
                // Orange ball detected
                lastBallLocation = objectLocations[0];
                objectLocations[0] = br;
                orangeBallFoundInFrame = true;
                ballInsideCup = false;
            } else if (object == 2) {
                // Red cup detected
                objectLocations[1] = br;
            } else if (object == 3) {
                // Green cup detected
                objectLocations[2] = br;
            } else {
                // Blue cup detected
                objectLocations[3] = br;
            }
//            rectangle(frame, br, Scalar(255, 255, 255), 5);
        }
    }
}

void processBallLocation() {
    // Check if an object location is stored for the orange ball in the current iteration
    if (orangeBallFoundInFrame) {
        // If so, then fill in the orange ball's contour

    } else {
        if (ballInsideCup) {
            // Draw the ball at the bottom of the identified cup it is inside

        } else {
            // If not, fill in the previous ball's contour size at the bottom of the nearest cup
                // Need to ensure the distance between the ball's last location and the current location is below a certain threshold
                // If not, then do not draw the ball under the nearest cup

        }

        ballInsideCup = true;
    }

    // Reset variables for next frame
    orangeBallFoundInFrame = false;
}
