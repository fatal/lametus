/*
 * cursesbar.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef CURSESBAR_H_
#define CURSESBAR_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include "cursescontrol.h"


class CursesBar : public CursesControl
{
    Q_OBJECT

public:
	CursesBar(CursesControl * aParent, const QString& aLabel, int aPadding);
    ~CursesBar();

    void draw();

public slots:
	void setValue(int);
protected:
	int iValue;
    virtual QString label();
    QString iLabel;
    int iPadding;
};


#endif /* CURSESBAR_H_ */
