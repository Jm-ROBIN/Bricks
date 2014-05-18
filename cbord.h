#ifndef CBORD_H
#define CBORD_H
#include <cobject.h>
#include <csphere.h>

class CBord : public CObject
{
public:
    CBord(int identifiant=0);
    ~CBord();
    virtual int iGetNbFaces();
    virtual int iGetNbVertices(int _iFace);
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void vGetSideColor(int _face, CVector3* _poColor);
    void vGetVertexAlt(int _iFace, int _iVertex, CVector3 *_poVect);

    bool detectionCollision(CSphere* boule);
};

#endif // CCUBE_H
