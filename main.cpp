#include "cview.h"
#include "ccontroler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CModel oModel;
    CView oView;
    CControler oCtrl(&oModel);
    oCtrl.cglMaj(oView.getArea());

    oView.setControl(&oCtrl);
    oView.setModel(&oModel);
    oView.show();

    return a.exec();
}
