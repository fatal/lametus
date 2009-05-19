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
class CursesControl;
class QTimer;

class CursesApplication : public QCoreApplication
{
    Q_OBJECT
public:
    CursesApplication(int argc, char**argv);
    ~CursesApplication();
    static void addWindow(CursesWindow*);
    static void addFocusControl(CursesControl*);
    static void previousFocus();
    static void nextFocus();
    static void markDirty();
    static CursesControl* currentFocus();
    int exec();
public slots:
    void timerTimeout();
    static void incFocus();
    static void decFocus();

private:
    // list of windows in this application
    QList<CursesWindow*> iWindows;
    // list of focusable controls (in order)
    // hack? of course..
    QList<CursesControl*> iFocusControls;
    int iCurrentFocus;

    QTimer* iTimer;

    bool iPendingRedraw;
};

#endif /* CURSESAPPLICATION_H_ */
