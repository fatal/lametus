
// #define CURSES

#ifndef CURSES
#include <QtGui/QApplication>
#include "mainwindow.h"
#else
#include "cursesapplication.h"
#include "maincurseswindow.h"
#endif


int main(int argc, char *argv[])
{
#ifndef CURSES
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#else
    CursesApplication a(argc, argv);
    MainCursesWindow win(NULL);
    win.show();
    return a.exec();
#endif
}
