#ifndef CCUBE_H
#define CCUBE_H
#include <cobject.h>

class CCube : public CObject
{
public:
    CCube(int identifiant=0);
    ~CCube();
    virtual int iGetNbFaces();
    virtual int iGetNbVertices(int _iFace);
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void vGetSideColor(int _face, CVector3* _poColor);
    virtual void getDeplacement(CVector3* _poDepla){}
    virtual void getScale(CVector3* _poScale);
    virtual bool detectionCollision(CVector3* _poPosBoule, int* i);
};

#endif // CCUBE_H
