#include <iostream>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void processVideo(VideoCapture cap);
void findPersonAndDrawTargets(Mat frame, Mat mask);
void detectFacePosition(Mat frame);
void detectBasketballPosition(Mat frame, Mat mask);
void determineBallTargetIntersection();

Rect personLocation;
Rect basketballLocation;
Rect leftTarget;
Rect rightTarget;
Point intersectionPoint;
int maxNumReps;
int numCompletedDribbles;
int numLookDowns = 0;
bool lastLeftTarget = false;
int lastFrameFaceDetected = -10;
int frameNum = 0;

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

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
    pBackSub = createBackgroundSubtractorKNN(100, 100.0, true);
    Mat fgMask;

    HOGDescriptor hog = HOGDescriptor();
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    // Start the stopwatch
    auto start = std::chrono::high_resolution_clock::now();

    // Create a video writer and process the input video frame by frame
    while(1)
    {
      // Ready in a frame at a time
      Mat frame;
      cap >> frame;

      frameNum++;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Run the background subtraction model
      pBackSub->apply(frame, fgMask);

      findPersonAndDrawTargets(frame, fgMask);
      detectBasketballPosition(frame, fgMask);
      determineBallTargetIntersection();

      // Write the frame into the output video file
//      video.write(frame);

      // Display the information on the screen
      string text = "#Reps = " + std::to_string(numCompletedDribbles);
      putText(frame, text, Point(10, 25), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
      text = "#Look Downs = " + std::to_string(numLookDowns);
      putText(frame, text, Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
      auto finish = std::chrono::high_resolution_clock::now();
      text = "Time: " + std::to_string((finish-start).count());
      putText(frame, text, Point(10, 75), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);

      // Detect vechicles from the background subtraction mask
      imshow("fgMask", fgMask);
      imshow("frame", frame);

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
void findPersonAndDrawTargets(Mat frame, Mat mask) {
    threshold(mask, mask, 200, 255, THRESH_BINARY);

    int width = 10;
    Mat element = getStructuringElement( MORPH_RECT,
                       Size( 2*(0+1) + 1, 2*width+1 ),
                       Point( 0+1, width ) );
    dilate( mask, mask, element );

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

        if (br.area() > 50000) {
            // Draw the bounding box around the vehicle
            rectangle(frame, br, Scalar(0, 255, 0), 5);
            drawContours(mask, contours, i, Scalar(255, 255, 255), -1);
            personLocation = br;
            break;
        }
    }

    detectFacePosition(frame);
}

// Detect's the user's face in the frame and ensures they are looking up when dribbling
void detectFacePosition(Mat frame) {
    // Convert image to grayscale for face detection
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    // Detect the faces from the image
    bool faceDetected = false;
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
        faceDetected = true;
        break;
    }

    // Increment number of look downs if no face is detected
    if (!faceDetected && frameNum-lastFrameFaceDetected > 10) {
       numLookDowns++;
       lastFrameFaceDetected = frameNum;
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

        if (br.area() > 5000 && br.y > personLocation.y+personLocation.height/4) {
            // Draw the bounding box around the vehicle
            rectangle(frame, br, Scalar(0, 0, 255), 5);
            basketballLocation = br;
            break;
        }
    }

    // Draw the target's on the screen
    leftTarget = Rect(personLocation.x+personLocation.width/2-200, personLocation.y+personLocation.height/2, basketballLocation.width, basketballLocation.height);
    rightTarget = Rect(personLocation.x+personLocation.width/2+100, personLocation.y+personLocation.height/2, basketballLocation.width, basketballLocation.height);

    rectangle(frame, leftTarget, Scalar(0, 255, 0), 5);
    rectangle(frame, rightTarget, Scalar(0, 255, 0), 5);
}

// ======================= New Functions ===================================

// Determines if there was an intersection between the basketball and a target location
void determineBallTargetIntersection() {
    // Determine if and where an intersection occurred
    if (((basketballLocation & leftTarget).area() > 0) && !lastLeftTarget) {
        // Intersection occurred on the left side, count it
        numCompletedDribbles++;
        lastLeftTarget = true;
    } else if (((basketballLocation & rightTarget).area() > 0) && lastLeftTarget) {
        // Intersection occurred on the right side, count it
        numCompletedDribbles++;
        lastLeftTarget = false;
    }
}

// Have the user select the type of dribble drill, the number of reps or time
// Find the location of the basketball and put a box around it
    // Store the basketball's location
// Find the location of the person and draw a box around them
    // Create a target on each side of the detected person that is the size of the basketball
    // Store the target's location
// Detect whether the basketball intersects the target position
    // If so, ensure that the intersection is a threshold distance away from the last detected intersection
    // If so, increment the successful dribble counter
// For face detection, increment the face down counter when the face is not detected on the screen
    // Only increment this value every nth frame
// Display the number of reps completed, number of head down situations, and time in each frame
