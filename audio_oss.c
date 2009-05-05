#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "lametus.h"
#include "audio.h"

#include <linux/soundcard.h>

#define OSS_DEFAULT_DEVNAME "/dev/dsp"

struct audio_oss_internal
{
	int fd;
};

struct audio_source *audio_source_create(void)
{
	struct audio_source *src;

	src = malloc(sizeof(struct audio_source));
	if (!src)
		fatal("Out of memory");

	src->internal_data = malloc(sizeof(struct audio_oss_internal));
	if (!src->internal_data)
		fatal("Out of memory");

	src->devname = strdup(OSS_DEFAULT_DEVNAME);
	src->samplerate = 44100;
	src->channels = 2;

	return src;
}

void audio_source_init(struct audio_source *src)
{
	int tmp;
	struct audio_oss_internal *oss =
		(struct audio_oss_internal *)src->internal_data;

	oss->fd = open(src->devname,O_RDONLY);
	if (oss->fd < 0)
		fatal("Could not open audio device '%s': %s",src->devname,strerror(errno));

	tmp = AFMT_S16_LE;

	if (ioctl(oss->fd,SNDCTL_DSP_SETFMT,&tmp) < 0)
		fatal("Could not set sample format: %s",strerror(errno));

	tmp = src->channels - 1;

	if (ioctl(oss->fd,SNDCTL_DSP_STEREO,&tmp) < 0)
		fatal("Could not set number of channels: %s",strerror(errno));

	tmp = src->samplerate;

	if (ioctl(oss->fd,SNDCTL_DSP_SPEED,&tmp) < 0)
		fatal("Could not set samplerate: %s",strerror(errno));

	fprintf(stderr,"OSS Audio source initialized:\n");
	fprintf(stderr," Device: '%s'\n",src->devname);
	fprintf(stderr," Samplerate: %d Channels: %d\n\n",src->samplerate,
			src->channels);
}

void audio_source_read(struct audio_source *src,unsigned char *buffer,int bytes)
{
	int gotten = 0;
	int r;
	struct audio_oss_internal *oss =
		(struct audio_oss_internal *)src->internal_data;

	while (gotten < bytes)
	{
		r = read(oss->fd,buffer+gotten,bytes-gotten);

		if (r < 0)
			fatal("Error reading audio data: %s",strerror(errno));
		else if (!r)
			fatal("Error reading audio data: got 0 bytes");

		gotten += r;
	}
}
