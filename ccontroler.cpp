#include "ccontroler.h"

CControler::CControler(CModel* mod)
{
    model=mod;
}

CControler::~CControler()
{

}

//appel de la fonction d'ajout d'objet du model
void CControler::Add()
{
    model->AddItem();
}

void CControler::Del()
{
    model->DelItem();
}
