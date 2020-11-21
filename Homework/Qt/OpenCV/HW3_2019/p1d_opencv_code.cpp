#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
Mat annotateSquares(Mat frame);
int findNumSquares(Mat mask);

int main()
{
    char keyPress;
    cout << "p1b_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_1b\\p1b_tetris_1.mp4");
    processVideo(cap1, "p1b_tetris_1.mp4", "p1b_output1.avi");
    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_1b\\p1b_tetris_2.mp4");
    processVideo(cap2, "p1b_tetris_2.mp4", "p1b_output2.avi");

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
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),60, Size(frame_width,frame_height));
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      frame = annotateSquares(frame);

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

// Prints the number of squares of each color on the video frame
Mat annotateSquares(Mat f) {
    Mat result = f.clone();
    Mat frame = f.clone();
    Mat yellowMask;
    inRange(frame, Scalar(0,233,224), Scalar(37,255,255), yellowMask);
    frame.setTo(Scalar(0, 0, 0), yellowMask);
    string yellowText = "# Yellow Squares = " + std::to_string(findNumSquares(yellowMask));
    putText(result, yellowText, Point(10,50), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 3);

    frame = f.clone();
    Mat orangeMask;
    inRange(frame, Scalar(0,148,240), Scalar(18,160,255), orangeMask);
    frame.setTo(Scalar(0, 0, 0), orangeMask);
    string orangeText = "# Orange Squares = " + std::to_string(findNumSquares(orangeMask));
    putText(result, orangeText, Point(10,100), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 3);

    frame = f.clone();
    Mat cyanMask;
    inRange(frame, Scalar(225,225,0), Scalar(255,255,30), cyanMask);
    frame.setTo(Scalar(0, 0, 0), cyanMask);
    string cyanText = "# Cyan Squares = " + std::to_string(findNumSquares(cyanMask));
    putText(result, cyanText, Point(10,150), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 3);

    frame = f.clone();
    Mat greenMask;
    inRange(frame, Scalar(0,100,0), Scalar(30,140,30), greenMask);
    frame.setTo(Scalar(0, 0, 0), greenMask);
    string greenText = "# Green Squares = " + std::to_string(findNumSquares(greenMask));
    putText(result, greenText, Point(10,200), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 3);

    frame = f.clone();
    Mat  blueMask;
    inRange(frame, Scalar(240,0,15), Scalar(255,20,35),  blueMask);
    frame.setTo(Scalar(0, 0, 0),  blueMask);
    string  blueText = "#  Blue Squares = " + std::to_string(findNumSquares( blueMask));
    putText(result,  blueText, Point(10,250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 3);

    Mat purpleMask;
    inRange(frame, Scalar(100, 0, 100), Scalar(140, 30, 140), purpleMask);
    frame.setTo(Scalar(0, 0, 0), purpleMask);
    string  purpleText = "#  Purple Squares = " + std::to_string(findNumSquares( purpleMask));
    putText(result,  purpleText, Point(10,300), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 3);

    Mat redMask;
    inRange(frame, Scalar(0, 0, 225), Scalar(30, 30, 255), redMask);
    frame.setTo(Scalar(0, 0, 0), redMask);
    string  redText = "#  Red Squares = " + std::to_string(findNumSquares( redMask));
    putText(result,  redText, Point(10,350), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 3);

    return result;
}

// Find the number of sqaures of the given mask color based on contours
int findNumSquares(Mat mask) {
    // Convert result to CV_8U to support finding contours
    Mat resb;
    mask.convertTo(resb, CV_8U, 255);

    // Each contours corresponds to a square
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    int numSquares = 0;
    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > 1000) {
            numSquares++;
        }
    }

    return numSquares;
}
