#ifndef CVIEW_H
#define CVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include "ccontroler.h"
#include "cmodel.h"
#include "ccube.h"
#include "cglarea.h"
#include "webcamwindow.h"

class CView : public QWidget
{
    Q_OBJECT

    CControler* controler;
    CModel* model;
    CGLArea *zoneTracage;

    WebCamWindow * camTrack;

public:
    CView(QWidget *parent = 0);
    ~CView();
    void setControl(CControler* ctrl) {controler=ctrl;}
    void setModel(CModel* mod);
    CGLArea* getArea() {return zoneTracage;}

public slots :
    void vAddFunction();
    void vDelFunction();
    void bougerPalet();
};

#endif // CVIEW_H
