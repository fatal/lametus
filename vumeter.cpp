#include <QtCore/QTimer>
#include "vumeter.h"
#include <cursesbar.h>


CursesVUMeter::CursesVUMeter(CursesControl* aParent ) :
	CursesControl( aParent )
{
    iLeftChannel = new CursesBar( this, QString("[left ]") );
    iRightChannel = new CursesBar( this, QString("[right]") );

    iLeftChannel->setRect(0, 1, 80, 2);
    iRightChannel->setRect(0, 2, 80, 2);
}

CursesVUMeter::~CursesVUMeter()
{
}

int CursesVUMeter::controlCount()
{
    return 2;
}
CursesControl* CursesVUMeter::control(int index)
{
    switch (index) {
    case 0:
        return iLeftChannel;
    case 1:
        return iRightChannel;
    default:
        return NULL;
    }
}
void CursesVUMeter::draw()
{
    CursesControl::draw();
}
bool CursesVUMeter::handleInput( int ch )
{
    if ( ch == '+' ) { iLeftChannel->setValue(50); return true; }
    return CursesControl::handleInput(ch);
}
