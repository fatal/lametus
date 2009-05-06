#include <QtCore/QTimer>
#include "cursescontrol.h"
#include "cursesapplication.h"


CursesControl::CursesControl(CursesControl* aParent ) :
	iParent( aParent ), iVisible ( 0 )
{

    // iWindow = newwin( w, h, x, y );
}

CursesControl::~CursesControl()
{
}

int CursesControl::controlCount()
{
    return 0;
}

CursesControl* CursesControl::control(int /* index */ )
{
    return 0;
}

void CursesControl::draw()
{
    for ( int i=0; i<controlCount(); i++ ) 
        control(i)->draw();
}

void CursesControl::show()
{
    iVisible = 1;
    for ( int i=0; i<controlCount(); i++ )
        if( control(i) ) control(i)->show();
}
WINDOW * CursesControl::Window()
{
    return iWindow;
}
void CursesControl::setRect( int x, int y, int w, int h )
{
    iX = x;
    iY = y;
    iWidth = w;
    iHeight = h;
}
bool CursesControl::handleInput( int ch )
{
    bool consumed = false;
    for ( int i=0; i<controlCount() && !consumed; i++ )
        consumed = control(i)->handleInput(ch);
    return consumed;
}

void CursesControl::drawString( const QString& aString )
{
    for ( int i=0; i<aString.length(); i++ )
        addch(aString.at(i).toLatin1());
}

void CursesControl::markDirty()
{
    CursesApplication::markDirty();
}

bool CursesControl::isNonFocusing() 
{
    return true;
}

