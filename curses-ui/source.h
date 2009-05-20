#ifndef CURSESAUDIOSOURCE_H
#define CURSESAUDIOSOURCE_H

#include <QtCore/QObject>
#include <curses.h>
#include "cursescontrol.h"
#include "audiosource.h"

class CursesAudioSource : public CursesControl
{
    Q_OBJECT
public:
    CursesAudioSource( CursesControl* aParent = NULL);
    ~CursesAudioSource();

    void draw();
public slots:
    void audioSourceUpdated( AudioSource* aAudioSource );
protected:
    AudioSource* iAudioSource;
private:
};

#endif // CURSESAUDIOSOURCE_H
