/*
 * CursesWindow.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */
#include "curseswindow.h"
#include "cursesapplication.h"

CursesWindow::CursesWindow( CursesControl* aParent ) : 
	CursesControl( aParent ), iChild(0)
{
    CursesApplication::addWindow(this);
}

CursesWindow::~CursesWindow()
{
}

void CursesWindow::setChild( CursesControl* aChild )
{
    if ( iChild ) delete iChild;
    iChild = aChild;
}

CursesControl* CursesWindow::control(int index)
{
    return iChild;
}
int CursesWindow::controlCount()
{
    return iChild == 0 ? 0 : 1;
}

WINDOW* CursesWindow::Window() 
{
    if ( iParent ) return iParent->Window();
    else if ( iWindow ) return iWindow;
//    iWindow = newwin( iWidth, iHeight, iX, iY );
    return iWindow;
}

void CursesWindow::draw()
{
    // decoration etc stuff goes here if anything.. 
    CursesControl::draw();
}
bool CursesWindow::handleInput( int ch )
{
    return CursesControl::handleInput( ch );
}
