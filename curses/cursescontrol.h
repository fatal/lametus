#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QObject>
#include <curses.h>

class CursesControl : public QObject
{
    Q_OBJECT
public:
    CursesControl( CursesControl* aParent = NULL);
    ~CursesControl();

    virtual int NumberOfControls();
    virtual void Draw();
    virtual void Show();
    virtual void SetRect( int x, int y, int w, int h );
    virtual WINDOW* Window();
    virtual bool handleInput(int ch);
protected:
    int iX, iY, iWidth, iHeight;
    bool iVisible;
    CursesControl* iParent;
    WINDOW* iWindow;
private:
};

#endif // MAINWINDOW_H
