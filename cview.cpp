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
    QPushButton *oAddBtn =new QPushButton(tr("&Add"));
    oAddBtn->show();
    QPushButton *oDelBtn =new QPushButton(tr("&Del"));
    oDelBtn->show();

    //la liste d'objets (ici cube) a afficher
    zoneTracage = new CGLArea();

    //tacking
    //camTrack = new WebCamWindow(parent);
    //camTrack->show();

    QTimer *timerPalet = new QTimer(this);
    connect(timerPalet, SIGNAL(timeout()), this, SLOT(bougerPalet()));
    timerPalet->start(5);

    //mise en place des interactions boutons avec l'utilisateur
    connect(oAddBtn, SIGNAL(clicked()), this, SLOT(vAddFunction()));
    connect(oDelBtn, SIGNAL(clicked()), this, SLOT(vDelFunction()));

    //placement dans la fenetre des differents elements graphiques
    QHBoxLayout* oBtnRLayout = new QHBoxLayout();
    oBtnRLayout->addWidget(oAddBtn, Qt::AlignTop);
    oBtnRLayout->addWidget(oDelBtn);
    oBtnRLayout->addStretch();

    QVBoxLayout* oBtnVLayout = new QVBoxLayout();
    oBtnVLayout->addWidget(zoneTracage);
    oBtnVLayout->addLayout(oBtnRLayout);

    setLayout(oBtnVLayout);
    setWindowTitle(tr("Bricks"));
}

CView::~CView()
{

}

void CView::setModel(CModel *mod)
{
    model=mod;
    zoneTracage->vSetModel(mod);
}

void CView::vAddFunction()
{
    // Dire au controleur d'ajouter un element
    for (int i = 0; i < 15; ++i) {
        controler->Add();
        // Mettre a jour la polist
        zoneTracage->updateGL();
    }
}

void CView::vDelFunction()
{
    if (model->getNbTableau()!=0)
    {
        // Dire au controleur de supprimer un element
        for (int i = 0; i < 30; ++i) {
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
