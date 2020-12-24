//#include <iostream>
//#include <chrono>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//// Declare function placeholders
//void processVideo(VideoCapture cap);
//void findPersonAndDrawTargets(Mat frame, Mat mask);
//void detectFacePosition(Mat f, Mat mask);
//void detectBasketballPosition(Mat frame, Mat mask);
//void determineBallTargetIntersection(Rect basketballLocation);

//// Variables used for detection
//// Object locations
//Rect personLocation;
//Rect leftTarget;
//Rect rightTarget;
//Point intersectionPoint;
//vector<Rect> currentFrameObjects;
//vector<Rect> previousFrameObjects;
//// Counting variables
//int maxNumReps;
//int numCompletedDribbles;
//int numLookDowns = 0;
//bool lastLeftTarget = false;
//bool detectFaceFlag = false;
//int frameNum = 0;
//int conseqFrameHeadDown = 0;
//int conseqFrameFaceDetected = 0;
//// Frame variables
//int frame_width = 0;
//int frame_height = 0;

//// Store cascade classifier for face detection
//CascadeClassifier face_cascade;
//CascadeClassifier eyes_cascade;

//int main()
//{
//    cout << "final_project_code\n";

//    // Load the face cascade classifiers
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

//    // Capture real-time video from device's camera
//    VideoCapture cap(1);
//    processVideo(cap);

//    return 0;
//}

//// Processes the video by converting it to grayscale and writing it to the output
//// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
//// The code from the source was modified to support the functionality of this assignment
//void processVideo(VideoCapture cap) {
//    // Check if camera opened successfully
//    if(!cap.isOpened())
//    {
//      cout << "Error opening video stream" << endl;
//      return;
//    }

//    // Declare the background subtractor
//    Ptr<BackgroundSubtractor> pBackSub;
//    pBackSub = createBackgroundSubtractorKNN(100, 100.0, true);
//    Mat fgMask;

//    // Keep track of the elasped time for the current drill
//    auto start = chrono::steady_clock::now();

//    // Default resolution of the frame is obtained.The default resolution is system dependent.
//    frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
//    frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

//    // Create a video writer and process the input video frame by frame
//    VideoWriter video("dribbleVideo.avi",VideoWriter::fourcc('M','J','P','G'),10, Size(frame_width,frame_height));
//    while(1)
//    {
//      // Ready in a frame at a time
//      Mat frame;
//      cap >> frame;
//      frameNum++;

//      // If the frame is empty, break immediately
//      if (frame.empty())
//        break;

//      // Run the background subtraction model
//      pBackSub->apply(frame, fgMask);

//      // Detect object locations and draw on the screen
//      findPersonAndDrawTargets(frame, fgMask);
//      detectBasketballPosition(frame, fgMask);

//      // Display the information on the screen
//      string text = "#Reps = " + std::to_string(numCompletedDribbles);
//      putText(frame, text, Point(10, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(1, 255, 11), 3);
//      text = "#Look Downs = " + std::to_string(numLookDowns);
//      putText(frame, text, Point(10, 100), FONT_HERSHEY_SIMPLEX, 2, Scalar(1, 255, 11), 3);
//      auto finish = chrono::steady_clock::now();

//      // Use chrono to print the elasped drill time in Minutes:Seconds:Milliseconds format
//      char buffer [50];
//      long duration = std::chrono::duration_cast<chrono::milliseconds>(finish-start).count();
//      sprintf(buffer, "Time: %02d:%02d:%02d", duration/60000, (duration/1000)%60, duration%1000);
//      putText(frame, buffer, Point(10, 150), FONT_HERSHEY_SIMPLEX, 2, Scalar(1, 255, 11), 3);

//      // Display the frame on the screen
//      imshow("fgMask", fgMask);
//      imshow("frame", frame);

//      // Write the frame into the output video file
//      imwrite("frame" + std::to_string(frameNum) + ".png", frame);
//      imwrite("mask" + std::to_string(frameNum) + ".png", fgMask);
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
//}

//// Detects the person in the frame and draws the target ball positions on the screen
//void findPersonAndDrawTargets(Mat frame, Mat mask) {
//    // Threshold to remove weak background subtraction detections
//    threshold(mask, mask, 200, 255, THRESH_BINARY);

//    // Dislate to fill in the detected body more
//    int width = 10;
//    Mat element = getStructuringElement( MORPH_RECT,
//                       Size( 2*(0+1) + 1, 2*width+1 ),
//                       Point( 0+1, width ) );
//    dilate( mask, mask, element );

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    mask.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Determine all possible locations for the person
//    for (int i = 0; i < contours.size(); i++) {
//        // Determine which type of object is detected
//        Rect br = boundingRect(contours[i]);

//        // Only match person location if in certain location
//        if (br.area() > 50000) {
//            // Draw the bounding box around the vehicle
//            rectangle(frame, br, Scalar(0, 255, 0), 5);
//            drawContours(mask, contours, i, Scalar(255, 255, 255), -1);
//            personLocation = br;
//            break;
//        }
//    }

