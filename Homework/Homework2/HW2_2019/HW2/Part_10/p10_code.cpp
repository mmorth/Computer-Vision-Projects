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
enum BoardType { dogs, fruits, schoolLife, dogsNoisy, fruitsNoisy, schoolLifeNoisy };
enum MovementDirection { upLeft, up, upRight, leftMove, rightMove, downLeft, down, downRight, none };
string dogWords[] = {"DALMATIAN", "DAUCHSHUND", "BEAGLE", "PINSCHER", "SHEPHERD", "MASTIFF", "SETTER", "CHIHUAHUA", "BULLDOG", "COLLIE", "HOUND", "CORGI", "TERRIER", "BOXER"};
int numDogWords = 14;
char dogBoard[14][14];
char dogBoardNoisy[14][14];
Mat hlDog;
Mat hlDogNoisy;
string fruitsWords[] = {"RASPBERRY", "LIME", "BLACKBERRY", "BLUEBERRY", "WATERMELON", "ORANGE", "BANANA", "PAPAYA", "LEMON", "KIWI", "STRAWBERRY", "GRAPE", "APPLE"};
int numFruitWords = 13;
char fruitBoard[14][14];
char fruitBoardNoisy[14][14];
Mat hlFruit;
Mat hlFruitNoisy;
string schoolLifeWords[] = {"GLITTER", "SHARPENER", "HOMEWORK", "JOURNAL", "ERASER", "BLACKBOARD", "NOTEBOOK", "BACKPACK", "CRAYONS", "SCISSORS", "GLUESTICK", "MARKERS", "BOOKS", "CALCULATION", "COMPASS", "PENS"};
int numSchoolLifeWords = 16;
char schoolBoard[14][14];
char schoolBoardNoisy[14][14];
Mat hlSchool;
Mat hlSchoolNoisy;
Mat tempMatch;
vector<int> locations;

void processLetter(Mat src, Mat temp, char letter, BoardType type);
bool dfs(int row, int col, int index, string word, vector<gridLocation> previousLetterMatches, MovementDirection move, BoardType type);

