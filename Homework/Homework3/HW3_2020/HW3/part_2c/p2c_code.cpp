#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;

int numFire = 0;
int numCoins = 0;
int lastFrameCoins = 0;
bool undergroundTriggered = false;

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
void checkForCoinsCollected(Mat frame, Mat temp);
void checkForCoinsCollected(Mat frame, Mat temp);
void checkForUndergroundCoins(Mat frame, Mat undergroundCoins[]);

int main()
{
    char keyPress;
    cout << "p2b_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2c\\p2c_mario_1.mp4");
    processVideo(cap1, "p2c_mario_1.mp4", "p2c_output1.avi");
    numCoins = 0;

    // TODO: Make a new template for the new window size
    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2c\\p2c_mario_2.mp4");
    processVideo(cap2, "p2c_mario_2.mp4", "p2c_output2.avi");
    numCoins = 0;

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

    // Obtain the template for the coin collected
    Mat coinCollectedTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinCollectedTemp.png");
    Mat coinBrightTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinUndergroundBright.png");
    Mat coinMidTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinUndergroundMid.png");
    Mat coinDarkTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinUndergroundDark.png");

    Mat coins[] = {coinBrightTemp, coinMidTemp, coinDarkTemp};

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

      checkForCoinsCollected(frame, coinCollectedTemp);
      checkForUndergroundCoins(frame, coins);

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

// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
// This code is based on the solution at this link
// This function checks if any coins were collected in the current frame, and if so, increments the coin counter on the frame
void checkForCoinsCollected(Mat frame, Mat temp) {
    Mat src;
    cvtColor(frame, src, COLOR_BGR2GRAY);
    cvtColor(temp, temp, COLOR_BGR2GRAY);

    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    double thresh = 0.99;
    threshold(result, result, thresh, 1., THRESH_BINARY);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    result.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Find the maximum matching location
    Point max_point;
    double max_val;
    minMaxLoc(result, NULL, &max_val, NULL, &max_point, noArray());

    // Draw the font in different colors
    if (max_val > 0) {
        numCoins++;
    }

    string text = "# Coins = " + std::to_string(numCoins);
    putText(frame, text, Point(1400, 50), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255), 1);
}

// This function checks if any fire projectiles are sent from Mario
void checkForFireProjectiles(Mat frame, Mat temp) {
    Mat src;
    cvtColor(frame, src, COLOR_BGR2GRAY);
    cvtColor(temp, temp, COLOR_BGR2GRAY);

    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    double thresh = 0.99;
    threshold(result, result, thresh, 1., THRESH_BINARY);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    result.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Find the maximum matching location
    Point max_point;
    double max_val;
    minMaxLoc(result, NULL, &max_val, NULL, &max_point, noArray());

    // Draw the font in different colors
    if (max_val > 0) {
        numFire++;
    }

    string text = "# Coins = " + std::to_string(numFire);
    putText(frame, text, Point(1400, 100), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255), 1);
}

// This method will manage checking for underground coins and, if found, will update the coin counter.
void checkForUndergroundCoins(Mat frame, Mat undergroundCoins[]) {
    // Determine number of coins in frame
    int coinCounter = 0;
    for (int i = 0; i < 3; i++) {
        Mat temp = undergroundCoins[i];

        // Match the A template on the grid
        Mat1f result;
        matchTemplate(frame, temp, result, TM_CCOEFF_NORMED);

        // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
        double thresh = 0.95;
        threshold(result, result, thresh, 1., THRESH_BINARY);

        // Convert result to CV_8U to support finding contours
        Mat resb;
        result.convertTo(resb, CV_8U, 255);

        // Find the contours of the grayscale match result (these will be all the points where A's are located)
        vector<vector<Point>> contours;
        findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

        // Process each matching A
        coinCounter += contours.size();
    }

    // Update the coin counter
    if (undergroundTriggered && coinCounter == 0) {
        return;
    } else if (coinCounter > 0) {
        if (lastFrameCoins == 0) {
            lastFrameCoins = coinCounter;
        } else {
            numCoins += (lastFrameCoins-coinCounter);
            lastFrameCoins = coinCounter;
            undergroundTriggered = true;
        }
    }
}
