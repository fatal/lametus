/*
 * cursesbar.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef CURSESBAR_H_
#define CURSESBAR_H_

#include <QtCore/QObject>
#include "cursescontrol.h"

class CursesBar : public CursesControl
{
    Q_OBJECT

public:
	CursesBar(CursesControl * aParent);
    ~CursesBar();

    void Draw();

public slots:
	void setValue(int);
private:
	int iValue;
};


#endif /* CURSESBAR_H_ */
