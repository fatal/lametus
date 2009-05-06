/*
 * maincurseswindow.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef MAINCURSESWINDOW_H_
#define MAINCURSESWINDOW_H_

#include <QtCore/QObject>
#include "curseswindow.h"
#include "vumeter.h"

class MainCursesWindow : public CursesWindow
{
    Q_OBJECT

public:
    MainCursesWindow(CursesControl * aParent);
    ~MainCursesWindow();

    void draw();

    int controlCount();
    CursesControl* control(int);

    bool handleInput(int ch);
private:
    CursesVUMeter* iVUMeter;
};


#endif /* CURSESWINDOW_H_ */
