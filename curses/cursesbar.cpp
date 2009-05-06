/*
 * CursesBar.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#include "cursesbar.h"

CursesBar::CursesBar( CursesControl* aParent, const QString& aLabel  ) : 
    CursesControl( aParent ), iLabel( aLabel) 
{

}

CursesBar::~CursesBar()
{

}

void CursesBar::setValue( int aValue )
{
    // value is in %
	if ( aValue >= 0 && aValue <= 100 ) 
    {
		iValue = aValue;
        markDirty();
    }
    
}

void CursesBar::draw()
{
	int i;
    move( iY, iX );
    drawString( iLabel );
    int w = iWidth - iLabel.length();

    int value = w * iValue / 100;

	for ( i=0 ; i<value; i++ )
	{
		if ( i > value * 7 / 10 )
			addch('#'|COLOR_PAIR(1));
		else if ( i > value * 6 / 10 )
			addch('#'|COLOR_PAIR(2));
		else
			addch('#'|COLOR_PAIR(3));
	}
	CursesControl::draw();
}
