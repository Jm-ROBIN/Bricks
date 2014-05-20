#ifndef CSPHERE_H
#define CSPHERE_H

#include "CObject.h"
#include <QVector>


class CSphere : public CObject
{
private:
    QVector<CVector3>   m_oVertices;
    QVector<CVector3>   m_oFaces;
    int iVitesse;
    CVector3 vecteurVitesse;

    void vGenerateData(void);
    void vComputeTriangle(float* v1, float *v2, float *v3, int n);
    void vPousserProfondeur(float v[3]);

public:

    CSphere(int _id=0);
    ~CSphere();

    virtual int iGetNbFaces();
    virtual int iGetNbVertices(int _iFace);
    virtual void vGetVertex(int _iFace, int _iVertex, CVector3* _poVect);
    virtual void vGetSideColor(int _face, CVector3* _poColor);
    virtual void getScale(CVector3* _poScale);
    virtual bool detectionCollision(CVector3* _poPosBoule, int* i) {}
    int iGetVitesse() {return iVitesse;}
    void vGetVecteurVitesse(CVector3 *_poVitesse);
    void vGetNextPosition(CVector3 *_poPosition);
    void vSetVitesse(float _fAngle);
    void vRebondir(int _Face);
};

#endif // CSPHERE_H
