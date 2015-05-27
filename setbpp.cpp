// set16Bpp.cpp : Sets the bpp to 16-bit
//
#include "stdafx.h"
#include < windows.h >

int _tmain(int argc, _TCHAR* argv[])
{
	int deviceIndex=0;
	int result;
	DWORD bpp=16;

	do
	{
		PDISPLAY_DEVICE displayDevice = new DISPLAY_DEVICE();
		displayDevice->cb = sizeof(DISPLAY_DEVICE);

		result = EnumDisplayDevices(NULL, 
			deviceIndex++, displayDevice, 0);
		if (displayDevice->StateFlags & DISPLAY_DEVICE_ACTIVE)
		{
			PDISPLAY_DEVICE monitor = new DISPLAY_DEVICE();
			monitor->cb = sizeof(DISPLAY_DEVICE);

			EnumDisplayDevices(displayDevice->DeviceName, 
				0, monitor, 0);
			
			PDEVMODE dm = new DEVMODE();
			
			if ( EnumDisplaySettings(displayDevice->DeviceName,
				ENUM_CURRENT_SETTINGS, dm) )
			{
				dm->dmBitsPerPel=(DWORD)bpp;
				ChangeDisplaySettingsEx(displayDevice->DeviceName, dm,  \
                                     NULL, (CDS_GLOBAL | CDS_UPDATEREGISTRY | CDS_RESET), NULL);
			}
		}
	} while (result);
	return 0;
}

