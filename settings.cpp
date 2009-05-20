#include "settings.h"

Settings::Settings(QObject * parent) : QObject(parent)
{
}
bool Settings::Read(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    if(settings.status() != QSettings::NoError)
        return FALSE;

    QStringList groups = settings.childGroups();

    for (int i = 0; i < groups.size(); ++i) {
        if(groups.at(i) == "source") {
            settings.beginGroup(groups.at(i));
            emit sourceFound(settings.value("type", "oss").toString(), settings.value("samplerate", 44100).toInt(), settings.value("channels", 2).toInt(), settings.value("device", "/dev/dsp").toString());
            settings.endGroup();
        } else if(groups.at(i) == "encoder") {
            settings.beginGroup(groups.at(i));
            emit encoderFound(settings.value("server", "127.0.0.1").toString(),
                              settings.value("name", "Name not set").toString(),
                              settings.value("password", "reallame").toString(),
                              settings.value("genre", "other").toString(),
                              settings.value("url", "http://lametus/").toString(),
                              settings.value("public", 0).toInt(),
                              settings.value("samplerate", 0).toInt(),
                              settings.value("bitrate", 44100).toInt(),
                              settings.value("channels", 2).toInt());
            settings.endGroup();
        }
    }
    return TRUE;
}
