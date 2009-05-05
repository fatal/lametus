#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtCore/QString>
#include <audiosource.h>
#include <settings.h>
#include <encoder.h>

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void sourceFound(unsigned int samplerate, int channels, QString device);
    void encoderFound(QString server, QString name, QString pass, QString genre, QString url, int pub, unsigned int samplerate, int bitrate, int channels);
private:
    Ui::MainWindowClass *ui;
    AudioSource *audioSource;
    QList<Encoder*> encoders;
};

#endif // MAINWINDOW_H