//    // Draw the target's on the screen
//    leftTarget = Rect(frame_width/2-200, personLocation.y+personLocation.height/2.5, 75, 75);
//    rightTarget = Rect(frame_width/2+150, personLocation.y+personLocation.height/2.5, 75, 75);

//    rectangle(frame, leftTarget, Scalar(0, 255, 0), 5);
//    rectangle(frame, rightTarget, Scalar(0, 255, 0), 5);

//    // Run the face detection
//    detectFacePosition(frame, mask);
//}

//// Detect's the user's face in the frame and ensures they are looking up when dribbling
//// Source: https://docs.opencv.org/master/db/d28/tutorial_cascade_classifier.html
//void detectFacePosition(Mat frame, Mat mask) {
//    // Convert image to grayscale for face detection
//    Mat frame_gray;
//    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
//    equalizeHist( frame_gray, frame_gray );

//    // Detect the faces from the image
//    bool faceDetected = false;
//    std::vector<Rect> faces;
//    face_cascade.detectMultiScale( frame_gray, faces, 1.5, 1 );
//    for ( size_t i = 0; i < faces.size(); i++ )
//    {
//        // Draw the location of the face
//        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
//        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
//        faceDetected = true;
//        break;
//    }

//    // Increment number of look downs if no face is detected
//    if (!faceDetected && detectFaceFlag) {
//       conseqFrameHeadDown++;
//       conseqFrameFaceDetected = 0;

//       if(conseqFrameHeadDown >= 10) {
//           numLookDowns++;
//           conseqFrameHeadDown = 0;
//           detectFaceFlag = false;
//       }
//    } else if (faceDetected && !detectFaceFlag) {
//        conseqFrameHeadDown = 0;
//        conseqFrameFaceDetected++;

//        if (conseqFrameFaceDetected >= 10) {
//            conseqFrameFaceDetected = 0;
//            detectFaceFlag = true;
//        }
//    } else if (!faceDetected) {
//        conseqFrameFaceDetected = 0;
//    } else if (faceDetected) {
//        conseqFrameHeadDown = 0;
//    }
//}

//// Detects the basketball's position in the frame to see if it is in the target position
//void detectBasketballPosition(Mat frame, Mat mask) {
//    Mat ballMask, frameHSV;
//    // Convert from BGR to HSV colorspace
//    cvtColor(frame, frameHSV, COLOR_BGR2HSV);

//    // Only search the non-background pixels for the basketball
//    threshold(mask, mask, 200, 255, THRESH_BINARY);
//    frameHSV.setTo(0, mask == 0);
//    imshow("frameHSV", frameHSV);

//    // Detect the object based on HSV Range Values
//    inRange(frameHSV, Scalar(0, 150, 150), Scalar(12, 220, 220), ballMask);

//    // Dilate to fill in the detected body more
//    int width = 30;
//    Mat element = getStructuringElement( MORPH_RECT,
//                       Size( 2*(width+1) + 1, 2*width+1 ),
//                       Point( width+1, width ) );
//    dilate( ballMask, ballMask, element );

//    imshow("ballMask", ballMask);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    ballMask.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Determine possible locations for the ball
//    for (int i = 0; i < contours.size(); i++) {
//        // Determine which type of object is detected
//        Rect br = boundingRect(contours[i]);

//        // Only match the ball if it meets certain parameters
//        printf("br.area() = %d\n", br.area());
//        if (br.area() > 1000 && br.area() < 15000) {
//            // Compute the centroid of the object
//            Point brCentroid = Point(br.x+br.width/2, br.y+br.height/2);

//            // Draw the bounding box around the vehicle
//            bool drawOnScreen = true;
//            for (int i = 0; i < previousFrameObjects.size(); i++) {
//                Point prevCentroid = Point(previousFrameObjects.at(i).x+previousFrameObjects.at(i).width/2, previousFrameObjects.at(i).y+previousFrameObjects.at(i).height/2);

//                double distance = cv::norm(brCentroid-prevCentroid);
//                // Check if the detect object's centroid is a minimum distance from an object detected in a previous frame
//                if (distance < 10) {
//                    drawOnScreen = false;
//                    break;
//                }
//            }

//            // Draw the object and detect intersection if the object has significantly moved between frames
//            if (drawOnScreen) {
//                rectangle(frame, br, Scalar(0, 0, 255), 5);
//                determineBallTargetIntersection(br);
//            }

//            currentFrameObjects.push_back(br);
//        }
//    }

//    previousFrameObjects = currentFrameObjects;
//    currentFrameObjects.clear();
//}

//// ======================= New Functions ===================================

//// Determines if there was an intersection between the basketball and a target location
//void determineBallTargetIntersection(Rect basketballLocation) {
//    // Determine if and where an intersection occurred
//    if (((basketballLocation & leftTarget).area() > 0) && !lastLeftTarget) {
//        // Intersection occurred on the left side, count it
//        numCompletedDribbles++;
//        lastLeftTarget = true;
//    } else if (((basketballLocation & rightTarget).area() > 0) && lastLeftTarget) {
//        // Intersection occurred on the right side, count it
//        numCompletedDribbles++;
//        lastLeftTarget = false;
//    }
//}
