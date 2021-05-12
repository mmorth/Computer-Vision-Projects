#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

// Points to store the center of the circle and a point on the circumference
Point topLeft, bottomRight;
// Source image
Mat source;

// function which will be called on mouse input
void drawRectangleAndSaveImage(int action, int x, int y, int flags, void *userdata)
{
  // Action to be taken when left mouse button is pressed
  if( action == EVENT_LBUTTONDOWN )
  {
    topLeft = Point(x,y);
  }
  // Action to be taken when left mouse button is released
  else if( action == EVENT_LBUTTONUP)
  {
    bottomRight = Point(x,y);
    rectangle(source, topLeft, bottomRight, Scalar(255, 0, 255), 5, LINE_8);
    imwrite("face.png", source);
    imshow("Window", source);
  }
}

int main()
{
  source = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\OpenCVCourse\\week2-cpp\\sample.jpg");
  // Make a dummy image, will be useful to clear the drawing
  Mat dummy = source.clone();
  namedWindow("Window");
  // highgui function called when mouse events occur
  setMouseCallback("Window", drawRectangleAndSaveImage);
  int k=0;
  // loop until escape character is pressed
  while(k!=27)
  {
    imshow("Window", source );
    k= waitKey(20) & 0xFF;
    if(k== 99)
            // Another way of cloning
            dummy.copyTo(source);
  }
  return 0;
}
