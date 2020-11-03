//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void processLetter(Mat src, Mat hl, Mat temp, Scalar color);

//int main()
//{
//    char keyPress;
//    cout << "p5_opencv_code.cpp\n";

//    // Read image and template and make a copy to have the original image
//    Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_5\\p5_search.png", IMREAD_GRAYSCALE);
//    Mat dst = src.clone();
//    Mat hl = src.clone();

//    // Read in the vowel templates
//    Mat aTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\A.png", IMREAD_GRAYSCALE);
//    Mat eTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\E.png", IMREAD_GRAYSCALE);
//    Mat iTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\I.png", IMREAD_GRAYSCALE);
//    Mat oTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\O.png", IMREAD_GRAYSCALE);
//    Mat uTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\U.png", IMREAD_GRAYSCALE);

//    // Store templates and colors in an array for easy iteration
//    Mat letterTemplates[] = {aTemp, eTemp, iTemp, oTemp, uTemp};
//    Scalar colors[] = {Scalar(0,0,255), Scalar(0,128,255), Scalar(0,255,255), Scalar(0,255,128), Scalar(255, 128, 0), Scalar(128,128,128)};

//    // Change hl (highlighted) from grayscale to BGR to enable coloring of letters
//    cvtColor(hl, hl, COLOR_GRAY2BGR);

//    // Loop through all vowel templates
//    for(int i = 0; i < 6; i++) {
//        // Call the function that will determine locations of each vowel and color them (apply these to the same image)
//        processLetter(src, hl, letterTemplates[i], colors[i]);
//    }

//    // Convert dst to BGR to color A matches
//    cvtColor(dst, dst, COLOR_GRAY2BGR);
//    addWeighted(hl, 0.5, dst, 0.5, 0, dst);

//    // Display final image
//    imshow("Result", dst);

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

//// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
//// This code is based on the solution at this link
//void processLetter(Mat src, Mat hl, Mat temp, Scalar color) {
//    // Match the A template on the grid
//    Mat1f result;
//    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

//    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
//    double thresh = 0.95;
//    threshold(result, result, thresh, 1., THRESH_BINARY);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    result.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result (these will be all the points where A's are located)
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Process each matching A
//    for (uint i=0; i<contours.size(); ++i)
//    {
//        // Mask out all other matching A's except the one that corresponds to the current contour
//        Mat mask(result.rows, result.cols, uchar(0));
//        drawContours(mask, contours, i, Scalar(255), FILLED);

//        // Find the maximum matching location
//        Point max_point;
//        double max_val;
//        minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);

//        // Highlight squares with A's with red
//        rectangle(hl, Rect(max_point.x, max_point.y, temp.cols, temp.rows), color, FILLED);
//    }
//}
