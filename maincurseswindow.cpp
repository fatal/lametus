/*
 * MainCursesWindow.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */
#include "maincurseswindow.h"
#include "cursesapplication.h"
#include "cursessetbar.h"
#include "vumeter.h"

MainCursesWindow::MainCursesWindow( CursesControl* aParent ) : 
	CursesWindow( aParent )
{
    iVUMeter = new CursesVUMeter(this);
    iTargetLevel = new CursesSetBar(this, QString("test"), 10);
    iTest = new CursesBar(this, QString("test2"), 10);
    connect( iTargetLevel, SIGNAL( valueChanged(int) ),
             iTest, SLOT( setValue(int) ) );
    iVUMeter->setRect(0, 0, 80, 3);
    iTargetLevel->setRect(0, 4, 80, 1);
    iTest->setRect(0, 5, 80, 1);
}

MainCursesWindow::~MainCursesWindow()
{
    delete iVUMeter;
    delete iTargetLevel;
    delete iTest;
}

CursesControl* MainCursesWindow::control(int index)
{
    switch (index) {
    case 0: return iVUMeter;
    case 1: return iTargetLevel;
    case 2: return iTest;
    default: return 0;
    }
}
int MainCursesWindow::controlCount()
{
    return 3;
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
