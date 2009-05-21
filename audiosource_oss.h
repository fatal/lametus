#ifndef AUDIOSOURCEOSS_H
#define AUDIOSOURCEOSS_H
#include <linux/soundcard.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <QDebug>
#include "audiosource.h"

#define OSS_DEFAULT_DEVNAME "/dev/dsp"


struct audio_oss_internal
{
        int fd;
};

class AudioSourceOss : public AudioSource
{
    Q_OBJECT

public:
    AudioSourceOss(QObject * parent);
    ~AudioSourceOss();
    bool Init(unsigned int samplerate, int channels, QString device);
protected:
    void read();
    void *internal_data;
    QString devname;
};

#endif // AUDIOSOURCEOSS_H
