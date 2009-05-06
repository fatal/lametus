#include "cursescontrol.h"

CursesControl::CursesControl(CursesControl* aParent ) :
	iParent( aParent ), iVisible ( 0 )
{

    // iWindow = newwin( w, h, x, y );
}

CursesControl::~CursesControl()
{
}

int CursesControl::NumberOfControls()
{
    return 0;
}

void CursesControl::Draw()
{
}

void CursesControl::Show()
{
    iVisible = 1;
}
WINDOW * CursesControl::Window()
{
    return iWindow;
}
void CursesControl::SetRect( int x, int y, int w, int h )
{
    iX = x;
    iY = y;
    iWidth = w;
    iHeight = h;
}
bool CursesControl::handleInput( int ch )
{
    return false;
}
