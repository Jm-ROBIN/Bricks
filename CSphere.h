#ifndef CSPHERE_H
#define CSPHERE_H

#include "CObject.h"
#include <QVector>

static class  CSphere : public CObject
{
private:
    QVector<CVector3>   m_oVertices;
    QVector<CVector3>   m_oFaces;

    static int vitesse;

    void                vGenerateData(void);
    void                vComputeTriangle(float* v1, float *v2, float *v3, int n);
    void                vPousserProfondeur(float v[3]);

public:
    CSphere(int _id=0);
    ~CSphere();

    virtual int iGetNbFaces();
    virtual int iGetNbVertices(int _iFace);
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void vGetSideColor(int _face, CVector3* _poColor);
    virtual void getDeplacement(CVector3 *_poDepla);

    //virtual int         iIsPicked(CVector3* _poOrigin, CVector3* _poDir, CVector3* _poIntersection, int* _iPickedFace);
};

#endif // CSPHERE_H