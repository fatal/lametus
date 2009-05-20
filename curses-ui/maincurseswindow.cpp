/*
 * MainCursesWindow.cpp
 *
 *  Created on: 5.5.2009
 *      Author: fatal
 */
#include "maincurseswindow.h"
#include "cursesapplication.h"
#include "cursessetbar.h"
#include "vumeter.h"

MainCursesWindow::MainCursesWindow( CursesControl* aParent ) : 
	CursesWindow( aParent )
{
    iVUMeter = new CursesVUMeter(this);
    iTargetLevel = new CursesSetBar(this, QString("test"), 10);
    iExtraLevel = new CursesSetBar(this, QString("test2"), 10);
    iTest = new CursesBar(this, QString("test2"), 10);
    connect( iTargetLevel, SIGNAL( valueChanged(int) ),
             iTest, SLOT( setValue(int) ) );
    iVUMeter->setRect(0, 0, 80, 3);
    iTargetLevel->setRect(0, 4, 80, 1);
    iTest->setRect(0, 5, 80, 1);
    iExtraLevel->setRect(0, 7, 80, 1);

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

MainCursesWindow::~MainCursesWindow()
{
    delete iVUMeter;
    delete iTargetLevel;
    delete iExtraLevel;
    delete iTest;
}

CursesControl* MainCursesWindow::control(int index)
{
    switch (index) {
    case 0: return iVUMeter;
    case 1: return iTargetLevel;
    case 2: return iTest;
    case 3: return iExtraLevel;
    default: return 0;
    }
}
int MainCursesWindow::controlCount()
{
    return 4;
}

void MainCursesWindow::draw()
{
    // decoration etc stuff goes here if anything.. 
    CursesWindow::draw();
}
bool MainCursesWindow::handleInput( int ch )
{
    if ( ch == 9 ) {
        CursesApplication::quit();
        return true;
    }
    return CursesWindow::handleInput( ch );
}

void MainCursesWindow::errorMessage(QString msg) {
}

void MainCursesWindow::audioSourceCreated(AudioSource *src) {
  audioSourceUpdated(src);
}

void MainCursesWindow::audioSourceUpdated(AudioSource *src) {
  audio_source_status_t status = src->getStatus();
    
    /*
     if(status==AUDIO_SOURCE_OK);
     else if(status==AUDIO_SOURCE_FAIL);
     else if(status==AUDIO_SOURCE_UNKNOWN);
    */
}
void MainCursesWindow::encoderCreated(Encoder *enc) {
}
void MainCursesWindow::encoderUpdated(Encoder *enc) {
}
