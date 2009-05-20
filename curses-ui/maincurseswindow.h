/*
 * maincurseswindow.h
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */

#ifndef MAINCURSESWINDOW_H_
#define MAINCURSESWINDOW_H_

#include <QtCore/QObject>
#include "curseswindow.h"

#include "audiosource.h"
#include "settings.h"
#include "encoder.h"
#include "lametus.h"


class CursesVUMeter;
class CursesSetBar;
class CursesBar;
class CursesAudioSource;


class MainCursesWindow : public CursesWindow
{
    Q_OBJECT

public:
    MainCursesWindow(CursesControl * aParent);
    ~MainCursesWindow();

    void draw();

    int controlCount();
    CursesControl* control(int);

    bool handleInput(int ch);
private:
    CursesVUMeter* iVUMeter;

    CursesSetBar* iTargetLevel;
    CursesSetBar* iExtraLevel;
    CursesBar* iTest;
    CursesAudioSource* iAudioSource;

protected:
public slots:
    void errorMessage(QString msg);
    void audioSourceCreated(AudioSource *src);
    void audioSourceUpdated(AudioSource *src);
    void encoderCreated(Encoder *enc);
    void encoderUpdated(Encoder *enc);
private:
    Lametus lametus;
    QList<QString> iErrorMessages;

};


#endif /* CURSESWINDOW_H_ */
