# -------------------------------------------------
# Project created by QtCreator 2009-05-04T17:06:20
# -------------------------------------------------
TARGET = lametus-qt
TEMPLATE = app
CONFIG += qt debug

MOC_DIR=tmp
OBJECTS_DIR=tmp

SOURCES += main.cpp \
    mainwindow.cpp \
    encoder.cpp \
    audiosource.cpp \
    audiosource_oss.cpp \
    audiosource_pulse.cpp \
    peakmonitor.cpp \
    settings.cpp \
    curses/cursescontrol.cpp \
    curses/cursescontext.cpp \
    curses/cursesbar.cpp \
    curses/cursesvbox.cpp \
    curses/cursesapplication.cpp \
    curses/curseswindow.cpp \
    curses/cursessetbar.cpp \
    curses-ui/vumeter.cpp \
    curses-ui/maincurseswindow.cpp \
    curses-ui/source.cpp \
    lametus.cpp 
HEADERS += mainwindow.h \
    encoder.h \
    audiosource.h \
    audiosource_oss.h \
    audiosource_pulse.h \
    peakmonitor.h \
    settings.h \
    curses/cursesapplication.h \
    curses/cursescontrol.h \
    curses/cursescontext.h \
    curses/cursesbar.h \
    curses/cursesvbox.h \
    curses/curseswindow.h \
    curses/cursessetbar.h \
    curses-ui/maincurseswindow.h \
    curses-ui/vumeter.h \
    curses-ui/source.h \
    lametus.h 
FORMS += mainwindow.ui
INCLUDEPATH += /usr/include/shout/ \
    /usr/include/lame/ curses ../lame-3.89/include curses-ui
LIBS += -L. -lmp3lame \
    -lshout -lncurses -lpulse-simple
OTHER_FILES += lametus.ini
