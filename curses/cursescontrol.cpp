#include <QtCore/QTimer>
#include "cursescontrol.h"
#include "cursesapplication.h"
#include "cursescontext.h"


CursesControl::CursesControl(CursesControl* aParent ) :
	iParent( aParent ), iVisible ( 0 ), iFocused( 0 ), iCursesContext( 0 )
{
}

CursesControl::~CursesControl()
{
    if ( iCursesContext ) delete iCursesContext;
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
    iPosition = QRect(x, y, w, h);
}
bool CursesControl::handleInput( int ch )
{
    bool consumed = false;

    if ( isFocused() ) {
        switch (ch) {
        case KEY_UP:
            CursesApplication::previousFocus();
            consumed = true;
            break;
        case KEY_DOWN:
            CursesApplication::nextFocus();
            consumed = true;
            break;
        }
    }
    for ( int i=0; i<controlCount() && !consumed; i++ )
        consumed = control(i)->handleInput(ch);
    return consumed;
}

void CursesControl::markDirty()
{
    CursesApplication::markDirty();
}

bool CursesControl::isFocused() 
{
    return iFocused;
}

bool CursesControl::isNonFocusing() 
{
    return true;
}

bool CursesControl::setFocused(bool aFocused)
{
    if ( !isNonFocusing() ) {
        markDirty();
        iFocused = aFocused; 
    }
    return iFocused;
}

CursesContext& CursesControl::context() 
{
    if ( !iCursesContext ) 
        iCursesContext = new CursesContext( iPosition );
    return *iCursesContext;
}

