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

void CursesVBox::Show()
{
    for ( int i=0; i<iChildren.count(); i++)
	iChildren[i]->Show();
}

void CursesVBox::Draw()
{
    // decoration etc stuff goes here if anything.. 
    for ( int i=0; i<iChildren.count(); i++ )
        iChildren[i]->Draw();
}
