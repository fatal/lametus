#include "audiosource.h"
#include <QtCore/QTimer>

AudioSource::AudioSource(QObject * parent) : QObject(parent)
{
    status = AUDIO_SOURCE_UNKNOWN;
    samplerate = 44100;
    channels = 2;
    iTimer = new QTimer();
}

AudioSource::~AudioSource()
{
    delete iTimer;
}

unsigned int AudioSource::getSamplerate() {
    return samplerate;
}
int AudioSource::getChannels() {
    return channels;
}

audio_source_status_t AudioSource::getStatus() {
    return status;
}

void AudioSource::start()
{
    iTimer->setInterval(30);
    connect(iTimer, SIGNAL(timeout()),
            this, SLOT(timerTimeout()));
    iTimer->start();
}

void AudioSource::timerTimeout() 
{
    read();
    iTimer->start();
}
