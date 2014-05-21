#include "cview.h"
#include<QPushButton>
#include<QVBoxLayout>
#include "cobject.h"
#include <QTimer>


//ajout des elements graphiques a la fenetre
CView::CView(QWidget *parent)
    : QWidget(parent)
{
    //Bouton de lancement de la boule
    oAddBtn =new QPushButton(tr("&Lancer"));
    oAddBtn->show();

    //Variable de gestion du jeu
    stop=0;
    vie=3;
    niveau=1;
    demarrer=false;
    suivant = true;

    //la liste d'objets graphique a afficher
    zoneTracage = new CGLArea();

    //tacking
    camTrack = new WebCamWindow(parent);

    //affichage des infos de jeu
    EtatPartie.setText("          ");
    QString TexteVie = "Vie : " + QString::number(vie);
    NbVie.setText(TexteVie);
    QString TexteNiveau = "Niveau : " + QString::number(niveau);
    Niveau.setText(TexteNiveau);

    //timer gerant la gestion du jeu et le mouvement du palet
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(bougerPalet()));
    connect(timer, SIGNAL(timeout()), this, SLOT(fctTestStop()));
    timer->start(50);

    //mise en place des interactions bouton avec l'utilisateur
    connect(oAddBtn, SIGNAL(clicked()), this, SLOT(vStartFunction()));

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

//lors de l'appuie sur le bouton lance la boule et si c'est une nouvelle partie, ajoute aussi les cubes
//les cubes sont placés aleatoirement et la boule est lance verticalement
void CView::vStartFunction()
{
    if(vie ==3 || suivant==true)
    {
        for (int i = 0; i < 15; ++i) {
            controler->Add();
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

//Fonction qui test en temps reelle s'il faut stopper le mouvement de la boule
//verifie de plus ce qu'il faut afficher a l'utilisateur lors des differentes phases de jeu
void CView::fctTestStop()
{
    if(demarrer==true)
    {
    stop=  controler->onStop();
    }

    //si touche le fond, on enleve une vie, et on continue la partie
    //on replace la boule au centre
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
        //si tout les cubes sont cassés on passe au niveau suivant tout en gardant le meme nombre de vie
        //on replace la boule au centre
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
        //si plus de vie, marque que le jeu est perdu, remet le nombre de vie a 3,
        //et supprime les briques restantes
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
                zoneTracage->updateGL();
            }
        }
    }
}


//Fonction qui recupere la position de la main dans la camera
//et transmet ce mouvement au palet
void CView::bougerPalet()
{
    int x = camTrack->getX();
    zoneTracage->mouvementPalet(x);
}

