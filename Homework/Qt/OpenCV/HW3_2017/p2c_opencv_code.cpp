//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//struct vehicle {
//    Rect br;
//    Point centroid;
//    int lastFrameSeen;
//    int direction = -1;
//};

//vector<vehicle> objects;

//void processVideo(VideoCapture cap, Mat firstFrame, string inputVideoName, string outputVideoName);
//void detectVehicles(Mat firstFrame, Mat videoFrame, Mat mask, int frameNum);
//void drawCarsOnFrame(Mat firstFrame, Mat videoFrame, Rect location);
//int checkExistingObjects(Rect br, int frameNum);
//void removeOldObjects(int frameNum);

//int numBuses = 0;
//int numCars = 0;
//int numPeople = 0;

//int main()
//{
//    cout << "p2c_opencv_code\n";

//    // Read input videos
//    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip1.avi");
//    Mat video1Frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\video1Frame.png");
//    processVideo(cap1, video1Frame, "clip1.avi", "output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip2.avi");
//    Mat video2Frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\video2Frame.png");
//    processVideo(cap2, video2Frame, "clip2.avi", "output2.avi");
//    VideoCapture cap3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip3.avi");
//    Mat video3Frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\video3Frame.png");
//    processVideo(cap3, video3Frame, "clip3.avi", "output3.avi");

//    return 0;
//}

//// Processes the video by converting it to grayscale and writing it to the output
//// Source: https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
//// The code from the source was modified to support the functionality of this assignment
//void processVideo(VideoCapture cap, Mat firstFrame, string inputVideoName, string outputVideoName) {
//    // Check if camera opened successfully
//    if(!cap.isOpened())
//    {
//      cout << "Error opening video stream" << endl;
//      return;
//    }

//    // Default resolution of the frame is obtained.The default resolution is system dependent.
//    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
//    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

//    Ptr<BackgroundSubtractor> pBackSub;
//    pBackSub = createBackgroundSubtractorKNN();
//    Mat fgMask;

//    // Create a video writer and process the input video frame by frame
//    int frameNum = 0;
//    printf("Processing video %s...\n", inputVideoName.c_str());
//    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height), true);
//    while(1)
//    {
//      // Ready in a frame at a time
//      Mat frame;
//      cap >> frame;
//      frameNum++;

//      // If the frame is empty, break immediately
//      if (frame.empty())
//        break;

//      Mat backgroundFrame = firstFrame.clone();

//      // Run the background subtraction model
//      pBackSub->apply(frame, fgMask);

//      // Detect vechicles from the background subtraction mask
//      detectVehicles(backgroundFrame, frame, fgMask, frameNum);
//      imshow("frame", frame);
//      imshow("backgroundFrame", backgroundFrame);

////      imwrite("frame" + std::to_string(frameNum) + ".png", frame);

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

//// Detect vehicles in the frame and count total number
//void detectVehicles(Mat firstFrame, Mat frame, Mat mask, int frameNum) {
//    // Threshold to pull out the main part of the object
//    threshold(mask, mask, 200, 255, THRESH_BINARY);
//    int width = 1;
//    Mat element = getStructuringElement( MORPH_RECT,
//                       Size( 2*(width+1) + 1, 2*width+1 ),
//                       Point( width+1, width ) );
//    dilate( mask, mask, element );
//    imshow("mask", mask);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    mask.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Determine whether detected objects are a vehicle or not
//    for (int i = 0; i < contours.size(); i++) {
//        // Determine which type of object is detected
//        Rect br = boundingRect(contours[i]);

//        // Ensure that the detected contour has the possibility of being a vehicle or person
//        if (contourArea(contours[i]) > 500 && br.y > 50 && br.height < 60 && br.height > 30) {
//            // Check whether this object is below min distance threshold to classify as other object
//            int vehicleNum = checkExistingObjects(br, frameNum);
//            if (vehicleNum == -1) {
//                // Add new detected vehicle to the frame
//                vehicle v;
//                v.br = br;
//                v.centroid = Point(br.x+br.width/2, br.y+br.height/2);
//                v.lastFrameSeen = frameNum;
//                objects.push_back(v);
//            } else {
//                // If vehicle is moving from left to right, draw on the frame
//                if (objects.at(vehicleNum).direction == 1) {
//                    // Car is traveling from left to right so draw it on the frame
//                    drawCarsOnFrame(firstFrame, frame, br);
//                }
//            }

//            // Draw the bounding box around the vehicle
//            rectangle(frame, br, Scalar(0, 0, 255), 1);
//        }
//    }

//    // Remove old objects from the frame
//    removeOldObjects(frameNum);
//}

//// Checks if the current object has already been identified in a prior frame
//int checkExistingObjects(Rect br, int frameNum) {
//    Point centroid = Point(br.x+br.width/2, br.y+br.height/2);
//    for (int i = 0; i < objects.size(); i++) {
//        // Check if distance between objects is less than threshold of 10 pixels
//        double distance = cv::norm(centroid-objects.at(i).centroid);
//        if (distance < 50) {
//            // Object has already been detected in prior frame, update information
//            if (objects.at(i).direction == -1) {
//                if (centroid.x - objects.at(i).centroid.x > -5) {
//                    objects.at(i).direction = 1;
//                } else {
//                    objects.at(i).direction = 0;
//                }
//            }

//            objects.at(i).lastFrameSeen = frameNum;
//            objects.at(i).br = br;
//            objects.at(i).centroid = centroid;
//            return i;
//        }
//    }

//    // Object has not been counted in a previous frame
//    return -1;
//}

//// Removes objects from the vector when they have not been seen for a while
//void removeOldObjects(int frameNum) {
//    for (vector<vehicle>::iterator it=objects.begin();it!=objects.end();) {
//       if(abs(frameNum-it->lastFrameSeen) > 10) {
//          it = objects.erase(it);
//       } else
//          ++it;
//    }
//}

//// Draws the detected car on the frame
//void drawCarsOnFrame(Mat firstFrame, Mat videoFrame, Rect location) {
//    Mat car = videoFrame(location);
//    car.copyTo(firstFrame(location));
//}