int main()
{
    char keyPress;
    cout << "p10_opencv_code.cpp\n";

    locations.push_back(5);
    locations.push_back(9);

    // Read image and make a copy to have the original image
    Mat srcDog = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_10\\p10_search1.png", IMREAD_GRAYSCALE);
    Mat dstDog = srcDog.clone();
    hlDog = srcDog.clone();
    Mat srcFruit = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_10\\p10_search2.png", IMREAD_GRAYSCALE);
    Mat dstFruit = srcFruit.clone();
    hlFruit = srcFruit.clone();
    Mat srcSchool = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_10\\p10_search3.png", IMREAD_GRAYSCALE);
    Mat dstSchool = srcSchool.clone();
    hlSchool = srcSchool.clone();

    // Read noisy image variants
    Mat srcDogNoisy = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_10\\p10_noisy_search1.png", IMREAD_GRAYSCALE);
    Mat dstDogNoisy = srcDogNoisy.clone();
    hlDogNoisy = srcDogNoisy.clone();
    Mat srcFruitNoisy = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_10\\p10_noisy_search2.png", IMREAD_GRAYSCALE);
    Mat dstFruitNoisy = srcFruitNoisy.clone();
    hlFruitNoisy = srcFruitNoisy.clone();
    Mat srcSchoolNoisy = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_10\\p10_noisy_search3.png", IMREAD_GRAYSCALE);
    Mat dstSchoolNoisy = srcSchoolNoisy.clone();
    hlSchoolNoisy = srcSchoolNoisy.clone();

    // Read in the letter templates
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
    cvtColor(hlDog, hlDog, COLOR_GRAY2BGR);
    cvtColor(hlFruit, hlFruit, COLOR_GRAY2BGR);
    cvtColor(hlSchool, hlSchool, COLOR_GRAY2BGR);

    // Compute the grid letter locations
    for(int i = 0; i < 26; i++) {
        // Call the function that will determine locations of each vowel and color them (apply these to the same image)
        processLetter(srcDog, letterTemplates[i], letters[i], dogs);
        processLetter(srcFruit, letterTemplates[i], letters[i], fruits);
        processLetter(srcSchool, letterTemplates[i], letters[i], schoolLife);
    }

    // Search for each word in grid
    for (int i = 0; i < numDogWords; i++) {
        char firstLetter = dogWords[i].at(0);
        bool found = false;
        // Loop through each row in grid
        for (int row = 0; row < 14; row++) {
            // Loop through each col in grid
            for (int col = 0; col < 14; col++) {
                // Check if current position matches first letter of word
                if (dogBoard[col][row] == firstLetter) {
                    // See if match starts at this location
                    vector<gridLocation> list;
                    bool result = dfs(row, col, 0, dogWords[i], list, none, dogs);
                    if (result) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) {
                break;
            }
        }
    }

    // Convert dst to BGR to color A matches
    cvtColor(dstDog, dstDog, COLOR_GRAY2BGR);
    addWeighted(hlDog, 0.5, dstDog, 0.5, 0, dstDog);

    // Display final image
    imshow("Dog Result", dstDog);

    for (int i = 0; i < numFruitWords; i++) {
        char firstLetter = fruitsWords[i].at(0);
        bool found = false;
        // Loop through each row in grid
        for (int row = 0; row < 14; row++) {
            // Loop through each col in grid
            for (int col = 0; col < 14; col++) {
                // Check if current position matches first letter of word
                if (fruitBoard[col][row] == firstLetter) {
                    // See if match starts at this location
                    vector<gridLocation> list;
                    bool result = dfs(row, col, 0, fruitsWords[i], list, none, fruits);
                    if (result) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) {
                break;
            }
        }
    }

    // Convert dst to BGR to color A matches
    cvtColor(dstFruit, dstFruit, COLOR_GRAY2BGR);
    addWeighted(hlFruit, 0.5, dstFruit, 0.5, 0, dstFruit);

    // Display final image
    imshow("Fruit Result", dstFruit);

    for (int i = 0; i < numSchoolLifeWords; i++) {
        char firstLetter = schoolLifeWords[i].at(0);
        bool found = false;
        // Loop through each row in grid
        for (int row = 0; row < 14; row++) {
            // Loop through each col in grid
            for (int col = 0; col < 14; col++) {
                // Check if current position matches first letter of word
                if (schoolBoard[col][row] == firstLetter) {
                    // See if match starts at this location
                    vector<gridLocation> list;
                    bool result = dfs(row, col, 0, schoolLifeWords[i], list, none, schoolLife);
                    if (result) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) {
                break;
            }
        }
    }

    // Convert dst to BGR to color A matches
    cvtColor(dstSchool, dstSchool, COLOR_GRAY2BGR);
    addWeighted(hlSchool, 0.5, dstSchool, 0.5, 0, dstSchool);

    // Display final image
    imshow("School Result", dstSchool);

    // Process noisy letters
    for (int i = 0; i < 26; i++) {
        medianBlur(letterTemplates[i], letterTemplates[i], 3);
    }

    // Process noisy boards
    medianBlur(srcDogNoisy, srcDogNoisy, 3);
    medianBlur(srcFruitNoisy, srcFruitNoisy, 3);
    medianBlur(srcSchoolNoisy, srcSchoolNoisy, 3);

    // Convert highlights to color
    cvtColor(hlDogNoisy, hlDogNoisy, COLOR_GRAY2BGR);
    cvtColor(hlFruitNoisy, hlFruitNoisy, COLOR_GRAY2BGR);
    cvtColor(hlSchoolNoisy, hlSchoolNoisy, COLOR_GRAY2BGR);

    for (int i = 0; i < 26; i++) {
        processLetter(srcDogNoisy, letterTemplates[i], letters[i], dogsNoisy);
        processLetter(srcFruitNoisy, letterTemplates[i], letters[i], fruitsNoisy);
        processLetter(srcSchoolNoisy, letterTemplates[i], letters[i], schoolLifeNoisy);
    }

    // Search for each word in grid
    for (int i = 0; i < numDogWords; i++) {
        char firstLetter = dogWords[i].at(0);
        bool found = false;
        // Loop through each row in grid
        for (int row = 0; row < 14; row++) {
            // Loop through each col in grid
            for (int col = 0; col < 14; col++) {
                // Check if current position matches first letter of word
                if (dogBoardNoisy[col][row] == firstLetter) {
                    // See if match starts at this location
                    vector<gridLocation> list;
                    bool result = dfs(row, col, 0, dogWords[i], list, none, dogsNoisy);
                    if (result) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) {
                break;
            }
        }
    }

    // Convert dst to BGR to color A matches
    cvtColor(dstDogNoisy, dstDogNoisy, COLOR_GRAY2BGR);
    addWeighted(hlDogNoisy, 0.5, dstDogNoisy, 0.5, 0, dstDogNoisy);

    // Display final image
    imshow("Dog Result Noisy", dstDogNoisy);

    for (int i = 0; i < numFruitWords; i++) {
        char firstLetter = fruitsWords[i].at(0);
        bool found = false;
        // Loop through each row in grid
        for (int row = 0; row < 14; row++) {
            // Loop through each col in grid
            for (int col = 0; col < 14; col++) {
                // Check if current position matches first letter of word
                if (fruitBoardNoisy[col][row] == firstLetter) {
                    // See if match starts at this location
                    vector<gridLocation> list;
                    bool result = dfs(row, col, 0, fruitsWords[i], list, none, fruitsNoisy);
                    if (result) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) {
                break;
            }
        }
    }

    // Convert dst to BGR to color A matches
    cvtColor(dstFruitNoisy, dstFruitNoisy, COLOR_GRAY2BGR);
    addWeighted(hlFruitNoisy, 0.5, dstFruitNoisy, 0.5, 0, dstFruitNoisy);

    // Display final image
    imshow("Fruit Result Noisy", dstFruitNoisy);

    for (int i = 0; i < numSchoolLifeWords; i++) {
        char firstLetter = schoolLifeWords[i].at(0);
        bool found = false;
        // Loop through each row in grid
        for (int row = 0; row < 14; row++) {
            // Loop through each col in grid
            for (int col = 0; col < 14; col++) {
                // Check if current position matches first letter of word
                if (schoolBoardNoisy[col][row] == firstLetter) {
                    // See if match starts at this location
                    vector<gridLocation> list;
                    bool result = dfs(row, col, 0, schoolLifeWords[i], list, none, schoolLifeNoisy);
                    if (result) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) {
                break;
            }
        }
    }

    // Convert dst to BGR to color A matches
    cvtColor(dstSchoolNoisy, dstSchoolNoisy, COLOR_GRAY2BGR);
    addWeighted(hlSchoolNoisy, 0.5, dstSchoolNoisy, 0.5, 0, dstSchoolNoisy);

    // Display final image
    imshow("School Result Noisy", dstSchoolNoisy);

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
void processLetter(Mat src, Mat temp, char letter, BoardType type) {
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
        int colPos = (max_point.x - 30) / 39;
        int rowPos = (max_point.y - 90) / 39;

        if (type == dogs) {
            dogBoard[colPos][rowPos] = letter;
        } else if (type == fruits) {
            fruitBoard[colPos][rowPos] = letter;
        } else if (type == schoolLife) {
            schoolBoard[colPos][rowPos] = letter;
        } else if (type == dogsNoisy) {
            dogBoardNoisy[colPos][rowPos] = letter;
        } else if (type == fruitsNoisy) {
            fruitBoardNoisy[colPos][rowPos] = letter;
        } else {
            schoolBoardNoisy[colPos][rowPos] = letter;
        }
    }
}

// Run depth-first search to find the words in the grid
bool dfs(int row, int col, int index, string word, vector<gridLocation> previousLetterMatches, MovementDirection move, BoardType type) {
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
            if (type == dogs) {
                rectangle(hlDog, Rect(pixelCol, pixelRow, tempMatch.cols, tempMatch.rows), color, FILLED);
            } else if (type == fruits) {
                rectangle(hlFruit, Rect(pixelCol, pixelRow, tempMatch.cols, tempMatch.rows), color, FILLED);
            } else if (type == schoolLife) {
                rectangle(hlSchool, Rect(pixelCol, pixelRow, tempMatch.cols, tempMatch.rows), color, FILLED);
            } else if (type == dogsNoisy) {
                rectangle(hlDogNoisy, Rect(pixelCol, pixelRow, tempMatch.cols, tempMatch.rows), color, FILLED);
            } else if (type == fruitsNoisy) {
                rectangle(hlFruitNoisy, Rect(pixelCol, pixelRow, tempMatch.cols, tempMatch.rows), color, FILLED);
            } else {
                rectangle(hlSchoolNoisy, Rect(pixelCol, pixelRow, tempMatch.cols, tempMatch.rows), color, FILLED);
            }
        }

        return true;
    } else if (row < 0 || row > 13 || col < 0 || col > 13) {
        // Out of bounds
        return false;
    } else {
        if (type == dogs && word.at(index) != dogBoard[col][row]) {
            return false;
        } else if (type == fruits && word.at(index) != fruitBoard[col][row]) {
            return false;
        } else if (type == schoolLife && word.at(index) != schoolBoard[col][row]) {
            return false;
        } else if (type == dogsNoisy && word.at(index) != dogBoardNoisy[col][row]) {
            return false;
        } else if (type == fruitsNoisy && word.at(index) != fruitBoardNoisy[col][row]) {
            return false;
        } else if (type == schoolLifeNoisy && word.at(index) != schoolBoardNoisy[col][row]) {
            return false;
        }

        // Match found at location
        gridLocation position;
        position.row = row;
        position.col = col;
        previousLetterMatches.push_back(position);

        // Check if entire string can be found starting at current location
        bool found = false;

        char temp;
        if (type == dogs) {
            temp = dogBoard[col][row];
            dogBoard[col][row] = '*';
        } else if (type == fruits) {
            temp = fruitBoard[col][row];
            fruitBoard[col][row] = '*';
        } else if (type == schoolLife) {
            temp = schoolBoard[col][row];
            schoolBoard[col][row] = '*';
        } else if (type == dogsNoisy) {
            temp = dogBoardNoisy[col][row];
            dogBoardNoisy[col][row] = '*';
        } else if (type == fruitsNoisy) {
            temp = fruitBoardNoisy[col][row];
            fruitBoardNoisy[col][row] = '*';
        } else {
            temp = schoolBoardNoisy[col][row];
            schoolBoardNoisy[col][row] = '*';
        }

        // Determine valid movement directions based on prior move
        if (move == upLeft) {
            if (dfs(row-1, col-1, index+1, word, previousLetterMatches, upLeft, type)) {
                found = true;
            }
        } else if (move == up) {
            if (dfs(row-1, col, index+1, word, previousLetterMatches, up, type)) {
                found = true;
            }
        } else if (move == upRight) {
            if (dfs(row-1, col+1, index+1, word, previousLetterMatches, upRight, type)) {
                found = true;
            }
        } else if (move == leftMove) {
            if (dfs(row, col-1, index+1, word, previousLetterMatches, leftMove, type)) {
                found = true;
            }
        } else if (move == rightMove) {
            if (dfs(row, col+1, index+1, word, previousLetterMatches, rightMove, type)) {
                found = true;
            }
        } else if (move == downLeft) {
            if (dfs(row+1, col-1, index+1, word, previousLetterMatches, downLeft, type)) {
                found = true;
            }
        } else if (move == down) {
            if (dfs(row+1, col, index+1, word, previousLetterMatches, down, type)) {
                found = true;
            }
        } else if (move == downRight) {
            if (dfs(row+1, col+1, index+1, word, previousLetterMatches, downRight, type)) {
                found = true;
            }
        } else {
            if (dfs(row-1, col-1, index+1, word, previousLetterMatches, upLeft, type) ||
                    dfs(row-1, col, index+1, word, previousLetterMatches, up, type) ||
                    dfs(row-1, col+1, index+1, word, previousLetterMatches, upRight, type) ||
                    dfs(row, col-1, index+1, word, previousLetterMatches, leftMove, type) ||
                    dfs(row, col+1, index+1, word, previousLetterMatches, rightMove, type) ||
                    dfs(row+1, col-1, index+1, word, previousLetterMatches, downLeft, type) ||
                    dfs(row+1, col, index+1, word, previousLetterMatches, down, type) ||
                    dfs(row+1, col+1, index+1, word, previousLetterMatches, downRight, type)) {
                found = true;
            }
        }

        if (!found) {
            previousLetterMatches.pop_back();
        }

        if (type == dogs) {
            dogBoard[col][row] = temp;
        } else if (type == fruits) {
            fruitBoard[col][row] = temp;
        } else if (type == schoolLife) {
            schoolBoard[col][row] = temp;
        } else if (type == dogsNoisy) {
            dogBoardNoisy[col][row] = temp;
        } else if (type == fruitsNoisy) {
            fruitBoardNoisy[col][row] = temp;
        } else {
            schoolBoardNoisy[col][row] = temp;
        }

        return found;
    }
}

