#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

int score[] = {0, 0, 0, 0, 0};
void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
void processTemplateMatching(Mat frame, Mat temp, double thresh);
void printScoreInTopRight();

int main()
{
    char keyPress;
    cout << "p4_opencv_code.cpp\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\input4_1.avi");
    processVideo(cap1, "input4_1.avi", "p4_output1.avi");
    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\input4_2.avi");
    processVideo(cap2, "input4_2.avi", "p4_output2.avi");

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

    // Read in number templates
    Mat zero = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\0.jpeg");
    Mat one = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\1.jpeg");
    Mat two = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\2.jpeg");
    Mat three = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\3.jpeg");
    Mat four = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\4.jpeg");
    Mat five = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\5.jpeg");
    Mat six = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\6.jpeg");
    Mat seven = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\7.jpeg");
    Mat eight = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\8.jpeg");
    Mat nine = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part4\\digits\\9.jpeg");

    Mat numberTemps[] = {zero, one, two, three, four, five, six, seven, eight, nine};
    int numbers[] = {0,1,2,3,4,5,6,7,8,9};

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

      // Process the templates and print the high scores
      for (int i = 0; i < 10; i++) {
          processTemplateMatching(frame, numberTemps[i], numbers[i]);
      }

      // Print the score in the top right corner of the grid
      printScoreInTopRight();

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
void processTemplateMatching(Mat frame, Mat temp, int number) {
    Mat src;
    cvtColor(frame, src, COLOR_BGR2GRAY);

    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    double thresh = 0.95;
    threshold(result, result, thresh, 1., THRESH_BINARY);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    result.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
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

        // Map the matched template to the right hand corner

    }
}

void printScoreInTopRight() {

}
