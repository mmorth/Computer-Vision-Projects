#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main()
{
  // Read in the input image and create separate images for the handle and disk
  Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p1\\1a.png", IMREAD_GRAYSCALE);
  Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p1\\1b.png", IMREAD_GRAYSCALE);

  imshow("src1", src1);
  imshow("src2", src2);

  waitKey(0);
  return 0;
}
