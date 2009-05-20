#include "audiosource_pulse.h"

AudioSourcePulse::AudioSourcePulse(QObject * parent) : AudioSource(parent)
{
    status = AUDIO_SOURCE_UNKNOWN;
    samplerate = 44100;
    channels = 2;
}

AudioSourcePulse::~AudioSourcePulse()
{
    if ( pulse ) 
        pa_simple_free( pulse );
}

bool AudioSourcePulse::Init(unsigned int samplerate, int channels)
{
    this->samplerate = samplerate;
    this->channels = channels;
    status = AUDIO_SOURCE_FAIL;

    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16NE;
    ss.channels = channels;
    ss.rate = samplerate;
    pulse = pa_simple_new(
        NULL, "Lametus", PA_STREAM_RECORD,
        NULL, "Music input", &ss,
        NULL, NULL, NULL );
    if ( !pulse ) return FALSE;

    status = AUDIO_SOURCE_OK;
    return TRUE;
}

int AudioSourcePulse::Read(unsigned char* buf, int maxLength )
{
    int err = 0;
    return pa_simple_read( pulse, buf, maxLength, &err );
}
