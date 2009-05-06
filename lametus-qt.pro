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
    curses/cursescontrol.cpp \
    curses/cursesbar.cpp \
    curses/cursesvbox.cpp \
    curses/cursesapplication.cpp \
    curses/curseswindow.cpp \
    vumeter.cpp \
    maincurseswindow.cpp \
    lametus.cpp \
    lametus_ui.cpp
HEADERS += mainwindow.h \
    encoder.h \
    audiosource.h \
    settings.h \
    curses/cursesapplication.h \
    curses/cursescontrol.h \
    curses/cursesbar.h \
    curses/cursesvbox.h \
    curses/curseswindow.h \
    maincurseswindow.h \
    vumeter.h \
    lametus.h \
    lametus_ui.h 
FORMS += mainwindow.ui
INCLUDEPATH += /usr/include/shout/ \
    /usr/include/lame/ curses ../lame-3.89/include
LIBS += -L. -lmp3lame \
    -lshout -lncurses
OTHER_FILES += lametus.ini
