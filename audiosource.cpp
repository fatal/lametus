#include "audiosource.h"

AudioSource::AudioSource(QObject * parent) : QObject(parent)
{
    internal_data = malloc(sizeof(struct audio_oss_internal));
    if (!internal_data)
        qDebug("Out of memory");

    devname = strdup(OSS_DEFAULT_DEVNAME);
    samplerate = 44100;
    channels = 2;
}

AudioSource::~AudioSource()
{
    struct audio_oss_internal *oss =
            (struct audio_oss_internal *)internal_data;
    if(oss && oss->fd >= 0)
        close(oss->fd);
    qDebug("Audio source closed");
}

bool AudioSource::Init(unsigned int samplerate, int channels, QString device)
{
    this->samplerate = samplerate;
    this->channels = channels;
    this->devname = device;

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
    return TRUE;
}

unsigned int AudioSource::getSamplerate() {
    return samplerate;
}
int AudioSource::getChannels() {
    return channels;
}
