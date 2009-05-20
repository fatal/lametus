#ifndef AUDIOSOURCEPULSE_H
#define AUDIOSOURCEPULSE_H

#include <QDebug>
#include "audiosource.h"
#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>


class AudioSourcePulse : public AudioSource
{
    Q_OBJECT

public:
    AudioSourcePulse(QObject * parent);
    ~AudioSourcePulse();
    bool Init(unsigned int samplerate, int channels);
    int Read(unsigned char *,int);
protected:
    QString devname;
    pa_simple* pulse;
};

#endif // AUDIOSOURCEOSS_H
