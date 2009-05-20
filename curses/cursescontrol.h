#ifndef CURSESCONTROL_H
#define CURSESCONTROL_H

#include <QtCore/QObject>
#include <QtCore/QRect>
#include <curses.h>

class QString;
class CursesContext;

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
    virtual bool isNonFocusing();
    virtual bool setFocused(bool aFocused);
    virtual CursesContext& context();
    bool isFocused();
protected:
    QRect iPosition;
    CursesControl* iParent;
    bool iVisible;
    WINDOW* iWindow;
    void markDirty();
    bool iFocused;
    CursesContext* iCursesContext;

private:
};

#endif // CURSESCONTROL_H
