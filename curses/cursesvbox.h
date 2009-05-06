/*
 * cursesvbox.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef CURSESVBOX_H_
#define CURSESVBOX_H_

#include <QtCore/QObject>
#include "cursescontrol.h"

class CursesVBox : public CursesControl
{
    Q_OBJECT

public:
    CursesVBox(CursesControl * aParent);
    ~CursesVBox();

    void Draw();
    void Show();

    void addChild( CursesControl * aChild );
private:
    QList<CursesControl*> iChildren;
};


#endif /* CURSESBAR_H_ */
