#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <math.h>

using namespace std;
using namespace cv;

RNG rng(12345);
struct gridLocation {
    int row;
    int col;
};
enum MovementDirection { upLeft, up, upRight, leftMove, rightMove, downLeft, down, downRight, none };
string wordsToSearch[] = {"LINEAR", "ALGEBRA"};
int numWords = 2;
char board[14][14];
Mat hl1;
Mat hl2;
Mat tempMatch;
vector<int> locations;

void processLetter(Mat src, Mat temp, char letter);
bool dfs(int row, int col, int index, string word, vector<gridLocation> previousLetterMatches, MovementDirection move);

int main()
{
    char keyPress;
    cout << "p8_opencv_code.cpp\n";

    locations.push_back(5);
    locations.push_back(9);

    // Read image and template and make a copy to have the original image
    Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_8\\p8_search.png", IMREAD_GRAYSCALE);
    Mat dst1 = src.clone();
    Mat dst2 = src.clone();
    hl1 = src.clone();
    hl2 = src.clone();

    // Read in the vowel templates
    tempMatch = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\A.png", IMREAD_GRAYSCALE);
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

    // Change hl (highlighted) from grayscale to BGR to enable coloring of letters
    cvtColor(hl1, hl1, COLOR_GRAY2BGR);
    cvtColor(hl2, hl2, COLOR_GRAY2BGR);

    // Loop through all vowel templates
    for(int i = 0; i < 26; i++) {
        // Call the function that will determine locations of each vowel and color them (apply these to the same image)
        processLetter(src, letterTemplates[i], letters[i]);
    }

    // Search for each word in grid
    string word = wordsToSearch[0];
    char firstLetter = wordsToSearch[0].at(0);
    // Loop through each row in grid
    for (int row = 0; row < 14; row++) {
        // Loop through each col in grid
        for (int col = 0; col < 14; col++) {
            // Check if current position matches first letter of word
            if (board[col][row] == firstLetter) {
                // See if match starts at this location
                vector<gridLocation> list;
                bool result = dfs(row, col, 0, wordsToSearch[0], list, none);
                if (result) {
                    break;
                }
            }
        }
    }

    // Convert dst to BGR to color A matches
    cvtColor(dst1, dst1, COLOR_GRAY2BGR);
    addWeighted(hl1, 0.5, dst1, 0.5, 0, dst1);

    // Display final image
    imshow("Result1", dst1);

    word = wordsToSearch[1];
    firstLetter = wordsToSearch[1].at(0);
    // Loop through each row in grid
    for (int row = 0; row < 14; row++) {
        // Loop through each col in grid
        for (int col = 0; col < 14; col++) {
            // Check if current position matches first letter of word
            if (board[col][row] == firstLetter) {
                // See if match starts at this location
                vector<gridLocation> list;
                bool result = dfs(row, col, 0, wordsToSearch[1], list, none);
                if (result) {
                    break;
                }
            }
        }
    }

    // Convert dst to BGR to color A matches
    cvtColor(dst2, dst2, COLOR_GRAY2BGR);
    addWeighted(hl2, 0.5, dst2, 0.5, 0, dst2);

    // Display final image
    imshow("Result2", dst2);

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
void processLetter(Mat src, Mat temp, char letter) {
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

        // Store the detected letter in the correct location in board
        int colPos = (max_point.x - 30) / 40;
        int rowPos = (max_point.y - 90) / 40;
        board[colPos][rowPos] = letter;
    }
}

// Run depth-first search to find the words in the grid
bool dfs(int row, int col, int index, string word, vector<gridLocation> previousLetterMatches, MovementDirection move) {
    // Check what position the move recent find is
    if (index == word.size()) {
        // Shade all locations in match
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256));
        for (int i = 0; i < previousLetterMatches.size(); i++) {
            // Convert board position to pixel location
            gridLocation cur = previousLetterMatches.at(i);
            int pixelRow = 0;
            if(std::find(locations.begin(), locations.end(), cur.row) != locations.end()) {
                pixelRow = (cur.row * 41) + 90 + 1;
            } else {
                pixelRow = (cur.row * 41) + 90;
            }
            int pixelCol = (cur.col * 41) + 30 + ceil(cur.col/2.0);

            // Highlight the matching squares
            if (word == "LINEAR") {
                rectangle(hl1, Rect(pixelCol, pixelRow, tempMatch.cols, tempMatch.rows), color, FILLED);
            } else {
                rectangle(hl2, Rect(pixelCol, pixelRow, tempMatch.cols, tempMatch.rows), color, FILLED);
            }
        }

        return true;
    } else if (row < 0 || row > 13 || col < 0 || col > 13) {
        // Out of bounds
        return false;
    } else if (word.at(index) != board[col][row]) {
        // No matching letter in this direction
        return false;
    } else {
        // Match found at location
        gridLocation position;
        position.row = row;
        position.col = col;
        previousLetterMatches.push_back(position);

        // Check if entire string can be found starting at current location
        bool found = false;

        char temp = board[col][row];
        board[col][row] = '*';

        // Determine valid movement directions based on prior move
        if (move == upLeft) {
            if (dfs(row-1, col-1, index+1, word, previousLetterMatches, upLeft)) {
                found = true;
            }
        } else if (move == up) {
            if (dfs(row-1, col, index+1, word, previousLetterMatches, up)) {
                found = true;
            }
        } else if (move == upRight) {
            if (dfs(row-1, col+1, index+1, word, previousLetterMatches, upRight)) {
                found = true;
            }
        } else if (move == leftMove) {
            if (dfs(row, col-1, index+1, word, previousLetterMatches, leftMove)) {
                found = true;
            }
        } else if (move == rightMove) {
            if (dfs(row, col+1, index+1, word, previousLetterMatches, rightMove)) {
                found = true;
            }
        } else if (move == downLeft) {
            if (dfs(row+1, col-1, index+1, word, previousLetterMatches, downLeft)) {
                found = true;
            }
        } else if (move == down) {
            if (dfs(row+1, col, index+1, word, previousLetterMatches, down)) {
                found = true;
            }
        } else if (move == downRight) {
            if (dfs(row+1, col+1, index+1, word, previousLetterMatches, downRight)) {
                found = true;
            }
        } else {
            if (dfs(row-1, col-1, index+1, word, previousLetterMatches, upLeft) ||
                    dfs(row-1, col, index+1, word, previousLetterMatches, up) ||
                    dfs(row-1, col+1, index+1, word, previousLetterMatches, upRight) ||
                    dfs(row, col-1, index+1, word, previousLetterMatches, leftMove) ||
                    dfs(row, col+1, index+1, word, previousLetterMatches, rightMove) ||
                    dfs(row+1, col-1, index+1, word, previousLetterMatches, downLeft) ||
                    dfs(row+1, col, index+1, word, previousLetterMatches, down) ||
                    dfs(row+1, col+1, index+1, word, previousLetterMatches, downRight)) {
                found = true;
            }
        }

        if (!found) {
            previousLetterMatches.pop_back();
        }

        board[col][row] = temp;
        return found;
    }
}
