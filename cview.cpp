#include "cview.h"
#include<QPushButton>
#include<QVBoxLayout>
#include "cobject.h"
#include <QTimer>


//ajout des elements graphiques a la fenetre
CView::CView(QWidget *parent)
    : QWidget(parent)
{
    //les boutons
<<<<<<< HEAD
    QPushButton *oAddBtn =new QPushButton(tr("&Add"));
    oAddBtn->show();
    QPushButton *oDelBtn =new QPushButton(tr("&Del"));
    oDelBtn->show();
=======
    QPushButton *oAddBtn =new QPushButton(tr("&Start"));
    oAddBtn->show();
    /*QPushButton *oDelBtn =new QPushButton(tr("&Del"));
    oDelBtn->show();*/

    stop=0;
    vie=3;
    demarrer=false;
>>>>>>> origin/Thib

    //la liste d'objets (ici cube) a afficher
    zoneTracage = new CGLArea();

    //tacking
<<<<<<< HEAD
    //camTrack = new WebCamWindow(parent);
    //camTrack->show();

    QTimer *timerPalet = new QTimer(this);
    connect(timerPalet, SIGNAL(timeout()), this, SLOT(bougerPalet()));
    timerPalet->start(5);

    //mise en place des interactions boutons avec l'utilisateur
    connect(oAddBtn, SIGNAL(clicked()), this, SLOT(vAddFunction()));
    connect(oDelBtn, SIGNAL(clicked()), this, SLOT(vDelFunction()));
=======
    camTrack = new WebCamWindow(parent);
    camTrack->show();

    EtatPartie.setText("          ");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(bougerPalet()));
    connect(timer, SIGNAL(timeout()), this, SLOT(fctTestStop()));
    timer->start(10);


    //mise en place des interactions boutons avec l'utilisateur
    connect(oAddBtn, SIGNAL(clicked()), this, SLOT(vStartFunction()));
    //connect(oDelBtn, SIGNAL(clicked()), this, SLOT(vDelFunction()));
>>>>>>> origin/Thib

    //placement dans la fenetre des differents elements graphiques
    QHBoxLayout* oBtnRLayout = new QHBoxLayout();
    oBtnRLayout->addWidget(oAddBtn, Qt::AlignTop);
<<<<<<< HEAD
    oBtnRLayout->addWidget(oDelBtn);
=======
    oBtnRLayout->addWidget(&EtatPartie);
>>>>>>> origin/Thib
    oBtnRLayout->addStretch();

    QVBoxLayout* oBtnVLayout = new QVBoxLayout();
    oBtnVLayout->addWidget(zoneTracage);
    oBtnVLayout->addLayout(oBtnRLayout);

    setLayout(oBtnVLayout);
<<<<<<< HEAD
    setWindowTitle(tr("Bricks"));
=======
    setWindowTitle(tr("Casse Brique"));
>>>>>>> origin/Thib
}

CView::~CView()
{

}

void CView::setModel(CModel *mod)
{
    model=mod;
    zoneTracage->vSetModel(mod);
}

<<<<<<< HEAD
void CView::vAddFunction()
{
    // Dire au controleur d'ajouter un element
    for (int i = 0; i < 15; ++i) {
        controler->Add();
        // Mettre a jour la polist
        zoneTracage->updateGL();
    }
}

=======
void CView::vStartFunction()
{
    if(vie ==3)
    {
        for (int i = 0; i < 1; ++i) {
            controler->Add();
            // Mettre a jour la polist
            zoneTracage->updateGL();
        }
        demarrer=true;
        zoneTracage->demarrer();
        EtatPartie.setText("          ");
    }
    else
    {
        demarrer=true;
        zoneTracage->demarrer();
        EtatPartie.setText("          ");
    }
}

void CView::fctTestStop()
{
    if(demarrer==true)
    {
    stop=  controler->onStop();
    }

    if(stop==1)
    {
        model->reinitialiser();
        vie=vie-1;
        qDebug()<<vie;
        /*demarrer=false;
        stop=0;*/
    }
    else {
        if (stop==2)
        {
            model->reinitialiser();
            EtatPartie.setText("Gagner !  ");
            /*demarrer=false;
            stop=0;*/
        }
        if(vie==0)
        {
            model->reinitialiser();
            EtatPartie.setText("Perdu !   ");
            /*demarrer=false;
            stop=0;*/
        }
    }
}


>>>>>>> origin/Thib
void CView::vDelFunction()
{
    if (model->getNbTableau()!=0)
    {
        // Dire au controleur de supprimer un element
<<<<<<< HEAD
        for (int i = 0; i < 30; ++i) {
=======
        for (int i = 0; i < 2; ++i) {
>>>>>>> origin/Thib
            controler->Del();
            // Mettre a jour la polist
            zoneTracage->updateGL();
        }
    }
}

void CView::bougerPalet()
{
    int x = camTrack->getX();
    //int y =camTrack->getY();
    zoneTracage->mouvementPalet(x);
}
