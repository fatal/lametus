/*
 * cursesapplication.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#include "cursesapplication.h"
#include <ncurses.h>

CursesApplication::CursesApplication()
{
    initscr(); start_color(); cbreak(); noecho();
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
}

CursesApplication::~CursesApplication()
{
	endwin();
}
