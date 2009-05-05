#include "cursescontrol.h"

CursesControl::CursesControl(CursesControl* aParent ) :
	iParent( aParent ), iVisible ( 0 )
{

    // iWindow = newwin( w, h, x, y );
}

CursesControl::~CursesControl()
{
	int i;
	for ( i = 0; i < iChilds.count(); i++ )
	{
		delete iChilds[i];
	}
}

int CursesControl::NumberOfControls()
{
	return iChilds.length() + 1;
}

void CursesControl::Draw()
{
	int i;
	if ( iVisible ) {
		for ( i=0; i<iChilds.count(); i++ )
		{
			iChilds[i]->Draw();
		}
	}
}

void CursesControl::Show()
{
	iVisible = 1;
}

void CursesControl::SetRect( int x, int y, int w, int h )
{
	iX = x;
	iY = y;
	iWidth = w;
	iHeight = h;
}
