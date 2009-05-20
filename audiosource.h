#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <QDebug>

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
    virtual int Read(unsigned char *,int) = 0;
protected:
    unsigned int samplerate;
    int channels;
    audio_source_status_t status;
};

#endif // AUDIOSOURCE_H
