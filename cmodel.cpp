#include "cmodel.h"
#include<QDebug>

CModel::CModel()
{
    //initialisation des differents objet graphique contenu dans le modele
    boule=new CSphere(0);
    CVector3 postion(2,0,8);
    boule->setPosition(&postion);
    palet=new CPalet(0);
    CVector3 position(2,0,9);
    palet->setPosition(&position);

    CVector3 positionCubeD(2,11.5,0);
    CBord* coteDroit= new CBord(0);
    coteDroit->setPosition(&positionCubeD);
    CVector3 positionCubeG(2,-11.5,0);
    CBord* coteGauche= new CBord(0);
    coteGauche->setPosition(&positionCubeG);
    CVector3 positionCubeH(2,0,-11.5);
    CBord* coteHaut= new CBord(0);
    coteHaut->setPosition(&positionCubeH);
    CVector3 positionCubeB(2,0,11.5);
    CBord *coteBas= new CBord(0);
    coteBas->setPosition(&positionCubeB);

    bords.push_back(coteHaut);
    bords.push_back(coteGauche);
    bords.push_back(coteDroit);
    bords.push_back(coteBas);
}


CModel::~CModel()
{

}

//ajout/destruction d'un element dans le tableau, celui-ci servira a remplir la liste a afficher a l'ecran
void CModel::AddItem()
{
    CObject *nouveau= new CCube(tableau.size());
    //a chaque objet on cree son simetrique par rapport a Z
    CObject *nouveau2= new CCube(tableau.size());
    //attribution d'une position aleatoire
    float Y=fGetRandom();
    float Z=fGetRandomZ();
    CVector3 postion(2,Y,Z-6);
    CVector3 postion2(2,Y,-Z-4.666666);
    nouveau->setPosition(&postion);
    tableau.append(nouveau);
    nouveau2->setPosition(&postion2);
    tableau.append(nouveau2);
}

void CModel::DelItem()
{
    //on verifie la taille afin de ne pas avoir une erreur losqu'on veut delete et qu'il n'y a pas d'element
    if (tableau.size()!=0)
    {
        //destruction du cObject
        CObject* last=tableau.last();
        tableau.pop_back();
    }
}

//obtention du tableau/d'un elementdu tableau
CObject* CModel::getTableauobject(int i)
{
    return tableau[i];
}

//retourne le nombre d'objet dans le tableau
int CModel::getNbTableau()
{
    return tableau.size();
}

//recupere un objet bord
CBord* CModel::getBordsobject(int i)
{
    return bords[i];
}

int CModel::getNbBords()
{
    return bords.size();
}

//fonction renvoyant un float aleatoire entre deux valeur
float CModel::fGetRandom()
{
    int High = 5;
    int Low = -5;
    float Div = 0.5;
    float result = ((float) (qrand() % ((High + 1) - Low) + Low)) / Div;
    return result;
}

//fonction renvoyant un float aleatoire entre deux valeur pour Z
float CModel::fGetRandomZ()
{
    int High = 0;
    int Low = -3.0;
    float Div = 0.75;
    float result = ((float) (qrand() % ((High + 1) - Low) + Low)) / Div;
    return result;
}

void CModel::detruireCube(int var){
    CObject* toRemove = tableau[var];
    CVector3 positionToRemove;
    toRemove->getPosition(&positionToRemove);

    for (int i = 0; i < tableau.size(); ++i) {
        CObject* current = tableau[i];
        CVector3 positionCurrent;
        current->getPosition(&positionCurrent);
        if ((positionCurrent.fGetY()==positionToRemove.fGetY()) && (positionCurrent.fGetZ()==positionToRemove.fGetZ()))
        {
            if (positionCurrent.fGetX()>positionToRemove.fGetX())
            {
                var = i;
            }
        }
    }
    tableau.removeAt(var);
}

bool CModel::plusDeBrique()
{
    if (tableau.size()==0)
        return true;
    else {return false;}
}

bool CModel::balleEnBas()
{
    CVector3 positionCourante;
    boule->getPosition(&positionCourante);
    if (positionCourante.fGetZ()>10)
    {
        return true;
    }
    else {
        return false;
    }
}

void CModel::reinitialiser()
{
    CVector3 position(2,0,8);
    boule->setPosition(&position);
    boule->vSetVitesse(0);
    boule->vSetVecteurVitesse(0);
}

void CModel::demarer() {
    boule->vSetVitesse(0.3535);
    boule->vSetVecteurVitesse(0);
}
