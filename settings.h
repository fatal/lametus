#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QSettings>
#include <QtCore/QStringList>
#include <QDebug>

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings(QObject * parent);
    bool Read(QString filename);
signals:
    void sourceFound(unsigned int samplerate, int channels, QString device);
    void encoderFound(QString server, QString name, QString pass, QString genre, QString url, int pub, unsigned int samplerate, int bitrate, int channels);
private:
    void configureSource(QSettings * settings);
};

#endif // SETTINGS_H
