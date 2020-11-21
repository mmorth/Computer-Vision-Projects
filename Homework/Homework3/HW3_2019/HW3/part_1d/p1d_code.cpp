#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

int brickNumbers[13];

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
Mat createGridMask(Mat frame);
void annotateBricks(Mat frame);
void processBrickLocation(Mat mask);
void drawBricksColumns(Mat frame);

int main()
{
    char keyPress;
    cout << "p1d_opencv_code\n";

//    Mat f1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1d\\frame.png");
//    Mat frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1d\\frame275.png");
//    Mat f2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1d\\frame706.png");

//    Mat whiteMask;
//    inRange(frame, Scalar(240,240,240), Scalar(255,255,255), whiteMask);
////    processBrickLocation(whiteMask);
//    imshow("whiteMask", whiteMask);

//    Mat orangeMask;
//    inRange(frame, Scalar(0,65,220), Scalar(30,150,255), orangeMask);
////    processBrickLocation(orangeMask);
//    imshow("orangeMask", orangeMask);

//    Mat cyanMask;
//    inRange(frame, Scalar(235,245,0), Scalar(255,255,30), cyanMask);
////    processBrickLocation(cyanMask);
//    imshow("cyanMask", cyanMask);

//    Mat greenMask;
//    inRange(frame, Scalar(0,245,0), Scalar(20,255,25), greenMask);
////    processBrickLocation(greenMask);
//    imshow("greenMask", greenMask);

//    Mat redMask;
//    inRange(frame, Scalar(0,0,170), Scalar(25,25,255), redMask);
////    processBrickLocation(redMask);
//    imshow("redMask", redMask);

//    Mat blueMask;
//    inRange(frame, Scalar(240,95,0), Scalar(255,115,15), blueMask);
////    processBrickLocation(blueMask);
//    imshow("blueMask", blueMask);

//    Mat yellowMask;
//    inRange(frame, Scalar(0,240,240), Scalar(25,255,255), yellowMask);
////    processBrickLocation(yellowMask);
//    imshow("yellowMask", yellowMask);

//    Mat purpleMask;
//    inRange(frame, Scalar(240,0,230), Scalar(255,20,255), purpleMask);
////    processBrickLocation(purpleMask);
//    imshow("purpleMask", purpleMask);

//    Mat grayMask;
//    inRange(frame, Scalar(140,140,140), Scalar(150,150,150), grayMask);
////    processBrickLocation(grayMask);
//    imshow("grayMask", grayMask);

//    imshow("f1", f1);
//    imshow("f2", f2);
//    imshow("og", frame);

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1d\\L2_clip1_16s.m4v");
    processVideo(cap1, "L2_clip1_16s.m4v", "p1d_output1.avi");
    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_1d\\L2_clip2_10s.m4v");
    processVideo(cap2, "L2_clip2_10s.m4v", "p1d_output2.avi");

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
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),60, Size(frame_width,frame_height));
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Locate and draw the number of bricks in each column
      Mat cropped = createGridMask(frame);
      annotateBricks(cropped);
      drawBricksColumns(frame);
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
    Mat mask(Size(838, 990), 16);
    mask = 0;
    Rect roi(38, 127, 759, 430);
    Mat temp = mask(roi);
    temp = Scalar(255, 255, 255);
    temp.copyTo(mask(roi));

    Mat result;
    bitwise_and(frame, mask, result);

    return result;
}

// Locates each brick location and assigns it to the correct column
void annotateBricks(Mat frame) {
    Mat whiteMask;
    inRange(frame, Scalar(240,240,240), Scalar(255,255,255), whiteMask);
    processBrickLocation(whiteMask);
//    imshow("whiteMask", whiteMask);

    Mat orangeMask;
    inRange(frame, Scalar(0,130,230), Scalar(20,150,255), orangeMask);
    processBrickLocation(orangeMask);
//    imshow("orangeMask", orangeMask);

    Mat cyanMask;
    inRange(frame, Scalar(235,245,0), Scalar(255,255,30), cyanMask);
    processBrickLocation(cyanMask);
//    imshow("cyanMask", cyanMask);

    Mat greenMask;
    inRange(frame, Scalar(0,245,0), Scalar(20,255,25), greenMask);
    processBrickLocation(greenMask);
//    imshow("greenMask", greenMask);

    Mat redMask;
    inRange(frame, Scalar(0,0,220), Scalar(25,25,255), redMask);
    processBrickLocation(redMask);
//    imshow("redMask", redMask);

    Mat blueMask;
    inRange(frame, Scalar(240,95,0), Scalar(255,115,15), blueMask);
    processBrickLocation(blueMask);
//    imshow("blueMask", blueMask);

    Mat yellowMask;
    inRange(frame, Scalar(0,240,240), Scalar(25,255,255), yellowMask);
    processBrickLocation(yellowMask);
//    imshow("yellowMask", yellowMask);

    Mat purpleMask;
    inRange(frame, Scalar(240,0,230), Scalar(255,20,255), purpleMask);
    processBrickLocation(purpleMask);
//    imshow("purpleMask", purpleMask);

    Mat grayMask;
    inRange(frame, Scalar(140,140,140), Scalar(150,150,150), grayMask);
    processBrickLocation(grayMask);
//    imshow("grayMask", grayMask);
}

// Find the number of sqaures of the given mask color based on contours
void processBrickLocation(Mat mask) {
    // Convert result to CV_8U to support finding contours
    Mat resb;
    mask.convertTo(resb, CV_8U, 255);

    // Each contours corresponds to a square
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Map the brick location to the correct column
    for (int i = 0; i < contours.size(); i++) {
        Rect br = boundingRect(contours[i]);
        if (contourArea(contours[i]) > 500) {
            brickNumbers[br.x/60]++;
        }
    }
}

// Writes the text with the number of bricks in each column
void drawBricksColumns(Mat frame) {
    for (int i = 0; i < 13; i++) {
        putText(frame, std::to_string(brickNumbers[i]), Point(40+60*i, 175), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 1);
        brickNumbers[i] = 0;
    }
}
