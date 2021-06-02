#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

using namespace std;
using namespace cv;

#define SSTR( x ) static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()

// Get the names of the output layers
auto getOutputsNames(const Net& net)
{
    static vector<String> names;
    if (names.empty())
    {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        vector<int> outLayers = net.getUnconnectedOutLayers();

        //get the names of all the layers in the network
        vector<String> layersNames = net.getLayerNames();

        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
        names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}

// Draw the predicted bounding box
void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame)
{
    //Draw a rectangle displaying the bounding box
    rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);

    //Get the label for the class name and its confidence
    string label = format("%.2f", conf);
    if (!classes.empty())
    {
        CV_Assert(classId < (int)classes.size());
        label = classes[classId] + ":" + label;
    }

    //Display the label at the top of the bounding box
    int baseLine;
    Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    top = max(top, labelSize.height);
    rectangle(frame, Point(left, top - round(1.5*labelSize.height)), Point(left + round(1.5*labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
    putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,0),1);
}

// Remove the bounding boxes with low confidence using non-maxima suppression
void postprocess(Mat& frame, const vector<Mat>& outs)
{
    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;

    for (size_t i = 0; i < outs.size(); ++i)
    {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            Point classIdPoint;
            double confidence;
            // Get the value and location of the maximum score
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold)
            {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(Rect(left, top, width, height));
            }
        }
    }

    // Perform non maximum suppression to eliminate redundant overlapping boxes with
    // lower confidences
    vector<int> indices;
    NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    for (size_t i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        Rect box = boxes[idx];
        drawPred(classIds[idx], confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height, frame);
    }
}

// Detects the location of the ball and returns location
Rect findBallLocation(Mat frame)
{
    // Use detection to find the location of the ball
    // Initialize the parameters
    float objectnessThreshold = 0.5; // Objectness threshold
    float confThreshold = 0.5; // Confidence threshold
    float nmsThreshold = 0.4;  // Non-maximum suppression threshold
    int inpWidth = 416;  // Width of network's input image
    int inpHeight = 416; // Height of network's input image
    vector<string> classes;

    // Load names of classes
    string classesFile = "coco.names";
    ifstream ifs(classesFile.c_str());
    string line;
    while (getline(ifs, line)) classes.push_back(line);
    // Give the configuration and weight files for the model
    String modelConfiguration = "yolov3.cfg";
    String modelWeights = "yolov3.weights";

    // Load the network
    Net net = readNetFromDarknet(modelConfiguration, modelWeights);

    // Create a 4D blob from a frame.
    Mat blob;
    blobFromImage(frame, blob, 1/255.0, Size(inpWidth, inpHeight), Scalar(0,0,0), true, false);
    //Sets the input to the network
    net.setInput(blob);
    // Runs the forward pass to get output of the output layers
    vector<Mat> outs;
    net.forward(outs, getOutputsNames(net));

    // Remove the bounding boxes with low confidence
    postprocess(frame, outs);
    // Put efficiency information. The function getPerfProfile returns the overall time for inference(t) and the timings for each of the layers(in layersTimes)
    vector<double> layersTimes;
    double freq = getTickFrequency() / 1000;
    double t = net.getPerfProfile(layersTimes) / freq;
    string label = format("Inference time for a frame : %.2f ms", t);
    putText(frame, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));

    // Find bounding rectangle of ball and draw in blue


    // Return the bounding rectangle of the ball (if not found, let user know)

}

// Tracks the ball
bool trackBall(Ptr<Tracker> tracker, Mat frame, Rect2d location, bool foundLastFrame)
{
    // Use an OpenCV tracker to track the soccer ball location
    // Update the tracking result
    double timer = (double)getTickCount();
    bool success = tracker->update(frame, location);

    // Calculate Frames per second (FPS)
    float fps = getTickFrequency() / ((double)getTickCount() - timer);

    if (success)
    {
        // Draw bounding ball location in green
        rectangle(frame, location, Scalar( 0, 255, 0 ), 2, 1 );
    }
    else
    {
        // Tracking failure detected.
        putText(frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
    }

    // Display tracker type on frame
    putText(frame, "Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);

    // Display FPS on frame
    putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);

    // Return whether this frame's tracking was successful
    return success;
}

int main()
{
    // Train the YOLO detector


    // Create a KCF tracker
    Ptr<Tracker> tracker = TrackerKCF::create();

    // Read video
    VideoCapture cap("soccer-ball.mp4");

    // Exit if video is not opened
    if(!cap.isOpened())
    {
        cout << "Could not read video file" << endl;
    }

    // Read first frame
    Mat frame;
    bool ok = cap.read(frame);

    // Initialize tracker
    Rect2d ballLocation = findBallLocation(frame);
    tracker->init(frame, ballLocation);

    // Display bounding box.
    rectangle(frame, ballLocation, Scalar(255, 0, 0), 2, 1 );

    // Read until video is completed
    Rect location;
    bool foundLastFrame = false;
    while(cap.isOpened()){

        Mat frame;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
          break;

        if (!foundLastFrame)
        {
            location = findBallLocation(frame);
        }

        foundLastFrame = trackBall(tracker, frame, location, foundLastFrame);

        // Display the found ball location
        imshow("Window", frame);

        // Wait for 25 ms before moving on to the next frame
        // This will slow down the video
        waitKey(25);
    }

    return 0;
}
