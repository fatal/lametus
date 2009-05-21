#include "encoder.h"
#include <iostream>

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
      qDebug("Error connecting to %s: %s\n", server.toAscii().data(), shout_get_error(shout));
    }
    connect( src, SIGNAL( dataAvailable(short*, int)),
             this, SLOT( dataAvailable(short*, int)) );
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
    if (channels != 1)
        lame_set_mode(lame_flags, JOINT_STEREO); /* J-Stereo mode */
    else
        lame_set_mode(lame_flags, MONO); /* Mono mode */

    lame_init_params(lame_flags);
    shout_init();

    QString serverHost = "";
    QString serverPort = "8000";
    if(server.contains(":")) {
      serverHost = server.split(":")[0];
      serverPort = server.split(":")[1];
    }
    if (!(shout = shout_new())) {
        qDebug("Could not allocate shout_t\n");
        return;
    }

    if (shout_set_host(shout, serverHost.toAscii().data()) != SHOUTERR_SUCCESS) {
        qDebug("Error setting hostname: %s\n", shout_get_error(shout));
        return;
    }

    if (shout_set_protocol(shout, SHOUT_PROTOCOL_HTTP) != SHOUTERR_SUCCESS) {
        qDebug("Error setting protocol: %s\n", shout_get_error(shout));
        return;
    }

    if (shout_set_port(shout, serverPort.toInt()) != SHOUTERR_SUCCESS) {
        qDebug("Error setting port: %s\n", shout_get_error(shout));
        return;
    }

    qDebug("Server: %s:%d", serverHost.toAscii().data(), serverPort.toInt());
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
void Encoder::dataAvailable( short* buffer, int len )
{
    unsigned char outbuf[10240];
    std::cerr << "Feeding: " << len << " shorts\n";
    int r = lame_encode_buffer_interleaved(lame_flags, buffer, len/2, outbuf, 10240);
    std::cerr << r << " available\n";
    if ( r > 0 ) {
        int r2 = shout_send( shout, outbuf, r );
        std::cerr << "Apparently sent: " << r2 << "\n";
    }
}

QString Encoder::getServer() {
  return server;
}
