/*
 * cursesapplication.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef CURSESAPPLICATION_H_
#define CURSESAPPLICATION_H_

#include <curses.h>
#include <QtCore/QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QEventLoop>
// #include <QtCore/QTimer>

class CursesWindow;
class QTimer;
class CursesApplication : public QCoreApplication
{
    Q_OBJECT
public:
    CursesApplication(int argc, char**argv);
    ~CursesApplication();
    static void addWindow(CursesWindow*);
    int exec();
public slots:
    void timerTimeout();

private:
    void doAddWindow(CursesWindow*);
    QList<CursesWindow*> iWindows;

    QTimer* iTimer;

    bool iPendingRedraw;
};

#endif /* CURSESAPPLICATION_H_ */
