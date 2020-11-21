#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

bool firstPoint = true;
int numContours = 124;
int contourIndex = 0;
std::vector<std::vector<cv::Point> > contourVec;

void colorBallRedAndDrawTrajectory(Mat frame);
void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);

int main()
{
    char keyPress;
    cout << "p1c_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1c\\L5_clip1_15s.m4v");
    processVideo(cap1, "L5_clip1_15s.m4v", "p1c_output1.avi");
    firstPoint = true;
    contourIndex = 0;
    contourVec.clear();
    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1c\\L5_clip2_12s.m4v");
    processVideo(cap2, "L5_clip2_12s.m4v", "p1c_output2.avi");

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

      // Apply green color to Pacman in the frame
      colorBallRedAndDrawTrajectory(frame);

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

// Colors ball green and draws its last 2 second trajectory
void colorBallRedAndDrawTrajectory(Mat frame) {
    // Create the mask to isolate the ball's colors
    Mat ballMask;
    inRange(frame, Scalar(195, 220, 0), Scalar(255, 255, 145), ballMask);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    ballMask.convertTo(resb, CV_8U, 255);

    // Find the contours that could correspond to Pacman
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Create a Mat that will store Pacman's path
    Mat path(Size(frame.cols, frame.rows), 16);
    path = Scalar(0,0,0);

    // Only draw the contours that are large enough (e.g. remove the noise of smaller objects with similar colors to Pacman)
    for (int i = 0; i < contours.size(); i++) {
        // Determine which of the contours is the ball
        Rect br = boundingRect(contours[i]);
        if (contourArea(contours[i]) > 40 && contourArea(contours[i]) < 100 && br.width < 15 && br.height < 10) {
            // Get the information about the ball's current location
            Point curPoint = Point(br.x+br.width/2, br.y+br.height/2);

            if (firstPoint) {
                // Process the first point
                std::vector<cv::Point> contour;
                contour.push_back(curPoint);

                contourVec.push_back(contour);
                contourIndex++;
                firstPoint = false;
            } else {
                // Process all non-first points
                if (contourIndex < numContours) {
                    // Populate the first 124 frame points
                    contourVec.at(0).push_back(curPoint);
                    contourIndex++;
                } else {
                    // Shift all points left and replace the last element with the current point
                    std::rotate(contourVec.at(0).begin(), contourVec.at(0).begin()+1, contourVec.at(0).end());
                    contourVec.at(0).at(numContours-1) = curPoint;
                }

                // Draw the last 2 second ball trajectory
                polylines(path, contourVec.at(0), false, Scalar(0,0,255));
            }

            // Color in the red ball
            drawContours(frame, contours, i, Scalar(0, 0, 255), FILLED);
        }
    }

    // Add the ball's last 2 second trajectory to the frame
    frame = frame + path;
}
