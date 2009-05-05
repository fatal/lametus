#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QObject>
#include <panel.h>

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

private:
    WINDOW * iWindow;
protected:
    int iX, iY, iWidth, iHeight;
    bool iVisible;
private:
    QList<CursesControl*> iChilds;
    CursesControl* iParent;
};

#endif // MAINWINDOW_H
