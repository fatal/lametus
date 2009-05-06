#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtCore/QString>
#include "audiosource.h"
#include "settings.h"
#include "encoder.h"
#include "lametus.h"
#include "lametus_ui.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow, LametusUI
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void errorMessage(QString msg);
    virtual void audioSourceCreated(AudioSource *src);
    virtual void audioSourceUpdated(AudioSource *src);
    virtual void encoderCreated(Encoder *enc);
    virtual void encoderUpdated(Encoder *enc);
public slots:

private:
    Ui::MainWindowClass *ui;
    Lametus lametus;
};

#endif // MAINWINDOW_H
