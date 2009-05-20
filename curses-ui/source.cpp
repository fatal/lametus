#include "source.h"
#include "cursescontext.h"

CursesAudioSource::CursesAudioSource(CursesControl* aParent ) :
	CursesControl( aParent )
{
}

CursesAudioSource::~CursesAudioSource()
{
}

void CursesAudioSource::draw()
{
    if ( iAudioSource ) {
        CursesContext& cc = context();
        cc.moveTo( 0, 0 );
        cc.setColor( 1 );
        unsigned int rate = iAudioSource->getSamplerate();
        int channels = iAudioSource->getChannels();
        QString tmp = QString("Channels: %1, Rate: %2 Hz ").arg(channels, 2).arg(rate, 5);
        cc.drawString(tmp);

    }
    CursesControl::draw();
}

void CursesAudioSource::audioSourceUpdated( AudioSource* aAudioSource )
{
    iAudioSource = aAudioSource;
    markDirty();
}

