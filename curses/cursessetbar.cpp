/*
 * CursesSetBar.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#include "cursessetbar.h"
#include "cursesapplication.h"

CursesSetBar::CursesSetBar( CursesControl* aParent, 
                            const QString& aLabel,
                            int aPadding  ) : 
    CursesBar( aParent, aLabel, aPadding ) 
{
    CursesApplication::addFocusControl( this );
}

CursesSetBar::~CursesSetBar()
{
}

bool CursesSetBar::isNonFocusing()
{
    return false;
}

QString CursesSetBar::label()
{
    QString s = QString("%1 %2 ").arg(CursesBar::label()).arg(iValue, 3);
    return s;
}

bool CursesSetBar::handleInput(int ch)
{
    bool consumed = false;
    if ( !isFocused() ) return false;
    switch(ch) {
    case KEY_LEFT:
        if ( iValue > 0 ) iValue --;
        consumed = true;
        break;
    case KEY_RIGHT:
        if ( iValue < 100 ) iValue ++;
        consumed = true;
        break;
    default:
        break;
    }
    if ( consumed ) {
        markDirty();
        emit valueChanged( iValue );
    }
    else consumed = CursesBar::handleInput(ch);
    return consumed;
}
