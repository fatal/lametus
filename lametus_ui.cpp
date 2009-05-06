#include "lametus_ui.h"
// Interface class, no implementation

LametusUI::LametusUI() {};
LametusUI::~LametusUI() {};
void LametusUI::errorMessage(QString msg) {
  qDebug("Error: " + msg.toAscii());
}
void LametusUI::audioSourceCreated(AudioSource *src) {}
void LametusUI::audioSourceUpdated(AudioSource *src) {}
void LametusUI::encoderCreated(Encoder *enc) {}
void LametusUI::encoderUpdated(Encoder *enc) {}
