#include "lametus.h"

Lametus::Lametus(QObject *parent) : QObject(parent)
{
    audioSource = 0;
    ui = 0;
}

bool Lametus::initialize(LametusUI *lameUi)
{
    ui = lameUi;

    Settings *settings = new Settings(this);
    connect(settings, SIGNAL(sourceFound(uint,int,QString)),
            this, SLOT(sourceFound(uint,int,QString)));
    connect(settings, SIGNAL(encoderFound(QString,QString,QString,QString,QString,int,uint,int,int)),
            this, SLOT(encoderFound(QString,QString,QString,QString,QString,int,uint,int,int)));
    if(!settings->Read("./lametus.ini")) {
      ui->errorMessage("Could not open settings file");
        return FALSE;
    }
    if(!audioSource) {
      ui->errorMessage("No audio source!");
      return FALSE;
    }
    for(int e=0;e<encoders.size();e++) {
        encoders.at(e)->connectToSource(audioSource);
    }
    return TRUE;
}

Lametus::~Lametus()
{

}

void Lametus::sourceFound(unsigned int samplerate, int channels, QString device) {
    audioSource = new AudioSource(this);
    ui->audioSourceCreated(audioSource);
    if(!audioSource->Init(samplerate, channels, device)) {
	ui->errorMessage("Audio source init failed.");
    }
    ui->audioSourceUpdated(audioSource);
}

void Lametus::encoderFound(QString server, QString name, QString pass, QString genre, QString url, int pub, unsigned int samplerate, int bitrate, int channels) {
    Encoder * enc = new Encoder(this);
    enc->Init(server, name, pass, genre, url, pub, samplerate, bitrate, channels);
    encoders.append(enc);
    ui->encoderCreated(enc);
}
