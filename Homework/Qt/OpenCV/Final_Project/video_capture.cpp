#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void processVideo(VideoCapture cap);
void findPersonAndDrawTargets(Mat frame, Mat mask, HOGDescriptor hog);
void detectFacePosition(Mat frame);
void detectBasketballPosition(Mat frame, Mat mask);

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
int numDribbles = 0;

int main()
{
    cout << "final_project_code\n";

    //-- 1. Load the cascades
    String face_cascade_name = samples::findFile( "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml" );
    String eyes_cascade_name = samples::findFile( "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml" );
    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    if( !eyes_cascade.load( eyes_cascade_name ) )
    {
        cout << "--(!)Error loading eyes cascade\n";
        return -1;
    };

    // Read input videos
    VideoCapture cap(1);
    processVideo(cap);

    return 0;
}

// Processes the video by converting it to grayscale and writing it to the output
// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
// The code from the source was modified to support the functionality of this assignment
void processVideo(VideoCapture cap) {
    // Check if camera opened successfully
    if(!cap.isOpened())
    {
      cout << "Error opening video stream" << endl;
      return;
    }

    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorKNN(100, 400.0, false);
    Mat fgMask;

    HOGDescriptor hog = HOGDescriptor();
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    // Create a video writer and process the input video frame by frame
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Run the background subtraction model
      pBackSub->apply(frame, fgMask);

      findPersonAndDrawTargets(frame, fgMask, hog);
      detectBasketballPosition(frame, fgMask);

      // Detect vechicles from the background subtraction mask
      imshow("frame", frame);
      imshow("fgMask", fgMask);

      // Write the frame into the output video file
//      video.write(frame);

      // Press  ESC on keyboard to  exit
      char c = (char)waitKey(1);
      if( c == 27 )
        break;
    }

    // Clean up video capture and writer
    cap.release();

    // Closes all the windows
    destroyAllWindows();
}

// Detects the person in the frame and draws the target ball positions on the screen
void findPersonAndDrawTargets(Mat frame, Mat mask, HOGDescriptor hog) {

    int width = 10;
    Mat element = getStructuringElement( MORPH_RECT,
                       Size( 2*(0+1) + 1, 2*width+1 ),
                       Point( 0+1, width ) );
    dilate( mask, mask, element );

    //    medianBlur(mask, mask, 3);
//    // Threshold to pull out the main part of the object
//    threshold(mask, mask, 200, 255, THRESH_BINARY);
//    int width = 1;
//    Mat element = getStructuringElement( MORPH_RECT,
//                       Size( 2*(0+1) + 1, 2*width+1 ),
//                       Point( 0+1, width ) );
//    erode( mask, mask, element );
//    dilate( mask, mask, element );

//    // Create the countour for the person
//    medianBlur(mask, mask, 21);
//    width = 100;
//    element = getStructuringElement( MORPH_RECT,
//                           Size( 2*(width+1) + 1, 2*width+1 ),
//                           Point( width+1, width ) );
//  //  dilate( src, dilation_dst, element );
//    morphologyEx( mask, mask, MORPH_CLOSE, element );

    // Convert result to CV_8U to support finding contours
    Mat resb;
    mask.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Determine whether detected objects are a vehicle or not
    for (int i = 0; i < contours.size(); i++) {
        // Determine which type of object is detected
        Rect br = boundingRect(contours[i]);

        if (br.area() > 10000) {
            // Draw the bounding box around the vehicle
            rectangle(frame, br, Scalar(0, 255, 0), 5);
            drawContours(mask, contours, i, Scalar(255, 255, 255), -1);
        }
    }

    detectFacePosition(frame);
}

// Detect's the user's face in the frame and ensures they are looking up when dribbling
void detectFacePosition(Mat frame) {
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
        Mat faceROI = frame_gray( faces[i] );
        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale( faceROI, eyes );
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
        }
    }
}

// Detects the basketball's position in the frame to see if it is in the target position
void detectBasketballPosition(Mat frame, Mat mask) {
    Mat ballMask, frameHSV;
    // Convert from BGR to HSV colorspace
    cvtColor(frame, frameHSV, COLOR_BGR2HSV);
    // Detect the object based on HSV Range Values
    inRange(frameHSV, Scalar(0, 66, 70), Scalar(12, 255, 255), ballMask);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    ballMask.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Determine whether detected objects are a vehicle or not
    for (int i = 0; i < contours.size(); i++) {
        // Determine which type of object is detected
        Rect br = boundingRect(contours[i]);

        if (br.area() > 10000) {
            // Draw the bounding box around the vehicle
            rectangle(frame, br, Scalar(0, 0, 255), 5);
        }
    }
}
