#ifndef CURSESCONTEXT_H
#define CURSESCONTEXT_H

#include <QtCore/QObject>
#include <QtCore/QRect>
#include <curses.h>

class QString;

/** A drawing context for curses drawing operations */

class CursesContext : public QObject
{
    Q_OBJECT
public:
    CursesContext( const QRect& aPosition );
    ~CursesContext();
    void setColor( int aColor );
    void drawChar( const QChar& aChar );
    void moveTo( const QPoint& aPosition ); // Position within context
    void moveTo( int x, int y ); // Position within context
    void drawString( const QString& aString );
    void setReverse( bool );
    static void initialize();
    static void deInitialize();
protected:
    QRect iPosition; // Absolute coordinates
    int iCurrentColor;
private:
};

#endif // CURSESCONTEXT_H
