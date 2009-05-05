
#define CURSES

#ifndef CURSES
#include <QtGui/QApplication>
#include "mainwindow.h"
#else
#include "cursesapplication.h"
#include "cursesbar.h"
#endif


int main(int argc, char *argv[])
{
#ifndef CURSES
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#else
    CursesApplication a();
    CursesBar bar(0);
    bar.SetRect(0,0,80,1);
    bar.Show();
#endif
}
