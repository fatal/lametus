#ifndef __AUDIO_H__
#define __AUDIO_H__

struct audio_source
{
	char *devname;
	unsigned int samplerate;
	int channels;

	void *internal_data;
};

struct audio_source *audio_source_create(void);
void audio_source_init(struct audio_source *);
void audio_source_read(struct audio_source *,unsigned char *,int);

#endif
