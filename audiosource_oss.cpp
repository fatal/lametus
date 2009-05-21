#include "audiosource_oss.h"
#include <unistd.h>

AudioSourceOss::AudioSourceOss(QObject * parent) : AudioSource(parent)
{
    internal_data = malloc(sizeof(struct audio_oss_internal));
    if (!internal_data)
        qDebug("Out of memory");
    status = AUDIO_SOURCE_UNKNOWN;
    devname = strdup(OSS_DEFAULT_DEVNAME);
    samplerate = 44100;
    channels = 2;
}

AudioSourceOss::~AudioSourceOss()
{
    struct audio_oss_internal *oss =
            (struct audio_oss_internal *)internal_data;
    if(oss && oss->fd >= 0)
        close(oss->fd);
    qDebug("Audio source closed");
}

bool AudioSourceOss::Init(unsigned int samplerate, int channels, QString device)
{
    this->samplerate = samplerate;
    this->channels = channels;
    this->devname = device;
    status = AUDIO_SOURCE_FAIL;
    int tmp;
    struct audio_oss_internal *oss =
            (struct audio_oss_internal *)internal_data;

    oss->fd = open(devname.toLatin1().data(),O_RDONLY);
    if (oss->fd < 0) {
        qDebug("Could not open audio device '%s': %s",devname.toAscii().data(), strerror(errno));
        return FALSE;
    }

    tmp = AFMT_S16_LE;

    if (ioctl(oss->fd,SNDCTL_DSP_SETFMT,&tmp) < 0) {
        qDebug("Could not set sample format: %s",strerror(errno));
        return FALSE;
    }

    tmp = channels - 1;

    if (ioctl(oss->fd,SNDCTL_DSP_STEREO,&tmp) < 0) {
        qDebug("Could not set number of channels: %s",strerror(errno));
        return FALSE;
    }

    tmp = samplerate;

    if (ioctl(oss->fd,SNDCTL_DSP_SPEED,&tmp) < 0) {
        qDebug("Could not set samplerate: %s",strerror(errno));
        return FALSE;
    }

    fprintf(stderr,"OSS Audio source initialized:\n");
    fprintf(stderr," Device: '%s'\n",devname.toAscii().data());
    fprintf(stderr," Samplerate: %d Channels: %d\n\n",samplerate,
            channels);
    status = AUDIO_SOURCE_OK;
    return TRUE;
}

#define BUF_SIZE 8192

void AudioSourceOss::read()
{
    struct audio_oss_internal *oss =
            (struct audio_oss_internal *)internal_data;
    unsigned char buf[BUF_SIZE];
    unsigned char* buffer = buf;
    int got = 0;
    while ( got < BUF_SIZE ) {
        int r = ::read(oss->fd, buffer+got, BUF_SIZE-got);
        got += r;
    }
    emit dataAvailable( (short*)buf, BUF_SIZE/2 );
}
