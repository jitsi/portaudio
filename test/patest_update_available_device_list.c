#include <stdio.h>
#include <assert.h>

#include "portaudio.h"

void printDevices()
{
    int deviceCount = Pa_GetDeviceCount();
    int i;

    for( i=0; i < deviceCount; ++i ){
        const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);
        const PaHostApiInfo *hostApiInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );

        assert( deviceInfo != 0 );

        printf( "%2d %s: %s, %s\n", i, hostApiInfo->name, deviceInfo->name, deviceInfo->deviceUID );
        fflush(stdout);
    }
}

static void devicesChangedCallback(void* p)
{
    (void)p;

    printf( "Portaudio device list have changed!\n" );
    fflush(stdout);
}

int main(int argc, char* argv[])
{
    Pa_Initialize();

    Pa_SetDevicesChangedCallback(NULL, devicesChangedCallback);

    for(;;){
        printDevices();
        
        printf( "press [enter] to update the device list. or q + [enter] to quit.\n" );
        fflush(stdout);
        char ch = getchar();
        if( ch == 'q' )
            break;
    
        Pa_UpdateAvailableDeviceList();
    }

    Pa_Terminate();

	return 0;
}

