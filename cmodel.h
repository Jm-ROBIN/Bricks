#ifndef CMODEL_H
#define CMODEL_H

#include<QVector>
#include "CObject.h"
#include <ccube.h>
#include <CSphere.h>
#include <cpalet.h>
#include <cbord.h>

class CModel
{
    QVector<CObject*> tableau;
    CSphere* boule;
    CPalet* palet;
    QVector<CBord*> bords;

public:
    CModel();
    ~CModel();
    void AddItem();
    void DelItem();
    CObject* getTableauobject(int i);
    int getNbTableau();
    float fGetRandom();
    float fGetRandomZ();
    CSphere* getBoule() {return boule;}
    CPalet* getPalet() {return palet;}
    CBord* getBordsobject(int i);
    int getNbBords();

    void detruireCube(int var);
};

#endif // CMODEL_H
