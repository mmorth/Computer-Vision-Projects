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
//int max_kernel_size = 100;


//int main()
//{
//    char keyPress;
//    cout << "p1_opencv_code.cpp\n";
//    // Read image
//    src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_1\\p1_search.png", IMREAD_GRAYSCALE);
//    bitwise_not(src, src);

//    // Extract the vertical lines of the grid
//    Mat element1 = getStructuringElement( MORPH_RECT,
//                         Size( 2*0 + 1, 2*17+1 ),
//                         Point( 0, 17 ) );
//    morphologyEx( src, vert, MORPH_OPEN, element1 );

//    // Extract the horizontal lines of the grid
//    Mat element2 = getStructuringElement( MORPH_RECT,
//                         Size( 2*10 + 1, 2*0+1 ),
//                         Point( 10, 0 ) );
//    morphologyEx( src, horiz, MORPH_OPEN, element2 );

//    // Combine the horizontal and vertical lines into one image
//    grid = horiz+vert;

//    // Determine the boundary of the image
//    bool searchingRight = false;
//    bool foundResult = false;
//    int minRow = 0;
//    int maxRow = 0;
//    int minCol = 0;
//    int maxCol = 0;
//    for (int r = 0; r < grid.rows; r++) {
//        for (int c = 0; c < grid.cols; c++) {
//            if ((int) grid.at<uchar>(r, c) > 0 && minRow == 0) {
//                minRow = r;
//                minCol = c;
//                searchingRight = true;
//            }
//            else if ((int) grid.at<uchar>(r, c) == 0 && searchingRight == true) {
//                maxCol = c;
//                maxRow = minRow + (maxCol - minCol);
//                foundResult = true;
//                break;
//            }
//        }
//        if (foundResult) {
//            break;
//        }
//    }

//    // Using the grid dimensions, display only the grid pixels and pixels within the grid
//    bitwise_not(src, src);
//    dst = src;
//    for (int i = 0; i < grid.rows; i++) {
//        for (int j = 0; j < grid.cols; j++) {
//            if (!(i >= minRow && i <= maxRow && j >= minCol && j <= maxCol)) {
//                dst.at<uchar>(i, j) = 255;
//            }
//        }
//    }

//    // Subtract the horizontal and vertical from the inverted image (should remove those lines)
//    Mat letters;
//    bitwise_not(dst, letters);
//    bitwise_not(dst, dst);
//    letters = letters-vert;
//    letters = letters-horiz;

//    // Subtract the isolated characters image from the original inverted image (should leave only grid)
//    grid = dst - letters;

//    // Invert the colors of these results back to the original black and white composition
//    bitwise_not(letters, letters);
//    bitwise_not(grid, grid);

//    // Show results
//    imshow("Letters", letters);
//    imshow("Grid", grid);

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
