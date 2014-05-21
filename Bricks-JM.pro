#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T09:40:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Bricks
TEMPLATE = app

QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

SOURCES += main.cpp\
        cview.cpp \
    ccontroler.cpp \
    cmodel.cpp \
    cobject.cpp\
	CVector3.cpp \
    ccube.cpp \
    cglarea.cpp \
    CShpere.cpp \
        cpalet.cpp \
    cbord.cpp \
        webcamwindow.cpp\
    rectangle.cpp

HEADERS  += cview.h \
    ccontroler.h \
    cmodel.h \
    cobject.h\
	CVector3.h \
    ccube.h \
    cglarea.h \
	CSphere.h \
        cpalet.h \
    cbord.h \
        webcamwindow.h\
    rectangle.h

INCLUDEPATH +=$$(OPENCV_DIR)\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core248 \
    -lopencv_highgui248 \
    -lopencv_imgproc248 \
    -lopencv_features2d248 \
    -lopencv_calib3d248 \
    -lopencv_objdetect248


