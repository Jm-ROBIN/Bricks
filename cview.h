#ifndef CVIEW_H
#define CVIEW_H

#include <QWidget>
#include<QListWidget>
#include "ccontroler.h"
#include "cmodel.h"
#include "ccube.h"
#include "cglarea.h"
#include "webcamwindow.h"
#include <QSound>
#include <QApplication>

class CView : public QWidget
{
    Q_OBJECT

    CControler* controler;
    CModel* model;
    CGLArea *zoneTracage;
    WebCamWindow * camTrack;
    QPushButton *oAddBtn;
    QLabel EtatPartie;
    QLabel NbVie;
    QLabel Niveau;
    int stop;
    int vie;
    int niveau;
    bool demarrer;
    bool suivant;
public:
    CView(QWidget *parent = 0);
    ~CView();
    void setControl(CControler* ctrl) {controler=ctrl;}
    void setModel(CModel* mod);
    CGLArea* getArea() {return zoneTracage;}

public slots :
    void vStartFunction();
    void bougerPalet();
    void fctTestStop();
};

#endif // CVIEW_H
