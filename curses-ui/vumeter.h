#ifndef VUMETER_H
#define VUMETER_H

#include <QtCore/QObject>
#include <curses.h>
#include "cursescontrol.h"

class CursesBar;

class CursesVUMeter : public CursesControl
{
    Q_OBJECT
public:
    CursesVUMeter( CursesControl* aParent = NULL);
    ~CursesVUMeter();

    int controlCount();
    CursesControl* control(int);
    void draw();
    bool handleInput(int ch);
protected:
    CursesBar* iLeftChannel;
    CursesBar* iRightChannel;
private:
};

#endif // VUMETER_H
