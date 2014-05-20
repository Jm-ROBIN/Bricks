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
    oAddBtn =new QPushButton(tr("&Lancer"));
    oAddBtn->show();
    /*QPushButton *oDelBtn =new QPushButton(tr("&Del"));
    oDelBtn->show();*/

    stop=0;
    vie=3;
    niveau=1;
    demarrer=false;
    suivant = true;

    //la liste d'objets (ici cube) a afficher
    zoneTracage = new CGLArea();

    //tacking
    camTrack = new WebCamWindow(parent);

    EtatPartie.setText("          ");
    QString TexteVie = "Vie : " + QString::number(vie);
    NbVie.setText(TexteVie);
    QString TexteNiveau = "Niveau : " + QString::number(niveau);
    Niveau.setText(TexteNiveau);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(bougerPalet()));
    connect(timer, SIGNAL(timeout()), this, SLOT(fctTestStop()));
    timer->start(50);


    //mise en place des interactions boutons avec l'utilisateur
    connect(oAddBtn, SIGNAL(clicked()), this, SLOT(vStartFunction()));
    //connect(oDelBtn, SIGNAL(clicked()), this, SLOT(vDelFunction()));

    //placement dans la fenetre des differents elements graphiques
    QHBoxLayout* oBtnRLayout = new QHBoxLayout();
    oBtnRLayout->addWidget(oAddBtn, Qt::AlignTop);
    oBtnRLayout->addWidget(&Niveau);
    oBtnRLayout->addWidget(&NbVie);
    oBtnRLayout->addWidget(&EtatPartie);
    oBtnRLayout->addStretch();

    QVBoxLayout* oBtnVLayout = new QVBoxLayout();
    oBtnVLayout->addWidget(zoneTracage);
    oBtnVLayout->addLayout(oBtnRLayout);

    QHBoxLayout* oBtnHLayout = new QHBoxLayout();
    oBtnHLayout->addLayout(oBtnVLayout);
    oBtnHLayout->addWidget(camTrack);

    setLayout(oBtnHLayout);
    resize(900,500);
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

void CView::vStartFunction()
{
    if(vie ==3 || suivant==true)
    {
        for (int i = 0; i < 1; ++i) {
            controler->Add();
            // Mettre a jour la polist
            zoneTracage->updateGL();
        }
        demarrer=true;
        model->demarer();
        EtatPartie.setText("          ");
        suivant=false;
    }
    else
    {
        demarrer=true;
        model->demarer();
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
        QString TexteVie = "Vie : " + QString::number(vie);
        NbVie.setText(TexteVie);
        oAddBtn->setText("Lancer");
        demarrer=false;
        stop=0;
    }
    else {
        if (stop==2)
        {
            model->reinitialiser();
            EtatPartie.setText("Gagner !  ");
            oAddBtn->setText("Niveau suivant");
            suivant = true;
            demarrer=false;
            niveau=niveau+1;
            QString TexteNiveau = "Niveau : " + QString::number(niveau);
            Niveau.setText(TexteNiveau);
            stop=0;
        }
        if(vie==0)
        {
            model->reinitialiser();
            EtatPartie.setText("Perdu !   ");
            demarrer=false;
            stop=0;
            vie=3;
            QString TexteVie = "Vie : " + QString::number(vie);
            NbVie.setText(TexteVie);
            oAddBtn->setText("Nouvelle partie");
            niveau=1;
            QString TexteNiveau = "Niveau : " + QString::number(niveau);
            Niveau.setText(TexteNiveau);
            for (int i = 0; i < 30; ++i) {
                controler->Del();
                // Mettre a jour la polist
                zoneTracage->updateGL();
            }
        }
    }
}


void CView::bougerPalet()
{
    int x = camTrack->getX();
    //int y =camTrack->getY();
    zoneTracage->mouvementPalet(x);
}
