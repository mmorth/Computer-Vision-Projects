#include <iostream>

#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main()
{
    char keyPress;
    cout << "Welcome to Qt\n";
    // Read image
    Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_2\\p2_board_1.jpg", IMREAD_GRAYSCALE);
    Mat border = src.clone();

    bitwise_not(src, src);
    threshold(src, src, 50, 255, THRESH_BINARY);

    threshold(border, border, 248, 100, THRESH_BINARY);

    int elementValue = 5;
    Mat element = getStructuringElement( MORPH_RECT, Size( 2*elementValue + 1, 2*elementValue+1 ), Point( elementValue, elementValue ) );
    morphologyEx( border, border, MORPH_CLOSE, element );

    src = src + border;

    Canny(src, src, 50, 50);

    // Pull the vertical and horizontal lines from the image
    Mat se = getStructuringElement( MORPH_RECT, Size( 3, 3 ), Point( 1, 1 ));
    morphologyEx( src, src, MORPH_CLOSE, element );

    Mat vert;
    Mat horiz;
    int e = 522;
    se = getStructuringElement( MORPH_RECT, Size( 2*e + 1, 1 ), Point( e, 0 ) );
    morphologyEx( src, horiz, MORPH_OPEN, se );

    imshow("horiz", horiz);

    se = getStructuringElement( MORPH_RECT, Size( 1, 2*e + 1 ), Point( 0, e ) );
    morphologyEx( src, vert, MORPH_OPEN, se );

    imshow("vert", vert);

    Mat grid = horiz + vert;

    imshow("grid", grid);

    imshow("Image", src);

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
