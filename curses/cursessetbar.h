/*
 * cursesbar.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef CURSESSETBAR_H_
#define CURSESSETBAR_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include "cursesbar.h"


class CursesSetBar : public CursesBar
{
    Q_OBJECT
public:
	CursesSetBar(CursesControl * aParent, const QString& aLabel, int aPadding);
    ~CursesSetBar();

    bool isNonFocusing();
    bool handleInput(int ch);
signals:
    void valueChanged(int);

protected:
    QString label();
    
};


#endif /* CURSESBAR_H_ */
