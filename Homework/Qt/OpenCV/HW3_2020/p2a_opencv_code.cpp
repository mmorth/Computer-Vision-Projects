#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
void processTemplateMatching(Mat src, Mat temp);

int main()
{
    char keyPress;
    cout << "p2a_opencv_code\n";

    Mat env = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallEnv.png", IMREAD_GRAYSCALE);
    Mat smallFace = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\smallMarioFace.png", IMREAD_GRAYSCALE);

    processTemplateMatching(env, smallFace);

    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_1.mp4");
//    processVideo(cap1, "p2a_mario_1.mp4", "p2a_output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_2.mp4");
//    processVideo(cap2, "p2a_mario_2.mp4", "p2a_output2.avi");
//    VideoCapture cap3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_3.mp4");
//    processVideo(cap3, "p2a_mario_3.mp4", "p2a_output3.avi");

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

      imwrite("frame" + std::to_string(frameNum++) + ".png", frame);

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

// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
// This code is based on the solution at this link
void processTemplateMatching(Mat src, Mat temp) {
    Ptr<FeatureDetector> detector = ORB::create();
    vector<KeyPoint> kpT;
    Mat descT;
    detector->detectAndCompute(temp, noArray(), kpT, descT);
    vector<KeyPoint> kpG;
    Mat descG;
    detector->detectAndCompute(src, noArray(), kpG, descG);

    BFMatcher bf = BFMatcher(NORM_HAMMING, true);
    vector<DMatch> matches;
    bf.match(descT, descG, matches);

    Mat res;
    drawMatches(temp, kpT, src, kpG, matches, res);

    imshow("result", res);

//    // Match the A template on the grid
//    Mat1f result;
//    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

//    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
//    double thresh = 0.95;
//    threshold(result, result, thresh, 1., THRESH_BINARY);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    result.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Process each matching A
//    for (uint i=0; i<contours.size(); ++i)
//    {
//        // Mask out all other matching A's except the one that corresponds to the current contour
//        Mat mask(result.rows, result.cols, uchar(0));
//        drawContours(mask, contours, i, Scalar(255), FILLED);

//        // Find the maximum matching location
//        Point max_point;
//        double max_val;
//        minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);

//        // Draw the font in different colors
//        rectangle(src, Rect(max_point.x, max_point.y, temp.cols, temp.rows), Scalar(0, 0, 255), 5);
//    }
}
