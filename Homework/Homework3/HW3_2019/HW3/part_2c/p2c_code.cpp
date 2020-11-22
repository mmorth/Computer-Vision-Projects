#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

bool lastLeftState = false;
int sevenSegmentState[8];
bool ledState[26];

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
Mat createGridMask(Mat frame);
void processLEDState(Mat frame, Mat mask);
void getFormattedFileOutput(ofstream& displayBoardFile);
void processTemplateMatching(Mat src, Mat temp, int num);
void drawLEDState(Mat frame);

int main()
{
    char keyPress;
    cout << "p2c_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\part_2c\\input2c_small.mp4");
    processVideo(cap1, "input2a_small.mp4", "p2c_output1.avi");

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

    // Read in the templates for each digit
    Mat zero = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit0Template.png");
    Mat one = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit1Template.png");
    Mat two = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit2Template.png");
    Mat three = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit3Template.png");
    Mat four = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit4Template.png");
    Mat five = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit5Template.png");
    Mat six = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit6Template.png");
    Mat seven = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit7Template.png");
    Mat eight = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit8Template.png");
    Mat nine = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\digit9Template.png");
    Mat numTemps[] = {zero, one, two, three, four, five, six, seven, eight, nine};
    int numbers[] = {0,1,2,3,4,5,6,7,8,9};

    // Write to the output file
    ofstream displayBoardFile("diplay_board_state.txt");

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

      // Process seven segment display values
      for (int i = 0; i < 10; i++) {
        processTemplateMatching(frame, numTemps[i], numbers[i]);
      }

      // Process and determine the LED states
      Mat mask = createGridMask(frame);
      processLEDState(frame, mask);
      drawLEDState(frame);

      // Write the frame into the output video file
      video.write(frame);

      // See if we need to write the current state to the output file
      getFormattedFileOutput(displayBoardFile);

      // Press  ESC on keyboard to  exit
      char c = (char)waitKey(1);
      if( c == 27 )
        break;
    }

    // Clean up video capture and writer
    cap.release();
    video.release();
    displayBoardFile.close();

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

    // Convert result to CV_8U to support finding contours
    Mat resb;
    mask.convertTo(resb, CV_8U, 255);

    // Each contours corresponds to a square
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Map the brick location to the correct column
    for (int i = 0; i < contours.size(); i++) {
        Rect br = boundingRect(contours[i]);
        if (contourArea(contours[i]) > 10) {
            int centerX = br.x+br.width/2;
            ledState[(centerX-33)/30] = true;
        }
    }
}

// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
// This code is based on the solution at this link
// Finds the location of the digit templates and draws the digit above it
void processTemplateMatching(Mat src, Mat temp, int num) {
    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    double thresh = 0.9;
    threshold(result, result, thresh, 1., THRESH_BINARY);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    result.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result (these will be all the points where A's are located)
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Process each matching A
    for (uint i=0; i<contours.size(); ++i)
    {
        // Mask out all other matching A's except the one that corresponds to the current contour
        Mat mask(result.rows, result.cols, uchar(0));
        drawContours(mask, contours, i, Scalar(255), FILLED);

        // Find the maximum matching location
        Point max_point;
        double max_val;
        minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);

        // Set the seven segment display state
        putText(src, std::to_string(num), Point(max_point.x, max_point.y-30), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 1);

        if (max_point.x < 50) {
            sevenSegmentState[0] = num;
        } else if (max_point.x < 80) {
            sevenSegmentState[1] = num;
        } else if (max_point.x < 150) {
            sevenSegmentState[2] = num;
        } else if (max_point.x < 180) {
            sevenSegmentState[3] = num;
        } else if (max_point.x < 270) {
            sevenSegmentState[4] = num;
        } else if (max_point.x < 300) {
            sevenSegmentState[5] = num;
        } else if (max_point.x < 330) {
            sevenSegmentState[6] = num;
        } else if (max_point.x < 370) {
            sevenSegmentState[7] = num;
        }
    }
}

// Returns the string with the formatted file output
void getFormattedFileOutput(ofstream& displayBoardFile) {
    // If the rightmost green LED is on, output the seven segment display values and LED values to a text file
    if (lastLeftState != ledState[25]) {
        lastLeftState = ledState[25];

        // Output to file
        string line = "";

        // Print the values of the first 6 red LEDs
        for (int i = 0; i < 6; i++) {
            string state = (ledState[i]) ? "1" : "0";
            line += state;
        }

        // Print the tab character
        line += '\t';

        // Print the values of the last 8 red LEDs
        for (int i = 10; i < 18; i++) {
            string state = (ledState[i]) ? "1" : "0";
            line += state;
        }

        // Print the tab character
        line += '\t';

        // Print the values of the last 8 red LEDs
        for (int i = 20; i < 22; i++) {
            string state = (ledState[i]) ? "1" : "0";
            line += state;
        }

        // Print the tab character
        line += '\t';

        // Print the values of the last 8 red LEDs
        for (int i = 2; i < 4; i++) {
            line += std::to_string(sevenSegmentState[i]);
        }

        // Print the newline character
        line += '\n';

        // Add the line to the output file
        displayBoardFile << line;
    }

    // Reset the LED state
    for (int i = 0; i < 26; i++) {
        ledState[i] = 0;
    }
}

// Draws the LED states above each LED on the frame
void drawLEDState(Mat frame) {
    ledState[22] = 0;
    for (int i = 0; i < 26; i++) {
        if (ledState[i]) {
            putText(frame, "1", Point(35+30*i, 175), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 1);
        } else {
            putText(frame, "0", Point(35+30*i, 175), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255), 1);
        }
    }
}
