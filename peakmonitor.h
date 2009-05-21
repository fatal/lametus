#ifndef PEAKMONITOR_H
#define PEAKMONITOR_H

#include <QtCore/QObject>

class AudioSource;

class PeakMonitor : public QObject
{
    Q_OBJECT
public:
    PeakMonitor(QObject * parent);
    ~PeakMonitor();
    void connectToSource(AudioSource * src);
public slots:
    void dataAvailable(short*, int);
signals:
    void peakValueChanged(int left, int right);
private:
};

#endif // ENCODER_H
