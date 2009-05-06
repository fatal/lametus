/*
 * cursesapplication.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#include "cursesapplication.h"
#include "curseswindow.h"
#include <ncurses.h>

CursesApplication * cursesApp = NULL;

CursesApplication::CursesApplication(int argc, char**argv) : QCoreApplication(argc, argv)
{
    initscr(); start_color(); cbreak(); noecho();
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    clear();

    move(5,0); addch('A'); addch('v'); addch('g');


    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    refresh();

    iSocketNotifier = new QSocketNotifier( 0, QSocketNotifier::Read );

    connect( iSocketNotifier, SIGNAL (activated(int)),
	this, SLOT( keyboardInput(int) ));
}

CursesApplication::~CursesApplication()
{
    endwin();
    delete iSocketNotifier;
}

void CursesApplication::addWindow(CursesWindow * aWindow)
{
    if ( cursesApp ) 
        cursesApp->iWindows.append(aWindow);
}

int CursesApplication::exec()
{
    return QCoreApplication::exec();
}

void CursesApplication::keyboardInput(int socket)
{
    bool consumed = false;
    int ch = getch();
    for ( int i=0; i<iWindows.count() && !consumed; i++ )
        consumed = iWindows[0]->handleInput( ch );
}
