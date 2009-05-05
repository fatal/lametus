#ifndef ENCODER_H
#define ENCODER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <shout/shout.h>
#include <lame.h>

#include "audiosource.h"

class Encoder : public QObject
{
public:
    Encoder(QObject * parent);
    ~Encoder();
    void Init(QString server, QString name, QString pass, QString genre, QString url, int pub, unsigned int samplerate, int bitrate, int channels);
    void Run(short *,int);
    void connectToSource(AudioSource * src);
private:
    lame_global_flags *lame_flags;

    QString passwd;
    QString encodername;
    QString genre;
    QString url;
    char *file_name;
    int pub;

    int samplerate;
    int bitrate;
    int mono;
    int produced;
    int streaming;

//    struct sockaddr_in server_addr;
    int server_fd;
    int file_fd;
    shout_t *shout;

};

#endif // ENCODER_H
