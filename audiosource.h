#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <QDebug>

class QTimer;

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
    void start();
signals:
    void dataAvailable(short*, int);
public slots:
    void timerTimeout();
protected:
    virtual void read() = 0;
    QTimer* iTimer;
    unsigned int samplerate;
    int channels;
    audio_source_status_t status;
};

#endif // AUDIOSOURCE_H
