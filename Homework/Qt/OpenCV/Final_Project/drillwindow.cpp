#include "drillwindow.h"
#include "ui_drillwindow.h"
#include <iostream>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

DrillWindow::DrillWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrillWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);
}

DrillWindow::~DrillWindow()
{
    delete ui;
}

void DrillWindow::on_startBtn_pressed()
{
    using namespace cv;

    if(video.isOpened())
    {
        ui->pushButton->setText("Start");
        video.release();
        return;
    }

    bool isCamera = true;
    int cameraIndex = 1;
    if(isCamera)
    {
        if(!video.open(cameraIndex))
        {
            QMessageBox::critical(this,
                                  "Camera Error",
                                  "Make sure you entered a correct camera index,"
                                  "<br>or that the camera is not being accessed by another program!");
            return;
        }
    }
//    else
//    {
//        if(!video.open(ui->videoEdit->text().trimmed().toStdString()))
//        {
//            QMessageBox::critical(this,
//                                  "Video Error",
//                                  "Make sure you entered a correct and supported video file path,"
//                                  "<br>or a correct RTSP feed URL!");
//            return;
//        }
//    }

    ui->pushButton->setText("Stop");

    Mat frame;
    while(video.isOpened())
    {
        video >> frame;
        if(!frame.empty())
        {
            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
        }
        qApp->processEvents();
    }

    ui->pushButton->setText("Start");
}

void DrillWindow::closeEvent(QCloseEvent *event)
{
    if(video.isOpened())
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Stop the video before closing the application!");
        event->ignore();
    }
    else
    {
        event->accept();
    }
}
