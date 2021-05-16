
#include "includeLibraries.h"
#include <opencv2/opencv.hpp>
#include "matplotlibcpp.h"
#include "displayImages.h"

using namespace std;

using namespace cv;

using namespace matplotlibcpp;

Mat pencilSketch(Mat image, int arguments=0){
    
    Mat pencilSketchImage;
    
    /// YOUR CODE HERE
    // Apply Laplacian to image to get edges
    int kernelSize = 5;
    Mat LOG, img1;
    cvtColor(image, img1, COLOR_BGR2GRAY);
    GaussianBlur(img1, img1, Size(3,3), 0, 0);
    Laplacian(img1, LOG, CV_32F, kernelSize, 1, 0);
    normalize(LOG, pencilSketchImage, 0, 1, NORM_MINMAX, CV_32F);
    
    // Threshold the image to mimic pencil marks
    pencilSketchImage = pencilSketchImage * 255;
    threshold( pencilSketchImage, pencilSketchImage, 148, 255, THRESH_BINARY_INV );

    return pencilSketchImage;
}

Mat cartoonify(Mat image, int arguments=0){
    
    /// YOUR CODE HERE
    Mat cartoonImage;

    //diameter of the pixel neighbourhood used during filtering
    int dia=15;   

    // Larger the value the distant colours will be mixed together 
    // to produce areas of semi equal colors
    int sigmaColor=100; 

    // Larger the value more the influence of the farther placed pixels 
    // as long as their colors are close enough
    int sigmaSpace=30; 

    // Apply bilateral filter
    Mat tempImage = image.clone();
    bilateralFilter(image, tempImage, dia, 
                  sigmaColor, 
                  sigmaSpace);

    Mat edges = pencilSketch(image);

    tempImage.convertTo(tempImage, CV_8UC3);
    edges.convertTo(edges, CV_8UC1);
    cout << edges.size() << endl;
    cout << tempImage.size() << endl;
    bitwise_and(tempImage, tempImage, cartoonImage, edges);
    
    return cartoonImage;
    
}

string imagePath = DATA_PATH + "images/trump.jpg";
Mat image = imread(imagePath);

Mat cartoonImage = cartoonify(image);
Mat pencilSketchImage = pencilSketch(image);

plt::figure_size(1200,500);
plt::subplot(1,3,1);
plt::imshow(image);
auto pltImg = displayImage(image);
plt::subplot(1,3,2);
plt::imshow(cartoonImage);
pltImg = displayImage(cartoonImage);
plt::subplot(1,3,3);
plt::imshow(pencilSketchImage);
pltImg = displayImage(pencilSketchImage);
pltImg
