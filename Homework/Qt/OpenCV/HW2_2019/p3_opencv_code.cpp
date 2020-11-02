//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//Mat src;
//Mat dst;
//RNG rng(12345);

//int main()
//{
//    char keyPress;
//    cout << "p3_opencv_code.cpp\n";

//    // Read image and make a copy to have the original image
//    src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_3\\p3_search.png", IMREAD_GRAYSCALE);
//    dst = src.clone();

//    // Invert the image and provide thresholding to remove various pixel noise within boxes
//    bitwise_not(src, src);
//    threshold(src, src, 15, 100, THRESH_BINARY);

//    // Determine contours of image
//    vector<vector<Point> > contours;
//    vector<Vec4i> hierarchy;
//    findContours(src, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

//    // Fill in the the boxes with random color
//    Mat drawing = Mat(src.size(), CV_8UC3, Scalar(0, 0, 0));
//    for( size_t i = 0; i< contours.size(); i++ )
//    {
//        // Fill in the contour boxes with random color
//        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
//        drawContours( drawing, contours, (int)i, color, FILLED, 8, hierarchy, 0 );
//        // Remove color from the contour themselves (will be colored using original grid color
//        Scalar gridColor = Scalar( 0, 0, 0 );
//        drawContours( drawing, contours, (int)i, gridColor, 1, 8, hierarchy, 0 );
//    }

//    // Convert the original image to BGR format
//    cvtColor(dst, dst, COLOR_GRAY2BGR);

//    // Filter out boxed color at contour intersections
//    vector<int> box_filter = {223, 7, 58};
//    Mat mask;
//    inRange(drawing, box_filter, box_filter, mask);
//    cvtColor(mask, mask, COLOR_GRAY2BGR);
//    bitwise_not(mask, mask);
//    bitwise_and(drawing, mask, drawing);

//    // Draw the original color grid lines on the image
//    bitwise_not(dst, dst);
//    drawing = drawing + dst;
//    bitwise_not(drawing, drawing);

//    // Display result
//    imshow("Contours", drawing);

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
