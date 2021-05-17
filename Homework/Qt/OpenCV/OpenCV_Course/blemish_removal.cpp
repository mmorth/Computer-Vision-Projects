//#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/photo.hpp>
//#include <vector>
//#include <iostream>
//#include <math.h>

//using namespace cv;
//using namespace std;

//// Source image
//Mat source;

//// Finds and returns the gradient of a Mat
//double findGradient(Mat image) {
//    Mat sobelx, sobely;

//    // Apply sobel filter with only x gradient
//    Sobel(image, sobelx, CV_32F, 1, 0);

//    // Apply sobel filter with only y gradient
//    Sobel(image, sobely, CV_32F, 0, 1);

//    Mat angle, mag;
//    cartToPolar(sobelx, sobely, mag, angle);

//    return mean(mag)[0];
//}

//// function which will be called on mouse input
//void removeBlemish(int action, int x, int y, int flags, void *userdata)
//{
//  // Action to be taken when left mouse button is pressed
//  if( action == EVENT_LBUTTONDBLCLK )
//  {
//    // Store clicked location (center of blemish window)
//    Point blemishPoint = Point(x,y);

//    // TODO: Find and remove blemish
//    // Find the location of highest gradient (laplacian) that likely corresponds to the blemish location
//    int windowSize = 5;

//    // Choose one of the surround 8 regions with lowest difference to the selected blemish region
//    vector<Mat> surroundingPatches;
//    surroundingPatches.push_back(source(Range(blemishPoint.y-windowSize/2, blemishPoint.y+windowSize/2+1), Range(blemishPoint.y-windowSize/2, blemishPoint.y+windowSize/2+1)).clone());

//    vector<double> gradients;
//    gradients.push_back(findGradient(source(Range(blemishPoint.y-windowSize/2, blemishPoint.y+windowSize/2+1), Range(blemishPoint.y-windowSize/2, blemishPoint.y+windowSize/2+1)).clone()));

//    int minGradIndex = INT_MAX;
//    double minGrad = DBL_MAX;
//    for (int i = 0; i < surroundingPatches.size(); i++)
//    {
//        double curGrad = findGradient(surroundingPatches.at(i));

//        if (curGrad < minGrad) {
//            minGrad = curGrad;
//            minGradIndex = i;
//        }
//    }

//    // Apply seamless cloning on the selected region with the blemish location
//    Mat bestPatch = surroundingPatches.at(minGradIndex);
//    Mat src_mask = 255 * Mat::ones(bestPatch.rows, bestPatch.cols, bestPatch.depth());
//    seamlessClone(bestPatch, source, src_mask, blemishPoint, source, NORMAL_CLONE);
//  }
//}

//int main()
//{
//  // Read blemish image
//  source = imread("blemish.png");

//  // Make a dummy image, will be useful to clear the drawing
//  Mat dummy = source.clone();
//  namedWindow("Window");

//  // highgui function called when mouse events occur
//  setMouseCallback("Window", removeBlemish);

//  // Stores the pressed key
//  int k=0;

//  // loop until escape character is pressed
//  while(k!=27)
//  {
//    imshow("Window", source );
//    putText(source, "Click on blemish to remove and c to clear", Point(10,30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 2);
//    k= waitKey(20) & 0xFF;

//    if(k== 99)
//            // Clear image if c button pressed
//            dummy.copyTo(source);
//  }

//  return 0;
//}
