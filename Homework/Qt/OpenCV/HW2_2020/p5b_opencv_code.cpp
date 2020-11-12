#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

struct piece {
    string name = "Empty";
    int value = 0;
};

piece board1[8][8];
piece board2[8][8];
piece board3[8][8];

void processPieceMatch(Mat src, Mat temp, string name, int board);

int main()
{
    char keyPress;
    cout << "p1_opencv\n";
    // Read image
    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_5\\p5_board_1b_grain.jpg", IMREAD_GRAYSCALE);
    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_5\\p5_board_2b_grain.jpg", IMREAD_GRAYSCALE);
    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_5\\p5_board_3b_grain.jpg", IMREAD_GRAYSCALE);

    // Load the knight chess piece templates
    Mat brd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackRookDark.jpg", IMREAD_GRAYSCALE);
    Mat brl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackRookLight.jpg", IMREAD_GRAYSCALE);
    Mat wrd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteRookDark.jpg", IMREAD_GRAYSCALE);
    Mat wrl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteRookLight.jpg", IMREAD_GRAYSCALE);

    Mat bbd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackBishopDark.jpg", IMREAD_GRAYSCALE);
    Mat bbl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackBishopLight.jpg", IMREAD_GRAYSCALE);
    Mat wbd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteBishopDark.jpg", IMREAD_GRAYSCALE);
    Mat wbl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteBishopLight.jpg", IMREAD_GRAYSCALE);

    Mat bqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackQueenDark.jpg", IMREAD_GRAYSCALE);
    Mat bql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackQueenLight.jpg", IMREAD_GRAYSCALE);
    Mat wqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteQueenDark.jpg", IMREAD_GRAYSCALE);
    Mat wql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteQueenLight.jpg", IMREAD_GRAYSCALE);

    Mat bkd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackKnightDark.jpg", IMREAD_GRAYSCALE);
    Mat bkl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackKnightLight.jpg", IMREAD_GRAYSCALE);
    Mat wkd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteKnightDark.jpg", IMREAD_GRAYSCALE);
    Mat wkl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteKnightLight.jpg", IMREAD_GRAYSCALE);

    Mat bgd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackKingDark.jpg", IMREAD_GRAYSCALE);
    Mat bgl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackKingLight.jpg", IMREAD_GRAYSCALE);
    Mat wgd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteKingDark.jpg", IMREAD_GRAYSCALE);
    Mat wgl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteKingLight.jpg", IMREAD_GRAYSCALE);

    Mat bpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnDark.jpg", IMREAD_GRAYSCALE);
    Mat bpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnLight.jpg", IMREAD_GRAYSCALE);
    Mat wpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnDark.jpg", IMREAD_GRAYSCALE);
    Mat wpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnLight.jpg", IMREAD_GRAYSCALE);

    Mat pieceTemplates[] = {brd,brl,wrd,wrl,bbd,bbl,wbd,wbl,bqd,bql,wqd,wql,bkd,bkl,wkd,wkl,bgd,bgl,wgd,wgl,bpd,bpl,wpd,wpl};
    string pieceNames[] = {"Black Rook", "Black Rook", "White Rook", "White Rook",
                       "Black Bishop", "Black Bishop", "White Bishop", "White Bishop",
                       "Black Queen", "Black Queen", "White Queen", "White Queen",
                       "Black Knight", "Black Knight", "White Knight", "White Knight",
                       "Black King", "Black King", "White King", "White King",
                       "Black Pawn", "Black Pawn", "White Pawn", "White Pawn"};
    int numPieceTemplates = 24;

    // Apply median blur to remove noise
    int b = 5;
    medianBlur(src1, src1, b);
    medianBlur(src2, src2, b);
    medianBlur(src3, src3, b);

    for (int i = 0; i < numPieceTemplates; i++) {
        medianBlur(pieceTemplates[i], pieceTemplates[i], b);
        processPieceMatch(src1, pieceTemplates[i], pieceNames[i], 1);
        processPieceMatch(src2, pieceTemplates[i], pieceNames[i], 2);
        processPieceMatch(src3, pieceTemplates[i], pieceNames[i], 3);
    }

    // Write output to file
    ofstream Board1File("p5a_result_1_grain.txt");
    ofstream Board2File("p5a_result_2_grain.txt");
    ofstream Board3File("p5a_result_3_grain.txt");
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            // Print results to files
            std::string s(1, letters[col]);
            string position = s + std::to_string(8-row);
            Board1File << position.c_str() << ": " << board1[row][col].name.c_str() << "\n";
            Board2File << position << ": " << board2[row][col].name << "\n";
            Board3File << position << ": " << board3[row][col].name << "\n";
        }
    }

    Board1File.close();
    Board2File.close();
    Board3File.close();
    cout << "Successfully completed!\n";
}

// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
// This code is based on the solution at this link
void processPieceMatch(Mat src, Mat temp, string name, int board) {
    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    double thresh = 0.99;
    threshold(result, result, thresh, 1., THRESH_BINARY);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    result.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
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

        // See if the current piece has a larger coorelation value than current max point
        if (board == 1) {
            if (max_val > board1[max_point.y/60][max_point.x/60].value) {
                piece cur;
                cur.name = name;
                cur.value = max_val;
                board1[max_point.y/60][max_point.x/60] = cur;
            }
        } else if (board == 2) {
            if (max_val > board2[max_point.y/60][max_point.x/60].value) {
                piece cur;
                cur.name = name;
                cur.value = max_val;
                board2[max_point.y/60][max_point.x/60] = cur;
            }
        } else {
            if (max_val > board3[max_point.y/60][max_point.x/60].value) {
                piece cur;
                cur.name = name;
                cur.value = max_val;
                board3[max_point.y/60][max_point.x/60] = cur;
            }
        }
    }
}
