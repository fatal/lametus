#include "audiosource.h"

AudioSource::AudioSource(QObject * parent) : QObject(parent)
{
    status = AUDIO_SOURCE_UNKNOWN;
    samplerate = 44100;
    channels = 2;
}

AudioSource::~AudioSource()
{
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
