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
};

#endif // CCUBE_H
