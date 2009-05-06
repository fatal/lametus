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

WINDOW* CursesWindow::Window() 
{
    if ( iParent ) return iParent->Window();
    else if ( iWindow ) return iWindow;
//    iWindow = newwin( iWidth, iHeight, iX, iY );
    return iWindow;
}
void CursesWindow::Show()
{
    if ( iChild ) iChild->Show();
    CursesControl::Show();
}

void CursesWindow::Draw()
{
    // decoration etc stuff goes here if anything.. 
    if ( iChild ) iChild->Draw();
}
bool CursesWindow::handleInput( int ch )
{
    addch('e');
    if ( ch == 9 ) {
        CursesApplication::quit();
	addch('t');
        return true;
    }
    return false;
}
