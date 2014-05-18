#include "cobject.h"

CObject::CObject(int i)
{
    identifiant=i;
    position=new CVector3;
    scale=new CVector3;
}

CObject::~CObject()
{

}

int CObject::getIdentifiant()
{
    return identifiant;
}

void CObject::setIdentifiant(int i)
{
    identifiant=i;
}

void CObject::getPosition(CVector3 *_c)
{
    _c->vSetX(position->fGetX());
    _c->vSetY(position->fGetY());
    _c->vSetZ(position->fGetZ());
}

void CObject::setPosition(CVector3 *Position)
{
    position->vSetX(Position->fGetX());
    position->vSetY(Position->fGetY());
    position->vSetZ(Position->fGetZ());
}
