// Read in the letter templates
    // Store in a Mat array
// Loop through all letter templates
    // Call the function that will determine locations of each vowel
        // Instead of drawing a bounding rectangle, draw the different font letter instead
// Display final image

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

RNG rng(12345);

void processLetter(Mat src, Mat hl, Mat temp, char letter);
Mat isolateGrid(Mat src, Mat dst);

int main()
{
    char keyPress;
    cout << "p7_opencv_code.cpp\n";

    // Read image and template and make a copy to have the original image
    Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_5\\p5_search.png", IMREAD_GRAYSCALE);
    Mat dst = src.clone();
    Mat orig = src.clone();
    Mat hl = src.clone();

    // Read in the vowel templates
    Mat a = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\A.png", IMREAD_GRAYSCALE);
    Mat b = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\B.png", IMREAD_GRAYSCALE);
    Mat c = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\C.png", IMREAD_GRAYSCALE);
    Mat d = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\D.png", IMREAD_GRAYSCALE);
    Mat e = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\E.png", IMREAD_GRAYSCALE);
    Mat f = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\F.png", IMREAD_GRAYSCALE);
    Mat g = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\G.png", IMREAD_GRAYSCALE);
    Mat h = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\H.png", IMREAD_GRAYSCALE);
    Mat i = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\I.png", IMREAD_GRAYSCALE);
    Mat j = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\J.png", IMREAD_GRAYSCALE);
    Mat k = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\K.png", IMREAD_GRAYSCALE);
    Mat l = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\L.png", IMREAD_GRAYSCALE);
    Mat m = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\M.png", IMREAD_GRAYSCALE);
    Mat n = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\N.png", IMREAD_GRAYSCALE);
    Mat o = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\O.png", IMREAD_GRAYSCALE);
    Mat p = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\P.png", IMREAD_GRAYSCALE);
    Mat q = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\Q.png", IMREAD_GRAYSCALE);
    Mat r = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\R.png", IMREAD_GRAYSCALE);
    Mat s = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\S.png", IMREAD_GRAYSCALE);
    Mat t = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\T.png", IMREAD_GRAYSCALE);
    Mat u = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\U.png", IMREAD_GRAYSCALE);
    Mat v = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\V.png", IMREAD_GRAYSCALE);
    Mat w = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\W.png", IMREAD_GRAYSCALE);
    Mat x = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\X.png", IMREAD_GRAYSCALE);
    Mat y = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\Y.png", IMREAD_GRAYSCALE);
    Mat z = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\Z.png", IMREAD_GRAYSCALE);

    // Store templates and colors in an array for easy iteration
    Mat letterTemplates[] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
    char letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    // Remove the grid from the image (used for grid repair)
    bitwise_not(src, src);
    Mat grid = isolateGrid(src, dst);
    bitwise_not(hl, hl);
    bitwise_not(grid, grid);
    hl = hl-grid;
    bitwise_not(hl, hl);

    // Loop through all vowel templates
    for(int i = 0; i < 26; i++) {
        // Call the function that will determine locations of each vowel and color them (apply these to the same image)
        processLetter(orig, hl, letterTemplates[i], letters[i]);
    }

    // Add the grid back to the image (grid repair)
    bitwise_not(hl, hl);
    hl = hl+grid;
    bitwise_not(hl, hl);

    // Display final image
    imshow("Result", hl);

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

// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
// This code is based on the solution at this link
void processLetter(Mat src, Mat hl, Mat temp, char letter) {
    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    double thresh = 0.95;
    threshold(result, result, thresh, 1., THRESH_BINARY);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    result.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result (these will be all the points where A's are located)
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Process each matching A
    for (uint i=0; i<contours.size(); ++i)
    {
        // Mask out all other matching A's except the one that corresponds to the current contour
        Mat mask(result.rows, result.cols, uchar(0));
        drawContours(mask, contours, i, Scalar(255), FILLED);

        // Find the maximum matching location
        Point max_point;
        double max_val;
        minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);

        // Draw the font in different colors
        std::string s(1, letter);
        rectangle(hl, Rect(max_point.x, max_point.y, temp.cols, temp.rows), Scalar(255), FILLED);
        putText(hl, s, Point(max_point.x+10, max_point.y+30), FONT_HERSHEY_TRIPLEX, 1, Scalar(0), 1);
    }
}

// This is using the same process to isolate the grid as in part 2
Mat isolateGrid(Mat src, Mat dst) {
    // Extract the vertical lines of the grid
    Mat vert;
    Mat element1 = getStructuringElement( MORPH_RECT,
                         Size( 2*0 + 1, 2*17+1 ),
                         Point( 0, 17 ) );
    morphologyEx( src, vert, MORPH_OPEN, element1 );

    // Extract the horizontal lines of the grid
    Mat horiz;
    Mat element2 = getStructuringElement( MORPH_RECT,
                         Size( 2*10 + 1, 2*0+1 ),
                         Point( 10, 0 ) );
    morphologyEx( src, horiz, MORPH_OPEN, element2 );

    // Combine the horizontal and vertical lines into one image
    Mat grid = horiz+vert;

    // Determine the boundary of the image
    bool searchingRight = false;
    bool foundResult = false;
    int minRow = 0;
    int maxRow = 0;
    int minCol = 0;
    int maxCol = 0;
    for (int r = 0; r < grid.rows; r++) {
        for (int c = 0; c < grid.cols; c++) {
            if ((int) grid.at<uchar>(r, c) > 0 && minRow == 0) {
                minRow = r;
                minCol = c;
                searchingRight = true;
            }
            else if ((int) grid.at<uchar>(r, c) == 0 && searchingRight == true) {
                maxCol = c;
                maxRow = minRow + (maxCol - minCol);
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
    for (int i = 0; i < grid.rows; i++) {
        for (int j = 0; j < grid.cols; j++) {
            if (!(i >= minRow && i <= maxRow && j >= minCol && j <= maxCol)) {
                dst.at<uchar>(i, j) = 255;
            }
        }
    }

    // Subtract the horizontal and vertical from the inverted image (should remove those lines)
    Mat letters;
    bitwise_not(dst, letters);
    bitwise_not(dst, dst);
    letters = letters-vert;
    letters = letters-horiz;

    // Subtract the isolated characters image from the original inverted image (should leave only grid)
    grid = dst - letters;

    // Invert the colors of these results back to the original black and white composition
    bitwise_not(letters, letters);
    bitwise_not(grid, grid);

    // Show results
    return grid;
}

