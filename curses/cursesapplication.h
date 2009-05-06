/*
 * cursesapplication.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef CURSESAPPLICATION_H_
#define CURSESAPPLICATION_H_

#include <QtCore/QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QEventLoop>
#include <QtCore/QSocketNotifier>

class CursesWindow;

class CursesApplication : public QCoreApplication
{
    Q_OBJECT
public:
    CursesApplication(int argc, char**argv);
    ~CursesApplication();
    static void addWindow(CursesWindow*);
    int exec();
protected slots:
    void keyboardInput(int);

private:
    void doAddWindow(CursesWindow*);
    QList<CursesWindow*> iWindows;
    QSocketNotifier* iSocketNotifier;

};

#endif /* CURSESAPPLICATION_H_ */
