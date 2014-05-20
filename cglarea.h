#ifndef CGLAREA_H
#define CGLAREA_H
#include<QGLWidget>
#include "cmodel.h"
#include <QPoint>

class CGLArea : public QGLWidget
{
    Q_OBJECT
private:
    float m_radius;
    float m_azimuth;
    float m_elevation;
    QPoint lastPos;
    QPoint lastPosWheel;
    QPoint lastPosBoule;
    CModel* m_poModel;
    CPalet* palet;
    CSphere* boule;
    int avantDepla;
public:
    CGLArea(QWidget *parent = 0);
    ~CGLArea();
    void vSetModel(CModel *_poModel);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void updateCamera(void);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent ( QWheelEvent * event ); 
    void mouvementPalet(int x);

    void afficherBoule();
    void afficherPalet();
    void AfficherCubes();
    void afficherBords();

    int onDoitStopper();
    void demarrer();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
public slots :
    void mouvementBoule();
};

#endif // CGLAREA_H
