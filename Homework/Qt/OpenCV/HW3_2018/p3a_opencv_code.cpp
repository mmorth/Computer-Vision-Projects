//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//bool firstPoint = true;
//Point lastPoint;
//void markPacmanPath(Mat frame, Mat mask, Mat path);
//Mat createGridMask(Mat frame);
//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);

//int main()
//{
//    char keyPress;
//    cout << "p3a_opencv_code\n";

//    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part3a\\input3a1.avi");
//    processVideo(cap1, "input3a1.avi", "p3a_output1.avi");
//    lastPoint = Point(1, 1);
//    firstPoint = true;
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\part3a\\input3a2.avi");
//    processVideo(cap2, "input3a2.avi", "p3a_output2.avi");

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

//    // Create a Mat that will store Pacman's path
//    Mat path(Size(frame_width, frame_height), 16);
//    path = Scalar(0,0,0);

//    // Create a video writer and process the input video frame by frame
//    printf("Processing video %s...\n", inputVideoName.c_str());
//    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height));
//    while(1)
//    {
//      // Ready in a frame at a time
//      Mat frame;
//      cap >> frame;

//      // If the frame is empty, break immediately
//      if (frame.empty())
//        break;

//      // Apply green color to Pacman in the frame
//      Mat mask = createGridMask(frame);
//      markPacmanPath(frame, mask, path);

//      // Write the frame into the output video file
//      video.write(frame);

//      // Press  ESC on keyboard to  exit
//      char c = (char)waitKey(1);
//      if( c == 27 )
//        break;
//    }

//    imwrite("path.png", path);

//    // Clean up video capture and writer
//    cap.release();
//    video.release();

//    // Closes all the windows
//    destroyAllWindows();

//    printf("Video processing complete for %s!\n", outputVideoName.c_str());
//}

//// Create a mask for the board to prevent matching of the Pacman representing the player's lives
//Mat createGridMask(Mat frame) {
//    Mat mask(Size(224, 288), 16);
//    mask = 0;
//    Rect roi(0, 0, 224, 270);
//    Mat temp = mask(roi);
//    temp = Scalar(255, 255, 255);
//    temp.copyTo(mask(roi));

//    Mat result;
//    bitwise_and(frame, mask, result);

//    return result;
//}

//// Colors Pacman green
//void markPacmanPath(Mat frame, Mat mask, Mat path) {
//    // Create the mask to isolate the Pacman colors
//    Mat yellowMask;
//    inRange(mask, Scalar(0, 200, 200), Scalar(210, 255, 255), yellowMask);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    yellowMask.convertTo(resb, CV_8U, 255);

//    // Find the contours that could correspond to Pacman
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Only draw the contours that are large enough (e.g. remove the noise of smaller objects with similar colors to Pacman)
//    for (int i = 0; i < contours.size(); i++) {
//        if (contourArea(contours[i]) > 100) {
//            // Find Pacman's center position
//            Rect br = boundingRect(contours[i]);
//            Vec3b color;
//            color.val[0] = 255;
//            color.val[1] = 255;
//            color.val[2] = 255;
//            Point curPoint = Point(br.x+br.width/2, br.y+br.height/2);
//            if (!firstPoint && abs(curPoint.x-lastPoint.x) < 100) {
//                // Add the line from the last point to the current point to the path
//                std::vector<cv::Point> contour;
//                contour.push_back(lastPoint);
//                contour.push_back(curPoint);
//                std::vector<std::vector<cv::Point> > contourVec;
//                contourVec.push_back(contour);

//                cv::drawContours(path,contourVec,0,color);
//                lastPoint = curPoint;
//            } else {
//                // Add the first point
//                lastPoint = curPoint;
//                firstPoint = false;
//            }
//        }
//    }

//    // Add the path to the frame
//    frame = frame + path;
//}
