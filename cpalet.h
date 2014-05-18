#ifndef CPALET_H
#define CPALET_H
#include <cobject.h>

class CPalet : public CObject
{
public:
    CPalet(int identifiant=0);
    ~CPalet();
    virtual int iGetNbFaces();
    virtual int iGetNbVertices(int _iFace);
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void vGetSideColor(int _face, CVector3* _poColor);
<<<<<<< HEAD
    virtual void getDeplacement(CVector3* _poDepla){}
    virtual void getScale(CVector3* _poScale);
    virtual bool detectionCollision(CVector3* _poPosBoule, int* i);
=======
>>>>>>> JM
};

#endif // CCUBE_H
