#ifndef LAMETUS_H
#define LAMETUS_H

#include <QtCore/QString>
#include <audiosource.h>
#include <settings.h>
#include <encoder.h>

class PeakMonitor;

class Lametus : public QObject
{
    Q_OBJECT

public:
    Lametus(QObject *parent = 0);
    ~Lametus();
    // Loads settings, creates source and encoders
    // returns FALSE if fails
    bool initialize();

public slots:
    void sourceFound(QString type, unsigned int samplerate, int channels, QString device);
    void encoderFound(QString server, QString name, QString pass, 
		      QString genre, QString url, int pub, 
		      unsigned int samplerate, int bitrate, int channels);

signals:
    void audioSourceCreated(AudioSource*);
    void audioSourceUpdated(AudioSource*);
    void encoderCreated(Encoder*);
    void errorMessage(QString);
    void peakMonitorCreated(PeakMonitor*);
private:
    AudioSource *audioSource;
    QList<Encoder*> encoders;
    PeakMonitor *peakMonitor;
};

#endif // LAMETUS_H
