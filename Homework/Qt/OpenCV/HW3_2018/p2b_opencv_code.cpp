//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//int numPellets = 0;
//Mat createLiveMask(Mat frame);
//void processFindLives(Mat frame, Mat mask, Mat temp);
//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);

//int main()
//{
//    char keyPress;
//    cout << "p2b_opencv_code\n";

//    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part2b\\input2b1.avi");
//    processVideo(cap1, "input2b1.avi", "p2b_output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part2b\\input2b2.avi");
//    processVideo(cap2, "input2b2.avi", "p2b_output2.avi");

//    while(1)
//    {
//        keyPress = waitKey();
//        // Press q key to close window
//        if (keyPress == 'q')
//        {
//            destroyAllWindows();
//            break;
//        }
//    }
//    return 0;
//}

//// Processes the video by converting it to grayscale and writing it to the output
//// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
//// The code from the source was modified to support the functionality of this assignment
//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName) {
//    // Check if camera opened successfully
//    if(!cap.isOpened())
//    {
//      cout << "Error opening video stream" << endl;
//      return;
//    }

//    // Default resolution of the frame is obtained.The default resolution is system dependent.
//    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
//    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

//    // Open PacMan life template
//    Mat liveTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\pacman_templates\\pacmanLifeTemplate.png");

//    // Create a video writer and process the input video frame by frame
//    printf("Processing video %s...\n", inputVideoName.c_str());
//    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height));
//    int frameNum = 0;
//    while(1)
//    {
//      // Ready in a frame at a time
//      Mat frame;
//      cap >> frame;

//      // If the frame is empty, break immediately
//      if (frame.empty())
//        break;

//      Mat mask = createLiveMask(frame);
//      processFindLives(frame, mask, liveTemp);

//      // Write the frame into the output video file
//      video.write(frame);

//      // Press  ESC on keyboard to  exit
//      char c = (char)waitKey(1);
//      if( c == 27 )
//        break;
//    }

//    // Clean up video capture and writer
//    cap.release();
//    video.release();

//    // Closes all the windows
//    destroyAllWindows();

//    printf("Video processing complete for %s!\n", outputVideoName.c_str());
//}

//Mat createLiveMask(Mat frame) {
//    Mat mask(Size(224, 288), 16);
//    mask = 0;
//    Rect roi(0, 270, 224, 18);
//    Mat temp = mask(roi);
//    temp = Scalar(255, 255, 255);
//    temp.copyTo(mask(roi));

//    Mat result;
//    bitwise_and(frame, mask, result);

//    return result;
//}

//// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
//// This code is based on the solution at this link
//void processFindLives(Mat frame, Mat mask, Mat temp) {
//    // Match the A template on the grid
//    Mat1f result;
//    matchTemplate(mask, temp, result, TM_CCOEFF_NORMED);

//    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
//    double thresh = 0.95;
//    threshold(result, result, thresh, 1., THRESH_BINARY);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    result.convertTo(resb, CV_8U, 255);

//    // Find the contours (representing pacman life templates of the grayscale match result)
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    string text = "# Lives = " + std::to_string(contours.size());
//    putText(frame,  text, Point(10,270), FONT_HERSHEY_TRIPLEX, .25, Scalar(255, 255, 255), 1);
//}
