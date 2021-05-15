//#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <vector>
//#include <iostream>
//#include <math.h>

//using namespace cv;
//using namespace std;

//// Points to store the top left and bottom right corners of the image
//Point topLeft, bottomRight;
//// Source image
//Mat source;

//// function which will be called on mouse input
//void drawRectangleAndSaveImage(int action, int x, int y, int flags, void *userdata)
//{
//  // Action to be taken when left mouse button is pressed
//  if( action == EVENT_LBUTTONDOWN )
//  {
//    // Mark top left corner of selection
//    topLeft = Point(x,y);
//  }
//  // Action to be taken when left mouse button is released
//  else if( action == EVENT_LBUTTONUP)
//  {
//    // Mark bottom right corner of selection
//    bottomRight = Point(x,y);
//    // Write face to image file
//    Mat face = source(Range(topLeft.y, bottomRight.y), Range(topLeft.x, bottomRight.x));
//    imwrite("face.png", face);
//    // Draw rectangle selection on image
//    rectangle(source, topLeft, bottomRight, Scalar(255, 0, 255), 5, LINE_8);
//    imshow("Window", source);
//  }
//}

//int main()
//{
//  // Read image
//  source = imread("sample.jpg");
//  // Make a dummy image, will be useful to clear the drawing
//  Mat dummy = source.clone();
//  namedWindow("Window");
//  // highgui function called when mouse events occur
//  setMouseCallback("Window", drawRectangleAndSaveImage);
//  int k=0;
//  // loop until escape character is pressed
//  while(k!=27)
//  {
//    imshow("Window", source );
//    putText(source,"Choose top left corner and drag" ,Point(10,30), FONT_HERSHEY_SIMPLEX, 0.7,Scalar(255,255,255), 2 );
//    k= waitKey(20) & 0xFF;
//    if(k== 99)
//            // Another way of cloning
//            dummy.copyTo(source);
//  }
//  return 0;
//}
