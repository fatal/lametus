#include "cursescontext.h"
#include "cursesapplication.h"
#include "curses.h"


CursesContext::CursesContext( const QRect& aPosition ) :
    iPosition( aPosition )
{
}

CursesContext::~CursesContext()
{
}

void CursesContext::initialize()
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
}

void CursesContext::deInitialize()
{
    endwin();
}

void
CursesContext::moveTo( const QPoint& aPoint )
{
    QPoint topLeft = iPosition.topLeft();
    topLeft += aPoint;
    if ( iPosition.contains( topLeft, false ) ) 
        move( topLeft.y(), topLeft.x() );
}
void CursesContext::moveTo( int x, int y )
{
    this->moveTo( QPoint( x, y ) );
}

void CursesContext::drawChar( const QChar& aChar )
{
    addch( aChar.toLatin1() | COLOR_PAIR( iCurrentColor ) );
}

void CursesContext::setColor( int aColor )
{
    iCurrentColor = aColor;
}
void CursesContext::drawString( const QString& aString )
{
    for ( int i=0; i<aString.length(); i++ )
        addch(aString.at(i).toLatin1() | COLOR_PAIR( iCurrentColor ) );
}
void CursesContext::setReverse( bool aReverse )
{
    if( aReverse ) 
        attron(A_REVERSE);
    else
        attroff(A_REVERSE);
}


