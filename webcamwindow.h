#ifndef WEBCAMWINDOW_H
#define WEBCAMWINDOW_H

#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

class WebCamWindow : public QWidget
{
    Q_OBJECT
    
public:
    WebCamWindow(QWidget *parent = 0);
    ~WebCamWindow();
    void displayImage(QLabel* _destination);
    void detectHand(int x=125, int y=145);
    void trackHand();
    int getX() { return x;}
    int getY() { return y;}

    void startWebCam();

public slots:
    void aquire();


private:
    int x,y;

    QCheckBox *detectCheckBox;
    QCheckBox *trackCheckBox;
    QTimer *timer;
    QLabel *label;
    cv::Mat imgCam;
    cv::Mat image;
    cv::Mat hand;
    cv::VideoCapture *webcam;
    };

#endif // WEBCAMWINDOW_H
