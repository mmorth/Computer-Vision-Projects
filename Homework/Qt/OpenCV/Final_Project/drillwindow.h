#ifndef DRILLWINDOW_H
#define DRILLWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

// Source: https://amin-ahmadi.com/2018/03/29/how-to-read-process-and-display-videos-using-qt-and-opencv/
namespace Ui {
class DrillWindow;
}

class DrillWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrillWindow(QWidget *parent = nullptr);
    ~DrillWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_startBtn_pressed();

private:
    Ui::DrillWindow *ui;

    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;
};

#endif // DRILLWINDOW_H
