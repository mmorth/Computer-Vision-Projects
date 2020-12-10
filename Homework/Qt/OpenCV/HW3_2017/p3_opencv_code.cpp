//#include "opencv2/objdetect.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/videoio.hpp"
//#include <iostream>

//using namespace std;
//using namespace cv;

//void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
//void detectAndDisplay( Mat frame );

//CascadeClassifier face_cascade;
//CascadeClassifier eyes_cascade;


//int main()
//{
//    //-- 1. Load the cascades
//    String face_cascade_name = samples::findFile( "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml" );
//    String eyes_cascade_name = samples::findFile( "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml" );
//    if( !face_cascade.load( face_cascade_name ) )
//    {
//        cout << "--(!)Error loading face cascade\n";
//        return -1;
//    };
//    if( !eyes_cascade.load( eyes_cascade_name ) )
//    {
//        cout << "--(!)Error loading eyes cascade\n";
//        return -1;
//    };

//    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2015\\face_counting1.avi");
//    processVideo(cap1, "face_counting1.avi", "output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2015\\face_counting2.avi");
//    processVideo(cap2, "face_counting2.avi", "output2.avi");

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

//    // Create a video writer and process the input video frame by frame
//    int frameNum = 0;
//    printf("Processing video %s...\n", inputVideoName.c_str());
//    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height), true);
//    while(1)
//    {
//      // Ready in a frame at a time
//      Mat frame;
//      cap >> frame;

//      // If the frame is empty, break immediately
//      if (frame.empty())
//        break;

////      detectAndDisplay( frame );
////      imshow("frame", frame);

//      // Write the frame into the output video file
////      video.write(frame);

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

//void detectAndDisplay( Mat frame )
//{
//    Mat frame_gray;
//    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
//    equalizeHist( frame_gray, frame_gray );
//    //-- Detect faces
//    std::vector<Rect> faces;
//    face_cascade.detectMultiScale( frame_gray, faces );
//    for ( size_t i = 0; i < faces.size(); i++ )
//    {
//        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
//        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
//        Mat faceROI = frame_gray( faces[i] );
//        //-- In each face, detect eyes
//        std::vector<Rect> eyes;
//        eyes_cascade.detectMultiScale( faceROI, eyes );
//        for ( size_t j = 0; j < eyes.size(); j++ )
//        {
//            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
//            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
//            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
//        }
//    }
//    //-- Show what you got
//    imshow( "Capture - Face detection", frame );
//}
