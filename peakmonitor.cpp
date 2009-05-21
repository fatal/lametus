#include <stdlib.h>
#include "audiosource.h"
#include "peakmonitor.h"

PeakMonitor::PeakMonitor(QObject * parent) : QObject(parent)
{
}

PeakMonitor::~PeakMonitor()
{
}

void PeakMonitor::connectToSource(AudioSource *src) {
    connect( src, SIGNAL( dataAvailable(short*, int)),
             this, SLOT( dataAvailable(short*, int)) );
}
void PeakMonitor::dataAvailable( short* buffer, int len )
{
    int left=0, right=0;
    int i;
    for( i=0; i<len; i+=2 ) {
        int l = abs( buffer[i] );
        int r = abs( buffer[i+1] );
        if( l > left ) left = l;
        if( r > right ) right = r;
    }
    emit peakValueChanged( left, right ); 
}
