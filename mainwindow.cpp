#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
  ui->setupUi(this);
  connect( &lametus, SIGNAL( audioSourceCreated( AudioSource* ) ),
        this, SLOT( audioSourceCreated( AudioSource* ) ) );
  connect( &lametus, SIGNAL( audioSourceUpdated( AudioSource* ) ),
        this, SLOT( audioSourceUpdated( AudioSource* ) ) );
  connect( &lametus, SIGNAL( encoderCreated( Encoder* ) ),
        this, SLOT( encoderCreated( Encoder* ) ) );
  connect( &lametus, SIGNAL( errorMessage( QString ) ),
        this, SLOT( errorMessage( QString ) ) );
  lametus.initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errorMessage(QString msg) {
  // LametusUI::errorMessage(msg);
  QMessageBox msgbox;
  msgbox.setText(msg);
  msgbox.exec();
}

void MainWindow::audioSourceCreated(AudioSource *src) {
  audioSourceUpdated(src);
}

void MainWindow::audioSourceUpdated(AudioSource *src) {
  audio_source_status_t status = src->getStatus();
  if(status==AUDIO_SOURCE_OK)
    ui->audioSourceStatus->setText("OK");
  if(status==AUDIO_SOURCE_FAIL)
    ui->audioSourceStatus->setText("FAIL");
  if(status==AUDIO_SOURCE_UNKNOWN)
    ui->audioSourceStatus->setText("Unknown");

  ui->audioSourceSamplerate->setText(QString().setNum(src->getSamplerate()));
  ui->audioSourceChannels->setText(QString().setNum(src->getChannels()));
}
void MainWindow::encoderCreated(Encoder *enc) {
  ui->encoderList->addItem(enc->getServer());
}
void MainWindow::encoderUpdated(Encoder *enc) {
  // TODO
}
