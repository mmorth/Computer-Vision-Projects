#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

Mat src;
Mat horiz;
Mat vert;
Mat grid;
Mat letters;
Mat dst;

int erosion_elem = 0;
int erosion_width = 0;
int erosion_height = 0;
int dilation_width = 0;
int dilation_height = 0;
int dilation_elem = 0;
int max_kernel_size = 100;


int main()
{
    char keyPress;
    cout << "p1_opencv_code.cpp\n";
    // Read image
    src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_1\\p1_search.png", IMREAD_GRAYSCALE);
    bitwise_not(src, src);

    // Extract the vertical lines of the grid
    Mat element1 = getStructuringElement( MORPH_RECT,
                         Size( 2*0 + 1, 2*17+1 ),
                         Point( 0, 17 ) );
    morphologyEx( src, vert, MORPH_OPEN, element1 );

    // Extract the horizontal lines of the grid
    Mat element2 = getStructuringElement( MORPH_RECT,
                         Size( 2*10 + 1, 2*0+1 ),
                         Point( 10, 0 ) );
    morphologyEx( src, horiz, MORPH_OPEN, element2 );

    // Combine the horizontal and vertical lines into one image
    grid = horiz+vert;

    // Determine the boundary of the image
    bool searchingRight = false;
    bool foundResult = false;
    Point topLeft = Point(0, 0);
    Point topRight = Point(0, 0);
    Point bottomRight = Point(0, 0);
    Point bottomLeft = Point(0, 0);
    for (int i = 0; i < grid.rows; i++) {
        for (int j = 0; j < grid.cols; j++) {
            if ((int) grid.at<uchar>(i, j) > 0 && topLeft == Point(0,0)) {
                topLeft = Point(i, j);
                searchingRight = true;
            }
            else if ((int) grid.at<uchar>(i, j) == 0 && searchingRight == true) {
                topRight = Point(i, j-1);
                bottomLeft = Point(topLeft.x+topRight.y-topLeft.y, topLeft.y);
                bottomRight = Point(bottomLeft.x, topRight.y);
                foundResult = true;
                break;
            }
        }
        if (foundResult) {
            break;
        }
    }

    // Using the grid dimensions, display only the grid pixels and pixels within the grid
    bitwise_not(src, src);
    dst = src;
    int minRow = topLeft.x;
    int maxRow = bottomLeft.x;
    int minCol = topLeft.y;
    int maxCol = topRight.y;
    for (int i = 0; i < grid.rows; i++) {
        for (int j = 0; j < grid.cols; j++) {
            if (!(i >= minRow && i <= maxRow && j >= minCol && j <= maxCol)) {
                dst.at<uchar>(i, j) = 255;
            }
        }
    }

    imshow( "Image", dst );

    while(1)
    {
        keyPress = waitKey();
        // Press q key to close window
        if (keyPress == 'q')
        {
            destroyAllWindows();
            break;
        }
    }
    return 0;
}
