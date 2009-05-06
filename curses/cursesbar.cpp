/*
 * CursesBar.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#include "cursesbar.h"

CursesBar::CursesBar( CursesControl* aParent, const QString& aLabel,
                      int aPadding  ) : 
    CursesControl( aParent ), iLabel( aLabel), iPadding(aPadding)
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

QString CursesBar::label()
{
    return iLabel;
}

void CursesBar::draw()
{
	int i;
    move( iY, iX );
    drawString( label() );
    move( iY, iX+iPadding );
    int w = iWidth - iPadding;

    int value = w * iValue / 100;

	for ( i=0 ; i<value; i++ )
	{
		if ( i > w * 7 / 10 )
			addch('#'|COLOR_PAIR(1));
		else if ( i > w * 6 / 10 )
			addch('#'|COLOR_PAIR(2));
		else
			addch('#'|COLOR_PAIR(3));
	}
    for (; i<w; i++) addch(' ');
	CursesControl::draw();
}
