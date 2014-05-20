#ifndef CCONTROLER_H
#define CCONTROLER_H

#include "cmodel.h"
#include "cglarea.h"

class CControler
{
    CModel* model;
    CGLArea* area;
public:
    CControler(CModel* mod);
    ~CControler();
    void cglMaj(CGLArea* are);
    void Add();
    void Del();
    int onStop();
};

#endif // CCONTROLER_H
