//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/xfeatures2d.hpp>

//using namespace std;
//using namespace cv;

//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
//void processTemplateMatching(Mat src, Mat temp, double thresh);

//int main()
//{
//    char keyPress;
//    cout << "p2a_opencv_code\n";

//    Mat env = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallRightEnv.png", IMREAD_GRAYSCALE);
//    Mat smallFace = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallRightFace.png", IMREAD_GRAYSCALE);

//    //-- Step 1: Detect the keypoints using SIFT Detector, compute the descriptors
//    int minHessian = 400;
//    Ptr<KAZE> detector = KAZE::create( minHessian );
//    std::vector<KeyPoint> keypoints1, keypoints2;
//    Mat descriptors1, descriptors2;
//    detector->detectAndCompute( smallFace, noArray(), keypoints1, descriptors1 );
//    detector->detectAndCompute( env, noArray(), keypoints2, descriptors2 );

//    //-- Step 2: Matching descriptor vectors with a FLANN based matcher
//    // Since SIFT is a floating-point descriptor NORM_L2 is used
//    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
//    std::vector< std::vector<DMatch> > knn_matches;
//    matcher->knnMatch( descriptors2, descriptors1, knn_matches, 2 );
//    //-- Filter matches using the Lowe's ratio test
//    const float ratio_thresh = 100.0f;
//    std::vector<DMatch> good_matches;
//    for (size_t i = 0; i < knn_matches.size(); i++)
//    {
////        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
////        {
//            good_matches.push_back(knn_matches[i][0]);
////        }
//    }
//    //-- Draw matches
//    Mat img_matches;
//    drawMatches( env, keypoints2, smallFace, keypoints1, good_matches, img_matches, Scalar::all(-1),
//                 Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
//    //-- Show detected matches
//    imshow("Good Matches", img_matches );

////    //-- Step 1: Detect the keypoints using SURF Detector
////    int minHessian = 400;
////    Ptr<SIFT> detector = SIFT::create( minHessian );
////    std::vector<KeyPoint> keypoints;
////    detector->detect( smallFace, keypoints );
////    //-- Draw keypoints
////    Mat img_keypoints;
////    drawKeypoints( smallFace, keypoints, img_keypoints );
////    //-- Show detected (drawn) keypoints
////    imshow("SURF Keypoints", img_keypoints );



////    processTemplateMatching(env, smallFace);

//    // Read input videos
////    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_1.mp4");
////    processVideo(cap1, "p2a_mario_1.mp4", "p2a_output1.avi");
////    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_2.mp4");
////    processVideo(cap2, "p2a_mario_2.mp4", "p2a_output2.avi");
////    VideoCapture cap3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_3.mp4");
////    processVideo(cap3, "p2a_mario_3.mp4", "p2a_output3.avi");

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

////// Processes the video by converting it to grayscale and writing it to the output
////// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
////// The code from the source was modified to support the functionality of this assignment
////void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName) {
////    // Check if camera opened successfully
////    if(!cap.isOpened())
////    {
////      cout << "Error opening video stream" << endl;
////      return;
////    }

////    // Default resolution of the frame is obtained.The default resolution is system dependent.
////    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
////    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

////    Mat marioSmallLeftEnv = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallLeftFace.png", IMREAD_GRAYSCALE);
////    Mat marioSmallRightEnv = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallRightFace.png", IMREAD_GRAYSCALE);
////    Mat marioSmallTurningLeftEnv = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallTurningLeftFace.png", IMREAD_GRAYSCALE);
////    Mat marioSmallTurningRightEnv = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallTurningRightFace.png", IMREAD_GRAYSCALE);

////    // Create a video writer and process the input video frame by frame
////    int frameNum = 0;
////    printf("Processing video %s...\n", inputVideoName.c_str());
////    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),60, Size(frame_width,frame_height));
////    while(1)
////    {
////      // Ready in a frame at a time
////      Mat frame;
////      cap >> frame;

////      // If the frame is empty, break immediately
////      if (frame.empty())
////        break;

//////      imwrite("frame" + std::to_string(frameNum++) + ".png", gray);

////      processTemplateMatching(frame, marioSmallLeftEnv, 0.68);
////      processTemplateMatching(frame, marioSmallRightEnv, 0.68);
////      processTemplateMatching(frame, marioSmallTurningLeftEnv, 0.68);
////      processTemplateMatching(frame, marioSmallTurningRightEnv, 0.68);
//////      imshow("frame", frame);

////      // Write the frame into the output video file
////      video.write(frame);

////      // Press  ESC on keyboard to  exit
////      char c = (char)waitKey(1);
////      if( c == 27 )
////        break;
////    }

////    // Clean up video capture and writer
////    cap.release();
////    video.release();

////    // Closes all the windows
////    destroyAllWindows();

////    printf("Video processing complete for %s!\n", outputVideoName.c_str());
////}

////// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
////// This code is based on the solution at this link
////void processTemplateMatching(Mat frame, Mat temp, double thresh) {
////    Mat src;
////    cvtColor(frame, src, COLOR_BGR2GRAY);

////    // Match the A template on the grid
////    Mat1f result;
////    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

////    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
////    threshold(result, result, thresh, 1., THRESH_BINARY);

////    // Convert result to CV_8U to support finding contours
////    Mat resb;
////    result.convertTo(resb, CV_8U, 255);

////    // Find the contours of the grayscale match result
////    vector<vector<Point>> contours;
////    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

////    // Find the maximum matching location
////    Point max_point;
////    double max_val;
////    minMaxLoc(result, NULL, &max_val, NULL, &max_point, noArray());

////    // Draw the font in different colors
////    if (max_val > 0) {
////        rectangle(frame, Rect(max_point.x-10, max_point.y, temp.cols+25, temp.rows+40), Scalar(0, 255, 255), 5);
////    }
////}
