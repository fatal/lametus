/*
 * CursesBar.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#include "cursesbar.h"

CursesBar::CursesBar( CursesControl* aParent ) : CursesControl( aParent )
{

}

CursesBar::~CursesBar()
{

}

void CursesBar::setValue( int aValue )
{
	if ( aValue >= 0 && aValue < iWidth )
		iValue = aValue;
}

void CursesBar::Draw()
{
	int i;
	for ( i=0 ; i<iValue; i++ )
	{
		if ( i > iValue * 7 / 10 )
			addch('#'|COLOR_PAIR(1));
		else if ( i > iValue * 6 / 10 )
			addch('#'|COLOR_PAIR(2));
		else
			addch('#'|COLOR_PAIR(3));
	}
	CursesControl::Draw();
}
