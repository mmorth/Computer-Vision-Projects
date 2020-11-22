//#include <opencv2/opencv.hpp>
//#include <opencv2/tracking.hpp>
//#include <opencv2/core/ocl.hpp>

//using namespace cv;
//using namespace std;

//Mat createFilteredFrame(Mat frame);
//void trackMario(VideoCapture video, Rect2d bbox, bool power, string fileName);

//// Convert to string
//#define SSTR( x ) static_cast< std::ostringstream & >( \
//( std::ostringstream() << std::dec << x ) ).str()

//int main()
//{
//    VideoCapture video1("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_1.mp4");
//    Rect2d bbox1(839, 764, 55, 70);
//    trackMario(video1, bbox1, false, "p2a_output1.avi");

//    VideoCapture video2("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_2.mp4");
//    Rect2d bbox2(36, 764, 55, 70);
//    trackMario(video2, bbox2, false, "p2a_output2.avi");

//    VideoCapture video3("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\part_2a\\p2a_mario_3.mp4");
//    Rect2d bbox3(130, 764, 55, 70);
//    trackMario(video3, bbox3, true, "p2a_output3.avi");
//}

//// Source: https://www.learnopencv.com/object-tracking-using-opencv-cpp-python/
//// The follow function's code was modified from the above source
//// Tracks mario in the game
//void trackMario(VideoCapture video, Rect2d bbox, bool power, string fileName) {
//    // Create a CSRT tracker used to track the position of mario
//    Ptr<Tracker> tracker = TrackerCSRT::create();

//    // Exit if video is not opened
//    if(!video.isOpened())
//    {
//        cout << "Could not read video file" << endl;
//        return;
//    }

//    // Default resolution of the frame is obtained.The default resolution is system dependent.
//    int frame_width = video.get(CAP_PROP_FRAME_WIDTH);
//    int frame_height = video.get(CAP_PROP_FRAME_HEIGHT);

//    // Create the VideoWriter that will write the output to a mp4 file
//    VideoWriter output(fileName,VideoWriter::fourcc('M','J','P','G'),60, Size(frame_width,frame_height));

//    // Read first frame
//    Mat frame;
//    bool ok = video.read(frame);
//    Mat fc = createFilteredFrame(frame);

//    // Uncomment the line below to select a different bounding box
////     bbox = selectROI(frame, false);
//    // Display bounding box.
//    rectangle(frame, bbox, Scalar( 255, 255, 255 ), 2, 1 );

//    imshow("Tracking", frame);
//    tracker->init(fc, bbox);

//    int frameNum = 0;
//    while(video.read(frame))
//    {
//        fc = createFilteredFrame(frame);

//        // Start timer
//        double timer = (double)getTickCount();

//        // Update the tracking result
//        bool ok = tracker->update(fc, bbox);

//        // Calculate Frames per second (FPS)
//        float fps = getTickFrequency() / ((double)getTickCount() - timer);

//        if (ok)
//        {
//            // Tracking success : Draw the tracked object
//            rectangle(frame, bbox, Scalar( 255, 255, 255 ), 2, 1 );
//        }
//        else
//        {
//            // Reinitialize the player's location after their tracking is lost
//            if (power) {
//                frameNum++;
//                if (frameNum > 65) {
//                    tracker->clear();
//                    Rect2d bbox(840, 769, 52, 65);
//                    tracker = TrackerCSRT::create();
//                    tracker->init(fc, bbox);
//                    rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
//                    frameNum = 0;
//                }
//            }
//        }

//        // Display frame.
//        imshow("Tracking", frame);
//        output.write(frame);

//        // Exit if ESC pressed.
//        int k = waitKey(1);
//        if(k == 27)
//        {
//            break;
//        }

//    }

//    // Close the VideoCapture and VideoWriter
//    video.release();
//    output.release();
//}

//// Returns a frame with some of the background filtered out
//Mat createFilteredFrame(Mat frame) {
//    Mat mask;
//    Mat fc = frame.clone();
//    // Mask the blue background
//    inRange(fc, Scalar(245,134,86), Scalar(245,134,86), mask);
//    fc.setTo(Scalar(0, 0, 0), mask);
//    // Mask the green hills
//    inRange(fc, Scalar(7,185,13), Scalar(7,185,13), mask);
//    fc.setTo(Scalar(0, 0, 0), mask);
//    // Mask the green bushes
//    inRange(fc, Scalar(23,218,118), Scalar(29,224,125), mask);
//    fc.setTo(Scalar(0, 0, 0), mask);
//    return fc;
//}
