#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtCore/QString>
#include "audiosource.h"
#include "settings.h"
#include "encoder.h"
#include "lametus.h"

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
    void errorMessage(QString msg);
    void audioSourceCreated(AudioSource *src);
    void audioSourceUpdated(AudioSource *src);
    void encoderCreated(Encoder *enc);
    void encoderUpdated(Encoder *enc);

private:
    Ui::MainWindowClass *ui;
    Lametus lametus;
};

#endif // MAINWINDOW_H
