# -------------------------------------------------
# Project created by QtCreator 2009-05-04T17:06:20
# -------------------------------------------------
TARGET = lametus-qt
TEMPLATE = app
CONFIG += qt debug

SOURCES += main.cpp \
    mainwindow.cpp \
    encoder.cpp \
    audiosource.cpp \
    settings.cpp \
    lametus.cpp \
    lametus_ui.cpp
HEADERS += mainwindow.h \
    encoder.h \
    audiosource.h \
    settings.h \
    lametus.h \
    lametus_ui.h 
FORMS += mainwindow.ui
INCLUDEPATH += /usr/include/shout/ \
    /usr/include/lame/
LIBS += -lmp3lame \
    -lshout
OTHER_FILES += lametus.ini
