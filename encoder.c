#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <lame.h>

#include "lametus.h"
#include "encoder.h"
#include "audio.h"

static void my_write(int,unsigned char *,int);

struct encoder *encoder_create(void)
{
	struct encoder *enc;

	enc = malloc(sizeof(struct encoder));
	if (!enc)
		return NULL;

	enc->lame_flags = lame_init();

	enc->server_addr.sin_family = AF_INET;
	enc->server_addr.sin_port = htons(8000);
	enc->server_addr.sin_addr.s_addr = INADDR_ANY;

	enc->passwd = strdup("hackme");
	enc->name = strdup("LAMEradio");
	enc->genre = strdup("lameness");
	enc->url = strdup("http://i.am/too.lame.to.configure.this");
	enc->pub = 0;

	enc->samplerate = 22050;
	enc->bitrate = 32000;
	enc->mono = 0; // have to default to stereo!
	enc->produced = 0;

	enc->file_name = 0;
	enc->streaming = 1;
	enc->file_fd = -1;

	return enc;
}

void encoder_init(struct audio_source *src,struct encoder *enc)
{
	char tmp[1024];

	/* Input configuration */
	lame_set_in_samplerate(enc->lame_flags,src->samplerate);
	lame_set_num_channels(enc->lame_flags,src->channels);

	/* Output configuration */
	lame_set_out_samplerate(enc->lame_flags,enc->samplerate);
	lame_set_brate(enc->lame_flags,enc->bitrate);
	if (!enc->mono)
		lame_set_mode(enc->lame_flags,1); /* J-Stereo mode */
	else
		lame_set_mode(enc->lame_flags,3); /* Mono mode */

	lame_init_params(enc->lame_flags);

	if(enc->file_name) {
		enc->file_fd = open(enc->file_name, O_WRONLY|O_CREAT|O_APPEND,S_IRWXU);
		if(enc->file_fd <0)
			fatal("Error opening file %s for writing", enc->file_name);
	}
	fprintf(stderr, "fsdfsdfsdfs %d", enc->server_addr);
	enc->server_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (enc->server_fd < 0)
		fatal("Error creating socket: %s",strerror(errno));

	if (connect(enc->server_fd,(struct sockaddr *)&enc->server_addr,
				sizeof(struct sockaddr_in)) < 0)
		fatal("Failed to connect to server: %s",strerror(errno));

	snprintf(tmp,1024,"%s\n",enc->passwd);
	my_write(enc->server_fd,tmp,strlen(tmp));
	snprintf(tmp,1024,"icy-br:%d\n",enc->bitrate);
	my_write(enc->server_fd,tmp,strlen(tmp));
	snprintf(tmp,1024,"icy-name:%s\n",enc->name);
	my_write(enc->server_fd,tmp,strlen(tmp));
	snprintf(tmp,1024,"icy-genre:%s\n",enc->genre);
	my_write(enc->server_fd,tmp,strlen(tmp));
	snprintf(tmp,1024,"icy-url:%s\n",enc->url);
	my_write(enc->server_fd,tmp,strlen(tmp));
	snprintf(tmp,1024,"icy-pub:%d\n",enc->pub);
	my_write(enc->server_fd,tmp,strlen(tmp));

	fprintf(stderr,"Encoder initialized:\n");
	fprintf(stderr," Output samplerate: %d Bitrate: %dkbps\n",
			enc->samplerate,enc->bitrate);
	if(enc->file_name)
		fprintf(stderr, " Filename: %s\n", enc->file_name);
 	if(enc->server_fd != -1)	
		fprintf(stderr," Server: %s:%d\n",
				inet_ntoa(enc->server_addr.sin_addr),
				ntohs(enc->server_addr.sin_port));
	fprintf(stderr," Stream name: '%s'\n",enc->name);
	fprintf(stderr," Genre: %s URL: %s Public: %d\n\n",enc->genre,enc->url,
			enc->pub);
}

void encoder_run(struct encoder *enc,short *inbuf,int nsamples)
{
	int r;
	short *tmpbuf;
	unsigned char outbuf[10240];

	tmpbuf = malloc(nsamples*sizeof(short)*2);
	if (!tmpbuf)
		fatal("Out of memory");

	memcpy(tmpbuf,inbuf,nsamples*sizeof(short)*2);

	r = lame_encode_buffer_interleaved(enc->lame_flags,tmpbuf,nsamples,outbuf,
			10240);

	if (r < 0)
	{
		switch (r)
		{
			case -1:
				fatal("Encoder problem: mp3buffer was too small");
			case -2:
				fatal("Encoder problem: malloc() problem");
			case -3:
				fatal("Encoder problem: lame_init_params() not called");
			case -4:
				fatal("Encoder problem: psycho acoustic problems");
			default:
				fatal("Encoder problem: unknown problem (%d)",r);
		}
	}

	free(tmpbuf);

	if(enc->file_fd != -1)
		my_write(enc->file_fd,outbuf,r);
	if(enc->server_fd != -1)
		my_write(enc->server_fd,outbuf,r);
	enc->produced += r;
}

static void my_write(int fd,unsigned char *data,int bytes)
{
	int written = 0;
	int r;

	while (written < bytes)
	{
		r = write(fd,data+written,bytes-written);

		if (r < 0)
			fatal("Error writing data: %s",strerror(errno));
		else if (!r)
			fatal("Lost connection to server");

		written += r;
	}
}
