#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QObject>
#include <curses.h>

class QString;

class CursesControl : public QObject
{
    Q_OBJECT
public:
    CursesControl( CursesControl* aParent = NULL);
    ~CursesControl();

    virtual void draw();
    virtual void show();
    virtual void setRect( int x, int y, int w, int h );
    virtual WINDOW* Window();
    virtual bool handleInput(int ch);
    virtual int controlCount();
    virtual CursesControl* control(int index);
protected:
    int iX, iY, iWidth, iHeight;
    CursesControl* iParent;
    bool iVisible;
    WINDOW* iWindow;
    void markDirty();

    virtual void drawString(const QString&);
private:
};

#endif // MAINWINDOW_H
