#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

// Stores the points for the selected greenscreen color area
Point topLeft;
Point bottomRight;
Mat source;
Mat background;

// Stores whether the greenscreen region has been selected
bool greenScreenSelected = false;

// Specifies the greenscreen color selected by the user
Scalar greenScreenColor;
int greenScreenValue = 0;

// function which will be called on mouse input
void chooseGreenscreenColor(int action, int x, int y, int flags, void *userdata)
{
    // Action to be taken when left mouse button is pressed
    if( action == EVENT_LBUTTONDOWN )
    {
      // Mark top left corner of selection
      topLeft = Point(x,y);
    }
    // Action to be taken when left mouse button is released
    else if( action == EVENT_LBUTTONUP)
    {
      // Mark bottom right corner of selection
      bottomRight = Point(x,y);

      // Find the mean color based on the selection made
      Mat gsRoi = source(Range(topLeft.y, bottomRight.y), Range(topLeft.x, bottomRight.x));
      greenScreenColor = mean(gsRoi);

      cout << greenScreenColor << endl;

      // Specify that the image has been correctly detected
      greenScreenSelected = true;
    }
}

// This function processes the greenscreen from the video frame by frame
void greenScreenDetector(Mat frame)
{
    // Implement desired greenscreen detections
    Mat mask;
    int lowBlue = max(0, static_cast<int>(greenScreenColor[0])-greenScreenValue/2);
    int lowGreen = max(0, static_cast<int>(greenScreenColor[1])-greenScreenValue);
    int lowRed = max(0, static_cast<int>(greenScreenColor[2])-greenScreenValue/2);
    int highBlue = min(255, static_cast<int>(greenScreenColor[0])+greenScreenValue/2);
    int highGreen = min(255, static_cast<int>(greenScreenColor[1])+greenScreenValue);
    int highRed = min(255, static_cast<int>(greenScreenColor[2])+greenScreenValue/2);
    Scalar lowRange(lowBlue, lowGreen, lowRed);
    Scalar highRange(highBlue, highGreen, highRed);
    inRange(frame, lowRange, highRange, mask);

    Mat maskBackground;
    cvtColor(mask, mask, COLOR_GRAY2BGR);
    bitwise_and(background, mask, maskBackground);

    bitwise_not(mask, mask);
    bitwise_and(frame, mask, frame);

    bitwise_or(frame, maskBackground, frame);
}

int main()
{
    // Create a window to display results
    namedWindow("Window", WINDOW_AUTOSIZE);

    // highgui function called when mouse events occur
    setMouseCallback("Window", chooseGreenscreenColor);

    // ================================== First Video =================================

    // TODO: Show sample frame from video and have user select region to use as greenscreen color background
    source = imread("demo.png");
    background = imread("sample.jpg");
    resize(background, background, Size(source.cols, source.rows));

    Mat dummy = source.clone();
    int k = 0;
    while(!greenScreenSelected)
    {
      imshow("Window", source );
      putText(source,"Drag greenscreen region" ,Point(10,30), FONT_HERSHEY_SIMPLEX, 0.7,Scalar(255,255,255), 2 );
      k= waitKey(20) & 0xFF;
      if(k== 99) {
              // Another way of cloning
              dummy.copyTo(source);
      } else if (k == 27) {
          return -1;
      }
    }

    // Create Trackbars and associate a callback function
    createTrackbar("Green Screen Slides", "Window", &greenScreenValue, 100);

    VideoCapture cap("greenscreen-demo.mp4");

    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
    }

    // Read until video is completed
    while(cap.isOpened()){

        Mat frame;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
          break;

        greenScreenDetector(frame);

        // Write the frame into the file 'outputChaplin.mp4'
        imshow("Window", frame);

        // Wait for 25 ms before moving on to the next frame
        // This will slow down the video
        waitKey(25);
    }


    // ====================== Second Video ====================================

//    source = imread("asteroid.png");

//    resize(background, background, Size(source.cols, source.rows));

//    dummy = source.clone();
//    while(greenScreenSelected)
//    {
//      imshow("Window", source );
//      putText(source,"Drag greenscreen region" ,Point(10,30), FONT_HERSHEY_SIMPLEX, 0.7,Scalar(255,255,255), 2 );
//      k= waitKey(20) & 0xFF;
//      if(k== 99) {
//              // Another way of cloning
//              dummy.copyTo(source);
//      } else if (k == 27) {
//          return -1;
//      }
//    }

//    cap.release();

//    VideoCapture cap2("greenscreen-asteroid.mp4");

//    greenScreenSelected = false;

//    // Check if camera opened successfully
//    if(!cap2.isOpened()){
//        cout << "Error opening video stream or file" << endl;
//    }

//    // Read until video is completed
//    while(cap2.isOpened()){

//        Mat frame;

//        // cap2ture frame-by-frame
//        cap2 >> frame;

//        // If the frame is empty, break immediately
//        if (frame.empty())
//          break;

//        greenScreenDetector(frame);

//        // Write the frame into the file 'outputChaplin.mp4'
//        imshow("Frame", frame);

//        // Wait for 25 ms before moving on to the next frame
//        // This will slow down the video
//        waitKey(25);
//    }

//    cap2.release();

    return 0;
}
