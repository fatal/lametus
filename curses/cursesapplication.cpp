/*
 * cursesapplication.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */
#include <QtCore/QTimer>
#include <ncurses.h>

#include "cursesapplication.h"
#include "curseswindow.h"
#include "cursescontrol.h"


CursesApplication * cursesApp = NULL;

CursesApplication::CursesApplication(int argc, char**argv) : QCoreApplication(argc, argv), iCurrentFocus(0)
{
    initscr(); start_color(); cbreak(); noecho();
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    clear();

    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

    refresh();

    iTimer = new QTimer();
    iTimer->setInterval( 60 );
    iTimer->setSingleShot( false );

    connect( iTimer, SIGNAL (timeout()),
	this, SLOT( timerTimeout() ));

    iTimer->start();
    cursesApp = this;

    iPendingRedraw = true;
}

CursesApplication::~CursesApplication()
{
    endwin();
    delete iTimer; 
    cursesApp = NULL;
}

void CursesApplication::addWindow( CursesWindow * aWindow )
{
    if ( cursesApp ) 
        cursesApp->iWindows.append( aWindow );
}

void CursesApplication::addFocusControl( CursesControl * aControl )
{
    if ( cursesApp ) 
        cursesApp->iFocusControls.append( aControl );
}

int CursesApplication::exec()
{
    return QCoreApplication::exec();
}

void CursesApplication::timerTimeout()
{
    bool consumed = false;
    int ch = getch();
    for ( int i=0; ch >= 0 && i<iWindows.count() && !consumed; i++ )
    {
        consumed = iWindows[0]->handleInput( ch );
    }

    if ( iPendingRedraw ) {
        for ( int i=0; i<iWindows.count(); i++ )
            iWindows[0]->draw();
        refresh();
        iPendingRedraw = false;
    }
    iTimer->start();
}

void CursesApplication::markDirty()
{
    cursesApp->iPendingRedraw = true;
}

void CursesApplication::nextFocus()
{
    if ( !cursesApp ) return;
    int count = cursesApp->iFocusControls.count();
    if ( count < 2 ) return;
    CursesControl* previous = currentFocus();
    incFocus();
    CursesControl* control = currentFocus();
    if ( previous && control ) {
        previous->setFocused( false );
        control->setFocused( true );
    }
    
}

void CursesApplication::previousFocus()
{
    if ( !cursesApp ) return;
    int count = cursesApp->iFocusControls.count();
    if ( count < 2 ) return;
    CursesControl* previous = currentFocus();
    decFocus();
    CursesControl* control = currentFocus();
    if ( previous && control ) {
        previous->setFocused( false );
        control->setFocused( true );
    }
}

void CursesApplication::incFocus()
{
    if ( !cursesApp ) return;
    int count = cursesApp->iFocusControls.count();
    cursesApp->iCurrentFocus ++;
    cursesApp->iCurrentFocus %= count;
} 

void CursesApplication::decFocus()
{
    if ( !cursesApp ) return;
    int count = cursesApp->iFocusControls.count();
    if ( count < 2 ) return;
    cursesApp->iCurrentFocus --;
    if ( cursesApp->iCurrentFocus < 0 )
        cursesApp->iCurrentFocus = count - 1;
} 

CursesControl* CursesApplication::currentFocus()
{
    if ( !cursesApp || !cursesApp->iFocusControls.count() )
        return NULL;
    return cursesApp->iFocusControls[cursesApp->iCurrentFocus];
}
