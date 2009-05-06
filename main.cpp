
#define CURSES

#ifndef CURSES
#include <QtGui/QApplication>
#include "mainwindow.h"
#else
#include "cursesapplication.h"
#include "cursesbar.h"
#include "curseswindow.h"
#include "cursesvbox.h"
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
    CursesWindow win(NULL);
    CursesVBox box((CursesControl*)&win);
    CursesBar bar(&box);
    box.addChild(&bar);
    win.Show();
    return a.exec();
#endif
}
