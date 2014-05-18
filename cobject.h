#ifndef COBJECT_H
#define COBJECT_H
#include <CVector3.h>

class CObject
{
    int identifiant;
    CVector3* position;
public:

    CVector3* scale;
    CObject(int i);
    ~CObject();
    int getIdentifiant();
    void setIdentifiant(int i);
    void getPosition(CVector3* _c);
    void setPosition(CVector3 *Position);
    virtual int iGetNbFaces() = 0;
    virtual int iGetNbVertices(int _iFace) = 0;
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect) = 0;
    virtual void vGetSideColor(int _face, CVector3* _poColor) = 0;
    virtual void getDeplacement(CVector3* _poDepla) = 0;
    virtual void getScale(CVector3* _poScale)=0;
    virtual bool detectionCollision(CVector3* _poPosBoule, int* i)=0;
};

#endif // COBJECT_H
