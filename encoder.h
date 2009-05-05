#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <netinet/in.h>

#include <lame.h>

struct encoder
{
	lame_global_flags *lame_flags;

	char *passwd;
	char *name;
	char *genre;
	char *url;
	char *file_name;
	int pub;

	int samplerate;
	int bitrate;
	int mono;
	int produced;
	int streaming;

	struct sockaddr_in server_addr;
	int server_fd;
	int file_fd;
};

struct audio_source;

struct encoder *encoder_create(void);
void encoder_init(struct audio_source *,struct encoder *);
void encoder_run(struct encoder *,short *,int);

#endif
