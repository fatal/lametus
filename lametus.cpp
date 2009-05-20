#include "lametus.h"
#include "audiosource_oss.h"
#include "audiosource_pulse.h"

Lametus::Lametus(QObject *parent) : QObject(parent)
{
    audioSource = 0;
}

bool Lametus::initialize()
{
    Settings *settings = new Settings(this);
    connect(settings, SIGNAL(sourceFound(QString,uint,int,QString)),
            this, SLOT(sourceFound(QString,uint,int,QString)));
    connect(settings, SIGNAL(encoderFound(QString,QString,QString,QString,QString,int,uint,int,int)),
            this, SLOT(encoderFound(QString,QString,QString,QString,QString,int,uint,int,int)));
    if(!settings->Read("./lametus.ini")) {
      emit errorMessage("Could not open settings file");
        return FALSE;
    }
    if(!audioSource) {
      emit errorMessage("No audio source!");
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

void Lametus::sourceFound(QString type, unsigned int samplerate, int channels, QString device) {
    if ( type == "oss" ) {
        AudioSourceOss* source = new AudioSourceOss(this);
        emit audioSourceCreated(source);
        if(!source->Init(samplerate, channels, device)) {
            emit errorMessage("Audio source init failed.");
        }
        audioSource = source;
    }
    else if ( type == "pulse" ) {
        AudioSourcePulse* source = new AudioSourcePulse(this);
        emit audioSourceCreated(source);
        if(!source->Init(samplerate, channels)) {
            emit errorMessage("Audio source init failed.");
        }
        audioSource = source;
    }
    
    emit audioSourceUpdated( audioSource );
}

void Lametus::encoderFound(QString server, QString name, QString pass, QString genre, QString url, int pub, unsigned int samplerate, int bitrate, int channels) {
    Encoder * enc = new Encoder(this);
    enc->Init(server, name, pass, genre, url, pub, samplerate, bitrate, channels);
    encoders.append(enc);
    emit encoderCreated( enc );
}
