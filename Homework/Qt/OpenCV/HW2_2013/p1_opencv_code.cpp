//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include <iostream>

//using namespace cv;
//using namespace std;

//void process1A(Mat src);
//void process1B(Mat src);

//int main()
//{
//  // Read in the input image and create separate images for the handle and disk
//  Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p1\\1a.png", IMREAD_GRAYSCALE);
//  Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p1\\1b.png", IMREAD_GRAYSCALE);

//  // Process the images
//  process1A(src1);
//  process1B(src2);

//  waitKey(0);
//  return 0;
//}

//void process1A(Mat src) {
//    // Apply close operation to isolate the bar
//    Mat handle;
//    Mat element = getStructuringElement( MORPH_RECT,
//                         Size( 2*0 + 1, 2*13+1 ),
//                         Point( 0, 13 ) );
//    morphologyEx( src, handle, MORPH_CLOSE, element );

//    // Create the handle matrix
//    bitwise_not(handle, handle);
//    bitwise_not(src, src);
//    src = src - handle;
//    bitwise_not(handle, handle);
//    bitwise_not(src, src);

//    // Isolate the top and bottom elements
//    Rect roi = Rect(0, 0, src.cols, src.rows/2);
//    Mat top = Mat(src.rows, src.cols, 0, 255.0);
//    Mat mask = src(roi);
//    mask.copyTo(top(roi));

//    // Use bitwise operations to isolate the bottom object
//    bitwise_not(top, top);
//    bitwise_not(src, src);
//    Mat bottom = src - top;
//    bitwise_not(top, top);
//    bitwise_not(bottom, bottom);
//    bitwise_not(src, src);

//    imshow("handle", handle);
//    imshow("top", top);
//    imshow("bottom", bottom);
//}

//void process1B(Mat src) {
//    // Close width of 40 for horizontal lines
//    Mat horiz;
//    Mat element = getStructuringElement( MORPH_RECT,
//                         Size( 2*40 + 1, 2*1+1 ),
//                         Point( 40, 1 ) );
//    morphologyEx( src, horiz, MORPH_CLOSE, element );

//    // Close height of 35 for vertical lines
//    Mat vert;
//    element = getStructuringElement( MORPH_RECT,
//                         Size( 2*1 + 1, 2*35+1 ),
//                         Point( 1, 35 ) );
//    morphologyEx( src, vert, MORPH_CLOSE, element );

//    // Bitwise and the components to get the entire box
//    Mat box;
//    bitwise_and(horiz, vert, box);

//    // Remove the box from the original source
//    bitwise_not(src, src);
//    bitwise_not(box, box);
//    src = src - box;
//    bitwise_not(src, src);
//    bitwise_not(box, box);

//    // Close for height of 12 and width of 3 to isolate vertical right corner
//    element = getStructuringElement( MORPH_RECT,
//                         Size( 2*3 + 1, 2*12+1 ),
//                         Point( 3, 12 ) );
//    morphologyEx( src, vert, MORPH_CLOSE, element );

//    // Threshold to darken vertical corner
//    threshold(vert, vert, 230, 255, THRESH_BINARY);

//    // Close for height of 2 width of 19 to isolate horizontal right corner
//    element = getStructuringElement( MORPH_RECT,
//                         Size( 2*19 + 1, 2*2+1 ),
//                         Point( 19, 2 ) );
//    morphologyEx( src, horiz, MORPH_CLOSE, element );

//    // Threshold 150 to remove remaining bird parts from vertical component
//    threshold(horiz, horiz, 120, 255, THRESH_BINARY);

//    // Combine the left and right parts of the top corner to create the corner
//    Mat corner;
//    bitwise_and(horiz, vert, corner);

//    // Remove the outer boundary and right corner from the original src to isolate the bird (need to apply close with height of 2 to remove stray lines from box)
//    Mat bird;
//    bitwise_not(src, src);
//    bitwise_not(corner, corner);
//    bird = src - corner;
//    bitwise_not(bird, bird);
//    bitwise_not(src, src);
//    bitwise_not(corner, corner);

//    // Close operation to remove leftovers from box
//    element = getStructuringElement( MORPH_RECT,
//                         Size( 2*0 + 1, 2*1+1 ),
//                         Point( 0, 1 ) );
//    morphologyEx( bird, bird, MORPH_CLOSE, element );

//    // Change the colors of the images and bitwise_and them back into the original images
//    imshow("box", box);
//    imshow("corner", corner);
//    imshow("bird", bird);
//}
