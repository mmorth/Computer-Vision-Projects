#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

struct vehicle {
    Rect br;
    Point centroid;
    int lastFrameSeen;
};

vector<vehicle> objects;

void processVideo(VideoCapture cap, string inputVideoName, string outputVideoName);
void detectVehicles(Mat frame, Mat mask, int frameNum);
bool checkExistingObjects(Rect br, int frameNum);
void removeOldObjects(int frameNum);

int numBuses = 0;
int numCars = 0;
int numPeople = 0;

int main()
{
    cout << "p1a_opencv_code\n";

    // Read input videos
    VideoCapture cap1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip1.avi");
    processVideo(cap1, "clip1.avi", "output1.avi");
//    VideoCapture cap2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip2.avi");
//    processVideo(cap2, "clip2.avi", "output2.avi");
//    VideoCapture cap3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2016\\1_Traffic_Monitoring\\clip3.avi");
//    processVideo(cap3, "clip3.avi", "output3.avi");

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

    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorKNN();
    Mat fgMask;

    // Create a video writer and process the input video frame by frame
    int frameNum = 0;
    printf("Processing video %s...\n", inputVideoName.c_str());
    VideoWriter video(outputVideoName,VideoWriter::fourcc('M','J','P','G'),30, Size(frame_width,frame_height), true);
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

      printf("numObjects = %d\n", objects.size());

      // Detect vechicles from the background subtraction mask
      detectVehicles(frame, fgMask, frameNum);
      imshow("frame", frame);

      imwrite("frame" + std::to_string(frameNum) + ".png", frame);

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

// Detect vehicles in the frame and count total number
void detectVehicles(Mat frame, Mat mask, int frameNum) {
    // Threshold to pull out the main part of the object
    threshold(mask, mask, 200, 255, THRESH_BINARY);
    int width = 1;
    Mat element = getStructuringElement( MORPH_RECT,
                       Size( 2*width + 1, 2*width+1 ),
                       Point( width, width ) );
    dilate( mask, mask, element );
    imshow("mask", mask);

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
        // Check that the object is large enough and within the correct frame for classification
        bool numPeopleIncreased = false;

        bool existingObject;
        if (contourArea(contours[i]) > 1000) {
            existingObject = checkExistingObjects(br, frameNum);
        }

        // Ensure that the detected contour has the possibility of being a vehicle or person
        if (contourArea(contours[i]) > 1000 && br.y > 50 && br.x > 1 && br.x+br.width < frame.cols-1) {
            // Check whether this object is below min distance threshold to classify as other object
            if (!existingObject) {
                // If not, determine which new object is detected and add it to the list and increment the counter
                // Also need to handle situation where the contour for one object is split in 2 for whatever reason
                bool classified = true;
                if (br.height > 60 && br.height < 90 && br.width > 250) {
                    // Object is a bus
                    numBuses++;
                } else if (br.width > 80 && br.height < 60 && br.height > 30) {
                    // Object is a car
                    numCars++;
                } else if (br.height > 30) {
                    // Object is a person
                    numPeople++;
                    numPeopleIncreased = true;
                } else {
                    // No classification found
                    classified = false;
                }

                if (classified) {
                    // Add object to vector
                    vehicle v;
                    v.br = br;
                    v.centroid = Point(br.x+br.width/2, br.y+br.height/2);
                    v.lastFrameSeen = frameNum;
                    objects.push_back(v);
                }
            }

            // Draw the bounding box around the vehicle
            rectangle(frame, br, Scalar(0, 0, 255), 1);
        }

        // Check for smaller person classification
        if (!numPeopleIncreased && br.y > 60 && br.x > 4 && br.x+br.width < frame.cols-4 && contourArea(contours[i]) > 500 && br.width < 50 && br.height > 50) {
            if (!checkExistingObjects(br, frameNum)) {
                numPeople++;
            }

            // Draw the bounding box around the vehicle
            rectangle(frame, br, Scalar(0, 0, 255), 1);
        }
    }

    // Draw the number of each object cumulatively
    string text = "#Buses = " + std::to_string(numBuses);
    putText(frame, text, Point(25, 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 2);
    text = "#Cars = " + std::to_string(numCars);
    putText(frame, text, Point(25, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 2);
    text = "#People = " + std::to_string(numPeople);
    putText(frame, text, Point(25, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 2);

    // Remove old objects from the frame
    removeOldObjects(frameNum);
}

// Checks if the current object has already been identified in a prior frame
bool checkExistingObjects(Rect br, int frameNum) {
    Point centroid = Point(br.x+br.width, br.y+br.height);
    for (int i = 0; i < objects.size(); i++) {
        // Check if distance between objects is less than threshold of 10 pixels
        double distance = cv::norm(centroid-objects.at(i).centroid);
        printf("Distance = %.2lf\n", distance);
        if (distance < 300) {
            // Object has already been detected in prior frame, update information
            objects.at(i).lastFrameSeen = frameNum;
            objects.at(i).br = br;
            return true;
        }
    }

    // Object has not been counted in a previous frame
    return false;
}

// Removes objects from the vector when they have not been seen for a while
void removeOldObjects(int frameNum) {
    for (vector<vehicle>::iterator it=objects.begin();it!=objects.end();) {
       if(abs(frameNum-it->lastFrameSeen) > 10) {
          it = objects.erase(it);
       } else
          ++it;
    }
}


// Apply thresholding to remove the shadows
// Apply morphological dilation to fill in the object to put a bounding box around



// Part 1
// Classify vehicles based on the height of the contour
// You can mask the top part of the frame since vehicles and people there should not be counted (could be reflection or not passing by)
// Need to figure out how to handle counting vehicles only once after moving across the screen
    // Could keep track of each vehicle's position on the screen until they have left the screen in a vector

// Part 2A
// Capture the first frame
// If bus is in frame, draw the actual frame
// If bus is not in frame, draw the first frame
// Will need to consider edge conditions when the bus is leaving the screen not to abruptly stop the video
    // Maybe we can control this by classifying a bus based on its height?

// Part 2B
// Maybe store a list of detected vehicles and their locations frame by frame
// If a car detection is triggered starting on the left side, then we want to show that vehicle across the screen
// Need a way to not show people and buses moving across the screen
    // Maybe we could display the first frame's roi in the detected contour region of the vehicle?
