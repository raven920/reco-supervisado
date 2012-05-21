#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T11:27:21
#
#-------------------------------------------------

QT       += core gui

TARGET = TareaGrupo3
TEMPLATE = app


win32 {

    INCLUDEPATH += "C:/OpenCV2.1/include/opencv"

    TEMPLATE = app

    LIBS += "C:\OpenCV2.1\lib\cv210.lib"   \
        "C:\OpenCV2.1\lib\cv210d.lib"      \
        "C:\OpenCV2.1\lib\cvaux210.lib"    \
        "C:\OpenCV2.1\lib\cvaux210d.lib"   \
        "C:\OpenCV2.1\lib\cxcore210.lib"   \
        "C:\OpenCV2.1\lib\cxcore210d.lib"  \
        "C:\OpenCV2.1\lib\highgui210.lib"  \
        "C:\OpenCV2.1\lib\highgui210d.lib" \
}

unix {

    CONFIG   -= app_bundle

    INCLUDEPATH += /usr/include/opencv

    TEMPLATE = app

    LIBS += `pkg-config opencv --cflags --libs`

}

SOURCES += main.cpp\
        mainwindow.cpp \
    Imagen/imagenCv.cpp

HEADERS  += mainwindow.h \
    Imagen/imagenCv.h

FORMS    += mainwindow.ui

