/*
 * CursesBar.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#include "cursesbar.h"
#include "cursescontext.h"

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

    CursesContext& cc = context();
    cc.setColor( 1 );

    cc.moveTo( 0, 0 );

    if ( iFocused ) cc.setReverse( true );
    cc.drawString( label() );
    cc.setReverse( false );

    cc.moveTo( iPadding, 0 );

    int w = iPosition.width() - iPadding;

    int value = w * iValue / 100;

	for ( i=0 ; i<value; i++ )
	{
		if ( i > w * 7 / 10 )
			cc.setColor(1);
		else if ( i > w * 6 / 10 )
			cc.setColor(2);
		else
			cc.setColor(3);

        cc.drawChar( QChar('#') );
	}
    for (; i<w; i++) cc.drawChar( QChar(' ') );
	CursesControl::draw();
}
