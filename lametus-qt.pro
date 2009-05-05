# -------------------------------------------------
# Project created by QtCreator 2009-05-04T17:06:20
# -------------------------------------------------
TARGET = lametus-qt
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    encoder.cpp \
    audiosource.cpp \
    settings.cpp \
    curses/cursesapplication.cpp \
    curses/cursescontrol.cpp \
    curses/cursesbar.cpp
HEADERS += mainwindow.h \
    encoder.h \
    audiosource.h \
    settings.h \
    curses/cursesapplication.h \
    curses/cursescontrol.h \
    curses/cursesbar.h
FORMS += mainwindow.ui
INCLUDEPATH += /usr/include/shout/ \
    /usr/include/lame/ curses
LIBS += -lmp3lame \
    -lshout -lncurses
OTHER_FILES += lametus.ini
