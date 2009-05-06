#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include <linux/soundcard.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <QDebug>

#define OSS_DEFAULT_DEVNAME "/dev/dsp"


struct audio_oss_internal
{
        int fd;
};

enum audio_source_status_t {
  AUDIO_SOURCE_OK,
  AUDIO_SOURCE_FAIL,
  AUDIO_SOURCE_UNKNOWN
};

class AudioSource : public QObject
{
    Q_OBJECT

public:
    AudioSource(QObject * parent);
    ~AudioSource();
    unsigned int getSamplerate();
    int getChannels();
    audio_source_status_t getStatus();
    bool Init(unsigned int samplerate, int channels, QString device);
    void Read(unsigned char *,int);
private:
    QString devname;
    unsigned int samplerate;
    int channels;
    void *internal_data;
    audio_source_status_t status;
};

#endif // AUDIOSOURCE_H
