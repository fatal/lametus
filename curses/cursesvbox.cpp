/*
 * CursesVBox.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#include "cursesvbox.h"

CursesVBox::CursesVBox( CursesControl* aParent ) : CursesControl( aParent )
{
}

CursesVBox::~CursesVBox()
{
}

void CursesVBox::addChild( CursesControl* aChild )
{
    if ( aChild )
        iChildren.append( aChild );
}

CursesControl* CursesVBox::control(int index)
{
    return iChildren[index];
}
int CursesVBox::controlCount()
{
    return iChildren.count();
}

void CursesVBox::draw()
{
    // decoration etc stuff goes here if anything.. 
    CursesControl::draw();
}
