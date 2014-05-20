#include "cpalet.h"
#include <QDebug>

#include <rectangle.h>
#include <math.h>



static const int m_iNbFaces = 6;
static const int m_iNbVertices[] = {4,4,4,4,4,4};
static const int m_iFaces[6][4] = {
    { 0, 3, 2, 1 }, // front side
    { 1, 2, 6, 5 }, // right side
    { 0, 1, 5, 4 }, // top side
    { 0, 4, 7, 3 }, // left side
    { 3, 7, 6, 2 }, // bottom side
    { 4, 5, 6, 7 }, // rear side
};
static const float m_fVertices[8][3] = {
    { -0.5, 1, -0.18 }, // 0 front top left
    { 0.5, 1, -0.18  }, // 1 front top right
    { 0.5, -1, -0.18  }, // 2 front bottom right
    { -0.5, -1, -0.18 }, // 3 front bottom left
    { -0.5, 1, 0.18  }, // 4 rear top left
    { 0.5, 1, 0.18  }, // 5 rear top right
    { 0.5, -1, 0.18  }, // 6 rear bottom right
    { -0.5, -1, 0.18  } // 7 rear bottom left
};


CPalet::CPalet(int identifiant) : CObject(identifiant)
{
    scale->vSetX(1.0);
    scale->vSetY(2.0);
    scale->vSetZ(2.0);
}

CPalet::~CPalet()
{

}

//recuperation du nombre de face et du nombre de vertex d'une face

int CPalet::iGetNbFaces()
{
    return m_iNbFaces;
}

int CPalet::iGetNbVertices(int _iFace)
{
    return m_iNbVertices[_iFace];
}

//recuperation dans un vector donné des coodornnées spaciales d'un vertex donné

void CPalet::vGetVertex(int _iFace, int _iVertex, CVector3 *_poVect)
{
    int n=m_iFaces[_iFace][_iVertex];
    _poVect->vSetX(m_fVertices[n][0]);
    _poVect->vSetY(m_fVertices[n][1]);
    _poVect->vSetZ(m_fVertices[n][2]);
}

//attribution d'une couleur a une face

void CPalet::vGetSideColor(int _face, CVector3 *_poColor)
{
    switch(_face)
    {
    case 0:
        _poColor->vSetX(1.0);
        _poColor->vSetY(1.0);
        _poColor->vSetZ(0.0);
        break;
    case 1:
        _poColor->vSetX(1.0);
        _poColor->vSetY(0.0);
        _poColor->vSetZ(1.0);
        break;
    case 2:
        _poColor->vSetX(0.0);
        _poColor->vSetY(1.0);
        _poColor->vSetZ(1.0);
        break;
    case 3:
        _poColor->vSetX(0.6f);
        _poColor->vSetY(0.7f);
        _poColor->vSetZ(0.6f);
        break;
    case 4:
        _poColor->vSetX(1.0);
        _poColor->vSetY(0.0);
        _poColor->vSetZ(0.0);
        break;
    case 5:
    default:
        _poColor->vSetX(0.0);
        _poColor->vSetY(0.0);
        _poColor->vSetZ(1.0);
        break;
    }
}

void CPalet::getScale(CVector3 *_poScale)
{
   _poScale->vSetX(scale->fGetX());
   _poScale->vSetY(scale->fGetY());
   _poScale->vSetZ(scale->fGetZ());
}

bool CPalet::detectionCollision(CVector3 *_poPosBoule, int *i)
{
    CVector3 positionObjet;
    this->getPosition(&positionObjet);

    float ys=_poPosBoule->fGetY();
    float yc=positionObjet.fGetY();
    float zs=_poPosBoule->fGetZ();
    float zc=positionObjet.fGetZ();
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> origin/Thib
    float L=2*scale->fGetY()*0.4;
    float l=2*scale->fGetZ()*1.2;

    Rectangle rect(yc,zc,L+0.3,l+0.3);
    if (rect.contains(ys,zs))
    {
        if (fabs(ys-yc)<((l/2))) {
            *i=0;
        }
        else {
            *i=1;
        }
        return true;
    }
    return false;
<<<<<<< HEAD
=======
    float L=2.0*scale->fGetY()*0.4;
    float l=2.0*scale->fGetZ()*1.2;

    Rectangle rect(yc,zc-0.1,L,0.25);
    *i=0;
    return rect.contains(ys,zs);
>>>>>>> JM
=======
>>>>>>> origin/Thib
}
