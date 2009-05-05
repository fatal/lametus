#ifndef __LAMETUS_H__
#define __LAMETUS_H__

void fatal(const char *,...);

#define MAX_ENCODERS 16

extern int num_encoders;
extern struct encoder *encoders[MAX_ENCODERS];
extern struct audio_source *source;

#endif
