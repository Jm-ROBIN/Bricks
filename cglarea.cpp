#include "cglarea.h"
#include <QDebug>
#include <cmath>
#include <glu.h>
#include <QMouseEvent>
#include <CSphere.h>
#include <QTimer>
#include <QVector>

bool swich = false;

CGLArea::CGLArea(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    //coordonees spheriques servant a placer la camera observatrice
    m_radius=-13;
    m_elevation=0;
    m_azimuth=0;
    avantDepla=0;

    //sert pour le mouvement de la boule
    QTimer *timerMvt = new QTimer(this);
    connect(timerMvt, SIGNAL(timeout()), this, SLOT(mouvementBoule()));
    timerMvt->start(50);
}
CGLArea::~CGLArea()
{
}

//recuperation du model

void CGLArea::vSetModel(CModel *_poModel)
{
    m_poModel=_poModel;
    palet= m_poModel->getPalet();
    boule= m_poModel->getBoule();
}

//mise en place de fonction de taille et d'initialisation de la zone de tracage

QSize CGLArea::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CGLArea::sizeHint() const
{
    return QSize(400, 400);
}

void CGLArea::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    updateCamera();
    /*glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);*/

}

void CGLArea::initializeGL()
{
    updateCamera();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

//fonction qui va tracer les cube et les placer

void CGLArea::paintGL()
{
    //on clear la zone a chaque ajout de cube
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    afficherBords();
    afficherBoule();
    afficherPalet();
    AfficherCubes();
}

//placement de la camera
void CGLArea::updateCamera(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-m_radius, m_radius, -m_radius, m_radius, 0.0, 30);
    gluLookAt(m_radius*cos(m_azimuth)*cos(m_elevation),
              m_radius*sin(m_azimuth)*cos(m_elevation),
              m_radius*sin(m_elevation),
              0,0,0,
              0,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Mise en place des reactions avec la souris
void CGLArea::mousePressEvent(QMouseEvent *event)
{
    //recuperation de la position courante de la souris
    lastPos = event->pos();


    updateCamera();
    updateGL();
}

void CGLArea::mouseMoveEvent(QMouseEvent *event)
{
    //determination du petit mouvement de souris
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    //transcription des mouvements de la souris a ceux de la camera autour de l'objet
    if (event->buttons() & Qt::LeftButton) {

        m_elevation-=0.01*dy;
        m_azimuth-=0.01*dx;
        if(m_elevation<=-1.57)
        {
            m_elevation=-1.57;
        }
        if(m_elevation>=1.57)
        {
            m_elevation=1.57;
        }
    } else if (event->buttons() & Qt::RightButton) {
    }

    lastPos = event->pos();

    updateCamera();
    updateGL();
}

void CGLArea::wheelEvent ( QWheelEvent * event )
{
    m_radius+=(event->delta()/120);

    updateCamera();
    updateGL();
}

void CGLArea::mouseReleaseEvent(QMouseEvent *event)
{

}

int CGLArea::onDoitStopper()
{
    if(m_poModel->balleEnBas())
        return 1;
    else{
        if(m_poModel->plusDeBrique())
        {
            return 2;
        }
        else {
            return 0;
        }
    }
}

void CGLArea::mouvementBoule()
{
    CVector3 PositionActuelle(0,0,0);
    CVector3 NextPosition(0,0,0);
    boule->getPosition(&PositionActuelle);
    boule->vGetNextPosition(&NextPosition);

    int var = 0;
    int sensCollision = -1;
    bool collision = false;
    while ((collision == false) && (var < m_poModel->getNbTableau()))
    {
        CObject* currentCube = m_poModel->getTableauobject(var);
        collision = currentCube->detectionCollision(&NextPosition,&sensCollision);
        var++;
    }
    if (collision) {
        boule->vRebondir(sensCollision);
        m_poModel->detruireCube(var-1);
        updateGL();
    }
    boule->vGetNextPosition(&NextPosition);

    sensCollision = -1;
    if (palet->detectionCollision(&NextPosition,&sensCollision))
    {
        boule->vRebondir(sensCollision);
    }

    else{
        if (palet->detectionCollision(&NextPosition,&sensCollision))
        {
            CVector3 posPalet;
            palet->getPosition(&posPalet);
            float fEcart = posPalet.fGetY() - NextPosition.fGetY();
            float fAngle = (120.0/8.0)*fabs(fEcart);
            if (fEcart<0){
                boule->vSetVecteurVitesse(fAngle);
            }
            else {
                boule->vSetVecteurVitesse(-fAngle);
            }
        }
    }
    boule->vGetNextPosition(&NextPosition);

    if (NextPosition.fGetY()<-10.666666666)
        boule->vRebondir(1);
    if (NextPosition.fGetY()>10.666666666)
        boule->vRebondir(1);
    if (NextPosition.fGetZ()<-10.666666666)
        boule->vRebondir(0);
    if (NextPosition.fGetZ()>10.666666666)
        boule->vRebondir(0);

    boule->setPosition(&NextPosition);
    boule->getPosition(&PositionActuelle);
    updateGL();

}

void CGLArea::mouvementPalet(int x)
{
    int dx = 1.2*(-((x-125)/13.8)) - lastPosBoule.x();


    CVector3 _poPositionAvant;
    palet->getPosition(&_poPositionAvant);
    float deplacement = 0.1*dx + _poPositionAvant.fGetY();

    if (deplacement<9.5 && deplacement>-9.5){
        CVector3 _poPositionMove(2,deplacement,9);
        palet->setPosition(&_poPositionMove);
    }

    lastPosBoule.setX( (int)deplacement);

    updateCamera();
    updateGL();
}

void CGLArea::afficherBoule()
{
    CVector3 _poPosition2;
    CVector3 _poColor2;
    boule->getPosition(&_poPosition2);
    glLoadIdentity ();
    glTranslatef (_poPosition2.fGetX(),_poPosition2.fGetY(),_poPosition2.fGetZ());
    CVector3 _poScale;
    boule->getScale(&_poScale);
    glScalef (_poScale.fGetX(),_poScale.fGetY(),_poScale.fGetZ());
    for(int j=0;j<boule->iGetNbFaces();j++)
    {
        //par parcours de chaque face on trace chaque cube en allant chercher les coordonnées des vertex des cette face ainsi que sa couleur
        boule->vGetSideColor(j,&_poColor2);
        glColor3f(_poColor2.fGetX(),_poColor2.fGetY(),_poColor2.fGetZ());
        glBegin(GL_POLYGON);
        int n=boule->iGetNbVertices(j);

        for(int k=0;k<n;k++)
        {
            CVector3 _oVertex;
            boule->vGetVertex(j,k,&_oVertex);
            glVertex3f(_oVertex.fGetX(), _oVertex.fGetY(),_oVertex.fGetZ());
        }
        glEnd();
    }
    glFlush();
}


void CGLArea::afficherPalet()
{
    CVector3 _poPosition3;
    CVector3 _poColor3;
    palet->getPosition(&_poPosition3);
    glLoadIdentity ();
    glTranslatef (_poPosition3.fGetX(),_poPosition3.fGetY(),_poPosition3.fGetZ());

    CVector3 _poScale;
    palet->getScale(&_poScale);
    glScalef (_poScale.fGetX(),_poScale.fGetY(),_poScale.fGetZ());
    for(int j=0;j<palet->iGetNbFaces();j++)
    {
        //par parcours de chaque face on trace chaque cube en allant chercher les coordonnées des vertex des cette face ainsi que sa couleur
        palet->vGetSideColor(j,&_poColor3);
        glColor3f(_poColor3.fGetX(),_poColor3.fGetY(),_poColor3.fGetZ());
        glBegin(GL_POLYGON);
        int n=palet->iGetNbVertices(j);

        for(int k=0;k<n;k++)
        {
            CVector3 _oVertex;
            palet->vGetVertex(j,k,&_oVertex);
            glVertex3f(_oVertex.fGetX(), _oVertex.fGetY(),_oVertex.fGetZ());
        }
        glEnd();
    }
    glFlush();
}

void CGLArea::AfficherCubes()
{
    for(int i=0;i<m_poModel->getNbTableau();i++)
    {
        CVector3 _poPosition;
        CVector3 _poColor;

        //recuperation de la position du cube definie à son initialisation et placement de celui par rapport a cette position
        CObject* current=m_poModel->getTableauobject(i);
        current->getPosition(&_poPosition);

        bool deja=false;

        CVector3 _poColorVerif(0.5f,0.3f,0.6f);

        for (int k = 0; k < i-1; ++k) {
            CObject* Verif=m_poModel->getTableauobject(k);
            CVector3 _poPositionVerif;
            Verif->getPosition(&_poPositionVerif);
            if (_poPosition.fGetY()==_poPositionVerif.fGetY() && _poPosition.fGetZ()==_poPositionVerif.fGetZ())
            {

                _poColorVerif.vSetX(_poColorVerif.fGetX()+0.2f);
                _poColorVerif.vSetY(_poColorVerif.fGetY()-0.1f);
                _poColorVerif.vSetZ(_poColorVerif.fGetZ()-0.2f);

                _poPosition.vSetX(_poPosition.fGetX()-1);
                deja=true;
            }
        }

        glLoadIdentity ();
        glTranslatef (_poPosition.fGetX(),_poPosition.fGetY(),_poPosition.fGetZ());
        //rotation predefinie
        //glRotatef(120*i, 1.0, 1.0, 0.0);

        CVector3 _poScale;
        current->getScale(&_poScale);
        glScalef (_poScale.fGetX(),_poScale.fGetY(),_poScale.fGetZ());


        for(int j=0;j<current->iGetNbFaces();j++)
        {
            //par parcours de chaque face on trace chaque cube en allant chercher les coordonnées des vertex des cette face ainsi que sa couleur
            if (deja==false)
            {
                current->vGetSideColor(j,&_poColor);
                glColor3f(_poColor.fGetX(),_poColor.fGetY(),_poColor.fGetZ());
            }
            else
            {
                glColor3f(_poColorVerif.fGetX(),_poColorVerif.fGetY(),_poColorVerif.fGetZ());
            }
            glBegin(GL_POLYGON);
            int n=current->iGetNbVertices(j);
            for(int k=0;k<n;k++)
            {
                CVector3 _oVertex;
                current->vGetVertex(j,k,&_oVertex);
                glVertex3f(_oVertex.fGetX(), _oVertex.fGetY(),_oVertex.fGetZ());
            }
            glEnd();
        }
        glFlush();

    }
}

void CGLArea::afficherBords()
{
    for(int i=0;i<m_poModel->getNbBords();i++)
    {
        CVector3 _poPosition;
        CVector3 _poColor;

        //recuperation de la position du cube definie à son initialisation et placement de celui par rapport a cette position
        CBord* current=m_poModel->getBordsobject(i);
        current->getPosition(&_poPosition);


        glLoadIdentity ();
        glTranslatef (_poPosition.fGetX(),_poPosition.fGetY(),_poPosition.fGetZ());
        CVector3 _poScale;
        current->getScale(&_poScale);
        if (i==1 || i ==2)
            glScalef (_poScale.fGetX(),_poScale.fGetZ(),_poScale.fGetY());
        else
            glScalef (_poScale.fGetX(),_poScale.fGetY(),_poScale.fGetZ());



        for(int j=0;j<current->iGetNbFaces();j++)
        {
            //par parcours de chaque face on trace chaque cube en allant chercher les coordonnées des vertex des cette face ainsi que sa couleur

            current->vGetSideColor(j,&_poColor);
            glColor3f(_poColor.fGetX(),_poColor.fGetY(),_poColor.fGetZ());
            glBegin(GL_POLYGON);
            int n=current->iGetNbVertices(j);
            for(int k=0;k<n;k++)
            {
                CVector3 _oVertex;
                if (i==1 || i==2)
                {
                    current->vGetVertexAlt(j,k,&_oVertex);
                }
                else
                {
                    current->vGetVertex(j,k,&_oVertex);
                }
                glVertex3f(_oVertex.fGetX(), _oVertex.fGetY(),_oVertex.fGetZ());
            }
            glEnd();
        }
        glFlush();

    }
}
