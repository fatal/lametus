/*
 * curseswindow.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef CURSESWINDOW_H_
#define CURSESWINDOW_H_

#include <QtCore/QObject>
#include "cursescontrol.h"

class CursesWindow : public CursesControl
{
    Q_OBJECT

public:
    CursesWindow(CursesControl * aParent);
    ~CursesWindow();

    void Draw();

    void Show();
    void setChild( CursesControl * aChild );
    bool handleInput(int ch);

    WINDOW* Window();
private:
    CursesControl* iChild;
};


#endif /* CURSESWINDOW_H_ */
