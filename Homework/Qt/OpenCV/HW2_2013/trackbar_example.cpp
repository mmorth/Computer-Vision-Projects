////#include <iostream>

////#include <opencv2/opencv.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <opencv2/imgcodecs/imgcodecs.hpp>

////using namespace std;
////using namespace cv;

////int main()
////{
////  // Read in the input image and create separate images for the handle and disk
////  Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p1\\1a.png", IMREAD_GRAYSCALE);
////  Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p1\\1b.png", IMREAD_GRAYSCALE);

////  imshow("src1", src1);
////  imshow("src2", src2);

////  waitKey(0);
////  return 0;
////}


//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include <iostream>
//using namespace cv;
//using namespace std;
//Mat src, erosion_dst, dilation_dst;
//int erosion_elem = 0;
//int erosion_height = 0;
//int erosion_width = 0;
//int dilation_elem = 0;
//int dilation_height = 0;
//int dilation_width = 0;
//int const max_elem = 2;
//int const max_kernel_size = 100;
//void Erosion( int, void* );
//void Dilation( int, void* );

//void process1A(Mat src);
//void process1B(Mat src);

//int main( int argc, char** argv )
//{
//  // Read in the input image and create separate images for the handle and disk
//  src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p1\\1a.png", IMREAD_GRAYSCALE);
////  src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p1\\1b.png", IMREAD_GRAYSCALE);

//  imshow("src", src);

//  // Process the images
//  process1A(src);
////  process1B(src);

//  // Use morphology to separate the three objects
//  // Then use flood fill mask or other segmentation procedure to isolate each region in the image

//  namedWindow( "Erosion Demo", WINDOW_AUTOSIZE );
//  namedWindow( "Dilation Demo", WINDOW_AUTOSIZE );
//  moveWindow( "Dilation Demo", src.cols, 0 );
//  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
//          &erosion_elem, max_elem,
//          Erosion );
//  createTrackbar( "Erosion height:\n 2n +1", "Erosion Demo",
//          &erosion_height, max_kernel_size,
//          Erosion );
//  createTrackbar( "Erosion width:\n 2n +1", "Erosion Demo",
//          &erosion_width, max_kernel_size,
//          Erosion );
//  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
//          &dilation_elem, max_elem,
//          Dilation );
//  createTrackbar( "Erosion height:\n 2n +1", "Dilation Demo",
//          &dilation_height, max_kernel_size,
//          Dilation );
//  createTrackbar( "Erosion width:\n 2n +1", "Dilation Demo",
//          &dilation_width, max_kernel_size,
//          Dilation );
//  Erosion( 0, 0 );
//  Dilation( 0, 0 );
//  waitKey(0);
//  return 0;
//}

//void process1A(Mat src) {
////    // Remove the vertical bar
////    Mat mask;
////    int size = 9;
////    Mat element = getStructuringElement( MORPH_RECT,
////                         Size( 2*size + 1, 2*size+1 ),
////                         Point( size, size ) );
////    morphologyEx( src, mask, MORPH_OPEN, element );

////    // Create the mask for the upper and lower objects
////    size = 4;
////    element = getStructuringElement( MORPH_RECT,
////                         Size( 2*size + 1, 2*size+1 ),
////                         Point( size, size ) );
////    morphologyEx( mask, mask, MORPH_CLOSE, element );

//    // Apply close operation to isolate the bar
//    Mat handle;
//    Mat element = getStructuringElement( MORPH_RECT,
//                         Size( 2*0 + 1, 2*13+1 ),
//                         Point( 0, 13 ) );
//    morphologyEx( src, handle, MORPH_CLOSE, element );

//    bitwise_not(handle, handle);
//    bitwise_not(src, src);
//    src = src - handle;
//    bitwise_not(handle, handle);
//    bitwise_not(src, src);

////    // Perform bitwise operations to remove the handle from the original image
////    Mat top;
////    bitwise_not(mask, mask);
////    bitwise_not(src, src);
////    bitwise_and(src, mask, top);
////    bitwise_not(top, top);
////    imshow("top", top);

////    src = top;

//    Rect roi = Rect(0, 0, src.cols, src.rows/2);
//    Mat top = Mat(src.rows, src.cols, 0, 255.0);
//    Mat mask = src(roi);
//    mask.copyTo(top(roi));

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

//    imshow("horiz", horiz);
//    imshow("vert", vert);

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

//void Erosion( int, void* )
//{
//  int erosion_type = 0;
//  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
//  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
//  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
//  Mat element = getStructuringElement( erosion_type,
//                       Size( 2*erosion_width + 1, 2*erosion_height+1 ),
//                       Point( erosion_width, erosion_height ) );
////  erode( src, erosion_dst, element );
//  morphologyEx( src, erosion_dst, MORPH_OPEN, element );
//  imshow( "Erosion Demo", erosion_dst );
//}
//void Dilation( int, void* )
//{
//  int dilation_type = 0;
//  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
//  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
//  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
//  Mat element = getStructuringElement( dilation_type,
//                       Size( 2*dilation_width + 1, 2*dilation_height+1 ),
//                       Point( dilation_width, dilation_height ) );
////  dilate( src, dilation_dst, element );
//  morphologyEx( src, dilation_dst, MORPH_CLOSE, element );
//  imshow( "Dilation Demo", dilation_dst );
//}
