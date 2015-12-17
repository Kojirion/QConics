QT       += core gui opengl

CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QConics
TEMPLATE = app


SOURCES += main.cpp \
    Cone.cpp \
    Scene.cpp \
    MainView.cpp \
    MainWindow.cpp \
    SurfacePatch.cpp

HEADERS  += \
    Surface.hpp \
    Cone.hpp \
    Scene.hpp \
    MainView.hpp \
    MainWindow.hpp \
    SurfacePatch.hpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += glew

FORMS += \
    mainwindow.ui

DISTFILES += \
    shader/geometry.geom \
    shader/tess_control.tes \
    shader/tess_evaluation.tes \
    shader/fragment.frag \
    shader/vertex.vert

install_it.path = $$OUT_PWD/shader
install_it.files += $$DISTFILES

INSTALLS += install_it
