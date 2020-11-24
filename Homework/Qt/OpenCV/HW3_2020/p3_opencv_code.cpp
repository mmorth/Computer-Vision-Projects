// TODO: Filter out the outer gray border
//     Use that information to find the bottom and side of the Tetris board
// Adjust the bottom and side logic from the previous implementation to use this new location
// Update the size (and maybe the color) of the Tetris squares




#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

bool bottomLineFull[5] = {false, false, false, false, false};
int linesCleared = 0;
int board[5][10];

void updateBoardSquares(Mat frame, int top, int left);
void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);

int main()
{
    char keyPress;
    cout << "p1c_opencv_code\n";


    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_3\\p3_tetris_1.mp4");
//    processVideo(cap1, "p3_tetris_1.mp4", "p3_output1.avi");
//    linesCleared = 0;
    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_3\\p3_tetris_2.mp4");
    processVideo(cap2, "p3_tetris_2.mp4", "p3_output2.avi");

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
    int frameNum = 0;
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),60, Size(frame_width,frame_height));
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Find the frame of the window to determine where the board region is
      Mat mask;
      inRange(frame, Scalar(110, 110, 110), Scalar(120, 120, 120), mask);

      // Convert result to CV_8U to support finding contours
      Mat resb;
      mask.convertTo(resb, CV_8U, 255);

      // Find the contours of the grayscale match result
      vector<vector<Point>> contours;
      findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

      int top, left;
      for (int i = 0; i < contours.size(); i++) {
          if (contourArea(contours[i]) > 800000 && contourArea(contours[i]) < 900000) {
              // Store the board dimensions
              Rect br = boundingRect(contours[i]);
              top = br.y;
              left = br.x;
          }
      }

      updateBoardSquares(frame, top, left);

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

// Populates the board square positions
void updateBoardSquares(Mat frame, int top, int left) {
    // Loop through the bottom 5 rows of the board
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 10; col++) {
            Vec3b color = frame.at<Vec3b>((top+1000)+(64*row), left+40+(col*64));
            if (color.val[0] < 5 && color.val[1] < 5 && color.val[2] < 5) {
                board[row][col] = 0;
            } else {
                board[row][col] = 1;
            }
        }
    }

    // Check if the last row is all 1s. If so, check upper rows for multi-line clear
    bool rowOnes = true;
    int increaseAmount = 0;
    for (int row = 0; row < 5 && rowOnes; row++) {
        rowOnes = false;
        for (int col = 0; col < 10; col++) {
            if (board[4-row][col] == 1) {
                rowOnes = true;
                continue;
            } else {
                rowOnes = false;
                bottomLineFull[4-row] = false;
                break;
            }
        }
        // Only increment the number of cleared rows is the new frame does not have a full bottom row (do not double count clears between multiple frames)
        if (rowOnes && !bottomLineFull[4-row]) {
            bottomLineFull[4-row] = true;
            increaseAmount++;
        }
    }

    // Increment the number of cleared lines by that amount
    linesCleared += increaseAmount;

    // Display text on the frame
    string text = "# lines cleared = " + std::to_string(linesCleared);
    putText(frame, text, Point(10,50), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255), 3);
}
