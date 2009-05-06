#include "encoder.h"

Encoder::Encoder(QObject * parent) : QObject(parent)
{
    lame_flags = lame_init();

    /*
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
*/
    pub = 0;

    samplerate = 22050;
    bitrate = 32000;
    mono = 0; // have to default to stereo!
    produced = 0;

    file_name = 0;
    streaming = 1;
    file_fd = -1;

}

Encoder::~Encoder()
{
    if(shout)
        shout_close(shout);

    shout_shutdown();
}

void Encoder::connectToSource(AudioSource *src) {
    /* Input configuration */
    lame_set_in_samplerate(lame_flags,src->getSamplerate());
    lame_set_num_channels(lame_flags,src->getChannels());
    if (shout_open(shout) == SHOUTERR_SUCCESS) {
        qDebug("Connected to server...\n");
    } else {
         qDebug("Error connecting: %s\n", shout_get_error(shout));
    }
}

void Encoder::Init(QString server, QString encodername, QString pass, QString genre, QString url, int pub, unsigned int samplerate, int bitrate, int channels) {
    this->encodername = encodername;
    this->server = server;
    this->passwd = pass;
    this->genre = genre;
    this->url = url;
    this->pub = pub;
    this->samplerate = samplerate;
    this->bitrate = bitrate;
    this->mono = channels == 1;

    /* Output configuration */
    lame_set_out_samplerate(lame_flags,samplerate);
    lame_set_brate(lame_flags,bitrate);
    if (channels != 0)
        lame_set_mode(lame_flags, JOINT_STEREO); /* J-Stereo mode */
    else
        lame_set_mode(lame_flags, MONO); /* Mono mode */

    lame_init_params(lame_flags);
    shout_init();

    if (!(shout = shout_new())) {
        qDebug("Could not allocate shout_t\n");
        return;
    }

    if (shout_set_host(shout, server.toAscii().data()) != SHOUTERR_SUCCESS) {
        qDebug("Error setting hostname: %s\n", shout_get_error(shout));
        return;
    }

    if (shout_set_protocol(shout, SHOUT_PROTOCOL_HTTP) != SHOUTERR_SUCCESS) {
        qDebug("Error setting protocol: %s\n", shout_get_error(shout));
        return;
    }

    if (shout_set_port(shout, 8000) != SHOUTERR_SUCCESS) {
        qDebug("Error setting port: %s\n", shout_get_error(shout));
        return;
    }

    if (shout_set_password(shout, passwd.toAscii().data()) != SHOUTERR_SUCCESS) {
        qDebug("Error setting password: %s\n", shout_get_error(shout));
        return;
    }
    if (shout_set_mount(shout, "/example.mp3") != SHOUTERR_SUCCESS) {
        qDebug("Error setting mount: %s\n", shout_get_error(shout));
        return;
    }

    if (shout_set_user(shout, "source") != SHOUTERR_SUCCESS) {
        qDebug("Error setting user: %s\n", shout_get_error(shout));
        return;
    }
    if (shout_set_format(shout, SHOUT_FORMAT_MP3) != SHOUTERR_SUCCESS) {
        qDebug("Error setting format: %s\n", shout_get_error(shout));
        return;
    }

}

void Encoder::Run(short *,int) {
}

QString Encoder::getServer() {
  return server;
}
