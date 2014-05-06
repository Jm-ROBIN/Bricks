#ifndef CCONTROLER_H
#define CCONTROLER_H

#include "cmodel.h"

class CControler
{
    CModel* model;
public:
    CControler(CModel* mod);
    ~CControler();
    void Add();
    void Del();
};

#endif // CCONTROLER_H
