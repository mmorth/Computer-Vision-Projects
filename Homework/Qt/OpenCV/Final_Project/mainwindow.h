//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

//#include <QMainWindow>
//#include <QDebug>
//#include <QGraphicsScene>
//#include <QGraphicsPixmapItem>
//#include <QImage>
//#include <QPixmap>
//#include <QCloseEvent>
//#include <QMessageBox>

//#include <iostream>
//#include <chrono>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//namespace Ui {
//class MainWindow;
//}

//class MainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    explicit MainWindow(QWidget *parent = 0);
//    ~MainWindow();

//protected:
//    void closeEvent(QCloseEvent *event);
//    void processVideo(VideoCapture cap);
//    void findPersonAndDrawTargets(Mat frame, Mat mask);
//    void detectFacePosition(Mat f, Mat mask);
//    void detectBasketballPosition(Mat frame, Mat mask);
//    void determineBallTargetIntersection();
//    void executeOpenCV();

//private slots:
//    void on_startButton_pressed();

//private:
//    Ui::MainWindow *ui;

//    QGraphicsPixmapItem pixmap;
//    cv::VideoCapture video;
//};

//#endif // MAINWINDOW_H
