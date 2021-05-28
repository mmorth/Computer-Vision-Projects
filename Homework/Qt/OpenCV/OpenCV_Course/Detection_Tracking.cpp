#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

// Detects the location of the ball and returns location
Rect findBallLocation(Mat frame)
{
    // Use detection to find the location of the ball


    // Find bounding rectangle of ball and draw in blue


    // Return the bounding rectangle of the ball (if not found, let user know)

}

// Tracks the ball
bool trackBall(Mat frame, Rect location, bool foundLastFrame)
{
    // Determine whether ball was found last frame
    if (!foundLastFrame)
    {
        // Check whether rectangle location is valid


            // Start up new tracker given location information

    }
    else if (foundLastFrame)
    {
        // Use an OpenCV tracker to track the soccer ball location

    }

    // Draw bounding ball location in green


    // Return whether this frame's tracking was successful

}

int main()
{
    VideoCapture cap("soccer-ball.mp4");

    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
    }

    // Read until video is completed
    Rect location;
    bool foundLastFrame = false;
    while(cap.isOpened()){

        Mat frame;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
          break;

        if (!foundLastFrame)
        {
            location = findBallLocation(frame);
        }

        foundLastFrame = trackBall(frame, location, foundLastFrame);

        // Display the found ball location
        imshow("Window", frame);

        // Wait for 25 ms before moving on to the next frame
        // This will slow down the video
        waitKey(25);
    }

    return 0;
}
