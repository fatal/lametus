#include "lametus.h"

Lametus::Lametus(QObject *parent) : QObject(parent)
{
    audioSource = 0;

    Settings *settings = new Settings(this);
    connect(settings, SIGNAL(sourceFound(uint,int,QString)),
            this, SLOT(sourceFound(uint,int,QString)));
    connect(settings, SIGNAL(encoderFound(QString,QString,QString,QString,QString,int,uint,int,int)),
            this, SLOT(encoderFound(QString,QString,QString,QString,QString,int,uint,int,int)));
    if(!settings->Read("/home/cosmo/qt-creator-workspace/lametus-qt/lametus.ini")) {
        QMessageBox msg;
        msg.setText("Could not open settings file");
        msg.exec();
        return;
    }
    if(!audioSource) {
        QMessageBox msg;
        msg.setText("No audio source!");
        msg.exec();
        return;
    }
    for(int e=0;e<encoders.size();e++) {
        encoders.at(e)->connectToSource(audioSource);
    }
}

Lametus::~Lametus()
{
    delete ui;
}

void Lametus::sourceFound(unsigned int samplerate, int channels, QString device) {
    audioSource = new AudioSource(this);
    if(audioSource->Init(samplerate, channels, device)) {
        ui->audioSourceStatus->setText("Initialized");
        ui->audioSourceSamplerate->setText(QString().setNum(audioSource->getSamplerate()));
        ui->audioSourceChannels->setText(QString().setNum(audioSource->getChannels()));
    } else {
        ui->audioSourceStatus->setText("Init FAILED");
        QMessageBox msg;
        msg.setText("Audio source init failed.");
        msg.exec();
    }
}
void Lametus::encoderFound(QString server, QString name, QString pass, QString genre, QString url, int pub, unsigned int samplerate, int bitrate, int channels) {
    qDebug("Encoder found");
    Encoder * enc = new Encoder(this);
    enc->Init(server, name, pass, genre, url, pub, samplerate, bitrate, channels);
    encoders.append(enc);
    ui->encoderList->addItem(QString(server));
}
