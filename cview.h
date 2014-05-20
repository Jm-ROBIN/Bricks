#ifndef CVIEW_H
#define CVIEW_H

#include <QWidget>
<<<<<<< HEAD
#include <QListWidget>
#include <QLabel>
=======
#include<QListWidget>
>>>>>>> origin/Thib
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
<<<<<<< HEAD

    WebCamWindow * camTrack;

=======
    WebCamWindow * camTrack;
    QLabel EtatPartie;
    int stop;
    int vie;
    bool demarrer;
>>>>>>> origin/Thib
public:
    CView(QWidget *parent = 0);
    ~CView();
    void setControl(CControler* ctrl) {controler=ctrl;}
    void setModel(CModel* mod);
    CGLArea* getArea() {return zoneTracage;}

<<<<<<< HEAD
public slots :
    void vAddFunction();
    void vDelFunction();
    void bougerPalet();
=======
    void vDelFunction();

public slots :
    void vStartFunction();
    void bougerPalet();
    void fctTestStop();
>>>>>>> origin/Thib
};

#endif // CVIEW_H
