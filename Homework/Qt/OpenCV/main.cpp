//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//Mat src;
//Mat horiz;
//Mat vert;
//Mat grid;
//Mat letters;
//Mat dst;

//int erosion_elem = 0;
//int erosion_width = 0;
//int erosion_height = 0;
//int dilation_width = 0;
//int dilation_height = 0;
//int dilation_elem = 0;
//int const max_elem = 2;
//int max_kernel_size = 100;

//void Dilation( int, void* )
//{
//  int dilation_type = 0;
//  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
//  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
//  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
//  Mat element = getStructuringElement( dilation_type,
//                       Size( 2*dilation_width + 1, 2*dilation_height+1 ),
//                       Point( dilation_width, dilation_height ) );
//  dilate( src, dst, element );
////  morphologyEx( src, dst, MORPH_CLOSE, element );
////  adaptiveThreshold(src, src, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 0);
//  imshow( "Image", dst );
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
//  erode( src, dst, element );
////  printf("SizeWidth = %d\n", 2*erosion_width + 1);
////  printf("SizeHeight = %d\n", 2*erosion_height+1);
////  printf("DilationWidth = %d\n", erosion_width);
////  printf("DilationHeight = %d\n\n", erosion_height);
////  morphologyEx( src, dst, MORPH_OPEN, element );
//  imshow( "Image", dst );
//}

//int main()
//{
//    char keyPress;
//    cout << "Welcome to Qt\n";
//    // Read image
////    src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\H.png", IMREAD_GRAYSCALE);
////    medianBlur(src, dst, 3);
////    fastNlMeansDenoising(src, dst, 50);

////    imshow("Noisy", dst);

////    bitwise_not(src, src);

////    namedWindow("Homework", WINDOW_AUTOSIZE); // Create Window

////    createTrackbar( "Erosion Element", "Homework",
////              &erosion_elem, max_elem,
////              Erosion );
////    createTrackbar( "Erosion Width", "Homework",
////              &erosion_width, max_kernel_size,
////              Erosion );
////    createTrackbar( "Erosion Height", "Homework",
////              &erosion_height, max_kernel_size,
////              Erosion );

////    createTrackbar( "Dilation Element", "Homework",
////            &dilation_elem, max_elem,
////            Dilation );
////    createTrackbar( "Dilation Width", "Homework",
////            &dilation_width, max_kernel_size,
////            Dilation );
////    createTrackbar( "Dilation Height", "Homework",
////            &dilation_height, max_kernel_size,
////            Dilation );

////    // Extract the vertical lines of the grid
////    Mat element1 = getStructuringElement( MORPH_RECT,
////                         Size( 2*0 + 1, 2*17+1 ),
////                         Point( 0, 17 ) );
////    morphologyEx( src, vert, MORPH_OPEN, element1 );

//////    imshow("vert", vert);

////    // Extract the horizontal lines of the grid
////    Mat element2 = getStructuringElement( MORPH_RECT,
////                         Size( 2*10 + 1, 2*0+1 ),
////                         Point( 10, 0 ) );
////    morphologyEx( src, horiz, MORPH_OPEN, element2 );

//////    imshow("horiz", horiz);

////    // Combine the horizontal and vertical lines into one image
////    grid = horiz+vert;
//////    imshow("grid", src);

////    // Determine the boundary of the image
////    bool searchingRight = false;
////    bool foundResult = false;
////    Point topLeft = Point(0, 0);
////    Point topRight = Point(0, 0);
////    Point bottomRight = Point(0, 0);
////    Point bottomLeft = Point(0, 0);
////    for (int i = 0; i < grid.rows; i++) {
////        for (int j = 0; j < grid.cols; j++) {
////            if ((int) grid.at<uchar>(i, j) > 0 && topLeft == Point(0,0)) {
////                topLeft = Point(i, j);
////                searchingRight = true;
////            }
////            else if ((int) grid.at<uchar>(i, j) == 0 && searchingRight == true) {
////                topRight = Point(i, j-1);
////                bottomLeft = Point(topLeft.x+topRight.y-topLeft.y, topLeft.y);
////                bottomRight = Point(bottomLeft.x, topRight.y);
////                foundResult = true;
////                break;
////            }
////        }
////        if (foundResult) {
////            break;
////        }
////    }

////    // Print the boundary positions
////    printf("topLeft: row = %d, col = %d\n", topLeft.x, topLeft.y);
////    printf("topRight: row = %d, col = %d\n", topRight.x, topRight.y);
////    printf("bottomLeft: row = %d, col = %d\n", bottomLeft.x, bottomLeft.y);
////    printf("bottomRight: row = %d, col = %d\n", bottomRight.x, bottomLeft.y);

////    // Using the grid dimensions, display the outer pixels of the grid
////    bitwise_not(src, src);
////    dst = src;
////    int minRow = topLeft.x;
////    int maxRow = bottomLeft.x;
////    int minCol = topLeft.y;
////    int maxCol = topRight.y;
////    for (int i = 0; i < grid.rows; i++) {
////        for (int j = 0; j < grid.cols; j++) {
////            if (!(i >= minRow && i <= maxRow && j >= minCol && j <= maxCol)) {
////                dst.at<uchar>(i, j) = 255;
////            }
////        }
////    }

////    imshow( "Image", dst );

////    Erosion( 0, 0 );
////    Dilation( 0, 0 );

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
