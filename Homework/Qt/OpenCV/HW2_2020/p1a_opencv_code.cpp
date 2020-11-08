//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void displayBoardGridOverlay(Mat src, Mat dst, string title);

//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image
//    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_1\\p1_board.jpg", IMREAD_GRAYSCALE);
//    Mat dst1 = src1.clone();

//    // Create constant border for grid detectioon
//    copyMakeBorder(src1, src1, 1, 1, 1, 1, BORDER_CONSTANT, Scalar(255));

//    // Run function to display location overlay
//    displayBoardGridOverlay(src1, dst1, "Results 1");

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

//void displayBoardGridOverlay(Mat src, Mat dst, string title) {
//    cvtColor(src, dst, COLOR_GRAY2BGR);
//    Mat border = src.clone();

//    // Invert colors and apply threshold to isolate border and grids
//    bitwise_not(src, src);
//    threshold(src, src, 50, 255, THRESH_BINARY);

//    threshold(border, border, 248, 100, THRESH_BINARY);

//    // Apply morphology to clean up border
//    int elementValue = 5;
//    Mat element = getStructuringElement( MORPH_RECT, Size( 2*elementValue + 1, 2*elementValue+1 ), Point( elementValue, elementValue ) );
//    morphologyEx( border, border, MORPH_CLOSE, element );

//    src = src + border;

//    // Apply Canny edge detection to display clear lines
//    Canny(src, src, 100, 100);

//    Mat se = getStructuringElement( MORPH_RECT, Size( 3, 3 ), Point( 1, 1 ));
//    dilate(src, src, se);

//    // Connect disconnected lines from prior morph operation
//    se = getStructuringElement( MORPH_RECT, Size( 3, 3 ), Point( 1, 1 ));
//    morphologyEx( src, src, MORPH_CLOSE, element );

//    // Pull the vertical and horizontal lines from the image
//    Mat vert;
//    Mat horiz;
//    int e = 100;
//    se = getStructuringElement( MORPH_RECT, Size( 2*e + 1, 1 ), Point( e, 0 ) );
//    morphologyEx( src, horiz, MORPH_OPEN, se );

//    se = getStructuringElement( MORPH_RECT, Size( 1, 2*e + 1 ), Point( 0, e ) );
//    morphologyEx( src, vert, MORPH_OPEN, se );

//    // Store the grid for processing
//    Mat grid = horiz + vert;

//    Mat resb;
//    grid.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result (these will be all the points where A's are located)
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Contour sorter source: https://answers.opencv.org/question/31515/sorting-contours-from-left-to-right-and-top-to-bottom/
//    // The countour sorter from this source was modified for application to this problem
//    struct contour_sorter // 'less' for contours
//    {
//        bool operator ()( const vector<Point>& a, const vector<Point> & b )
//        {
//            Rect ra(boundingRect(a));
//            Rect rb(boundingRect(b));
//            // Sort contours from left to right, up to down on the grid
//            if (abs(ra.y-rb.y) < 5) {
//                return ra.x < rb.x;
//            } else {
//                return ( (ra.x + 1000*ra.y) < (rb.x + 1000*rb.y) );
//            }
//        }
//    };

//    // apply it to the contours:
//    std::sort(contours.begin(), contours.end(), contour_sorter());

//    // Display the square labels on the grid
//    char col = 'A';
//    int row = 8;

//    // Display text
//    int lastX = -64;
//    for (uint i=0; i<contours.size(); ++i)
//    {
//        // Display text for each bounding box in grid
//        if (contourArea(contours[i]) > 2500) {
//            Rect bound = boundingRect(contours[i]);
//            if (abs(bound.x - lastX) > 50) {
//                std::string s(1, col);
//                string text = s + std::to_string(row);
//                putText(dst, text, Point(bound.x+10, bound.y+35), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255), 3);
//                col++;

//                if (col == 'I') {
//                    col = 'A';
//                    row--;
//                }
//                lastX = bound.x;
//            }
//        }
//    }

//    // Display result
//    imshow(title, dst);
//}
