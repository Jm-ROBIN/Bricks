#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "webcamwindow.h"

using namespace cv;

WebCamWindow::WebCamWindow(QWidget *parent)
    : QWidget(parent)
{
    webCamButton = new QPushButton(tr("Demarrer aquisition"));
    label = new QLabel(tr("Image"));
    detectCheckBox = new QCheckBox(tr("Detection initiale"));
    trackCheckBox= new QCheckBox(tr("Tracking"));
    
    connect(webCamButton, SIGNAL(clicked()), this, SLOT(startWebCam()));

    x=125;
    y=0;
    
    QVBoxLayout *vl1=new QVBoxLayout;
    vl1->addWidget(detectCheckBox);
    vl1->addWidget(trackCheckBox);
    QHBoxLayout *hl=new QHBoxLayout;
    hl->addWidget(webCamButton);
    hl->addLayout(vl1);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addLayout(hl);
    
    setLayout(layout);
    setWindowTitle(tr("Track WebCam"));
    
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(aquire()));
    
}

WebCamWindow::~WebCamWindow()
{
    delete webcam;
}

void WebCamWindow::displayImage(QLabel *_destination)
{
    if (image.data!=NULL)
    {
        cv::flip(image,image,1); // process the image
        // change color channel ordering
        cv::cvtColor(image,image,CV_BGR2RGB);
        // Qt image
        QImage img= QImage((const unsigned char*)(image.data),
                           image.cols,image.rows,QImage::Format_RGB888);
        // display on label
        _destination->setPixmap(QPixmap::fromImage(img));
        // resize the label to fit the image
        _destination->resize(label->pixmap()->size());
    }
    else QMessageBox(QMessageBox::Critical,tr("Error"),tr("Image is void")).exec();
}


void WebCamWindow::aquire()
{
    *webcam >> imgCam;
    ::resize(imgCam,image,Size(),1,1,CV_INTER_AREA);
    if (detectCheckBox->isChecked() && !trackCheckBox->isChecked()) detectHand();
    if (trackCheckBox->isChecked())
    {
        trackHand();
    }
    displayImage(label);
}

void WebCamWindow::startWebCam()
{
    if (!timer->isActive())
    {
        webcam= new cv::VideoCapture(0);
        timer->start(50);
        webcam->set(CV_CAP_PROP_FRAME_WIDTH,320);
        webcam->set(CV_CAP_PROP_FRAME_HEIGHT,240);
        qDebug()<<"W : "<<webcam->get(CV_CAP_PROP_FRAME_WIDTH);
        qDebug()<<"H : "<<webcam->get(CV_CAP_PROP_FRAME_HEIGHT);
        webCamButton->setText(tr("Arreter aquisition"));
        
    }
    else
    {
        timer->stop();
        delete webcam;
        webcam=0;
        webCamButton->setText(tr("Demarrer aquisition"));
    }
}

void WebCamWindow::detectHand(int _x, int _y)
{
    cv::Rect rectRoi(_x,_y,75,50);
    rectangle(image,rectRoi,Scalar( 0, 255, 0),2,8,0);
    Mat handC (image, rectRoi );

    x=_x;
    y=_y;
    
    namedWindow("Display",WINDOW_AUTOSIZE);
    cv::flip(handC,hand,1);
    imshow("Display",hand);
    
}

void WebCamWindow::trackHand()
{
    // X positif vers la gauche de l'image
    // Y positif vers le bas de l'image

    /// Source image to display
    Mat result;
    Mat img_display;
    Mat imagePart;
    int match_method = CV_TM_SQDIFF ;
    imagePart = image(Rect(0, 140,320,100));

    namedWindow("Part",WINDOW_AUTOSIZE);
    imshow("Part",imagePart);

    /// Create the result matrix
    int result_cols =  imagePart.cols - hand.cols + 1;
    int result_rows = imagePart.rows - hand.rows + 1;

    result.create( result_cols, result_rows, CV_32FC1 );

    /// Do the Matching and Normalize
    matchTemplate( imagePart, hand, result, match_method);
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
    else
    { matchLoc = maxLoc; }


    /// Show me what you got
    rectangle(image, Point(matchLoc.x,matchLoc.y+140), Point( matchLoc.x + hand.cols , matchLoc.y + hand.rows+140), Scalar::all(0), 2, 8, 0 );

    x = matchLoc.x;
    y = matchLoc.y+140;

    detectHand(x,y);

    return;
}
