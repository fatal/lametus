/*
 * MainCursesWindow.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */
#include "maincurseswindow.h"
#include "cursesapplication.h"

MainCursesWindow::MainCursesWindow( CursesControl* aParent ) : 
	CursesWindow( aParent )
{
    iVUMeter = new CursesVUMeter(this);
}

MainCursesWindow::~MainCursesWindow()
{
}

CursesControl* MainCursesWindow::control(int index)
{
    switch (index) {
    case 0: return iVUMeter;
    default: return 0;
    }
}
int MainCursesWindow::controlCount()
{
    return 1;
}

void MainCursesWindow::draw()
{
    // decoration etc stuff goes here if anything.. 
    CursesWindow::draw();
}
bool MainCursesWindow::handleInput( int ch )
{
    if ( ch == 9 ) {
        CursesApplication::quit();
        return true;
    }
    return CursesWindow::handleInput( ch );
}
