#ifndef LAMETUS_UI_H
#define LAMETUS_UI_H

#include <QtCore/QString>
#include <audiosource.h>
#include <settings.h>
#include <encoder.h>

class LametusUI
{
public:
  LametusUI();
  virtual ~LametusUI();

  virtual void errorMessage(QString msg)=0;
  // Called when audio source has been created
  virtual void audioSourceCreated(AudioSource *src) = 0;
  // Called when audio source's status has been updated.
  virtual void audioSourceUpdated(AudioSource *src) = 0;
  // Called when a new encoder has been created
  virtual void encoderCreated(Encoder *enc) = 0;
  // Called when a new encoder has been created
  virtual void encoderUpdated(Encoder *enc) = 0;
private:
};

#endif // LAMETUSUI_H
