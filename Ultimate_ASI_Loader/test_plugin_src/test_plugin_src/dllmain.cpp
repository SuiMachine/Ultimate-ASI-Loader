#include "stdafx.h"
#include <windows.h>
#include "stdio.h"
#include <Shlobj.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
using namespace std;

HANDLE HndThread;



DWORD WINAPI Thread(LPVOID param)
{
  		char			moduleName[MAX_PATH];
		char			preparedPath[128];	// stores scripts\*exename*\settings.ini
		char*			tempPointer;

		GetModuleFileName(NULL, moduleName, MAX_PATH);
		tempPointer = strrchr(moduleName, '.');
		*tempPointer  = '\0';

		tempPointer = strrchr(moduleName, '\\');
		strncpy(preparedPath, "scripts", 8);
		mkdir(preparedPath);
		strcat(preparedPath, tempPointer);
		mkdir(preparedPath);
		strcat(preparedPath, "\\settings.ini");


ofstream settings_ini;
settings_ini.open (preparedPath,ios::out | ios::in | ios::binary | ios::trunc);
char hexData[700] = {
    0x3B, 0x20, 0x54, 0x68, 0x69, 0x73, 0x20, 0x66,
    0x69, 0x6C, 0x65, 0x20, 0x6E, 0x65, 0x65, 0x64,
    0x73, 0x20, 0x74, 0x6F, 0x20, 0x67, 0x6F, 0x20,
    0x69, 0x6E, 0x74, 0x6F, 0x20, 0x27, 0x73, 0x63,
    0x72, 0x69, 0x70, 0x74, 0x73, 0x5C, 0x2A, 0x79,
    0x6F, 0x75, 0x72, 0x5F, 0x65, 0x78, 0x65, 0x5F,
    0x6E, 0x61, 0x6D, 0x65, 0x2A, 0x20, 0x66, 0x6F,
    0x6C, 0x64, 0x65, 0x72, 0x20, 0x69, 0x6E, 0x20,
    0x6F, 0x72, 0x64, 0x65, 0x72, 0x20, 0x74, 0x6F,
    0x20, 0x77, 0x6F, 0x72, 0x6B, 0x20, 0x63, 0x6F,
    0x72, 0x72, 0x65, 0x63, 0x74, 0x6C, 0x79, 0x21,
    0x0D, 0x0A, 0x0D, 0x0A, 0x5B, 0x45, 0x78, 0x63,
    0x6C, 0x75, 0x73, 0x69, 0x76, 0x65, 0x53, 0x65,
    0x74, 0x73, 0x5D, 0x0D, 0x0A, 0x3B, 0x20, 0x53,
    0x65, 0x74, 0x20, 0x74, 0x6F, 0x20, 0x30, 0x20,
    0x69, 0x66, 0x20, 0x79, 0x6F, 0x75, 0x20, 0x64,
    0x6F, 0x6E, 0x27, 0x74, 0x20, 0x77, 0x61, 0x6E,
    0x74, 0x20, 0x70, 0x6C, 0x75, 0x67, 0x69, 0x6E,
    0x73, 0x20, 0x74, 0x6F, 0x20, 0x62, 0x65, 0x20,
    0x6C, 0x6F, 0x61, 0x64, 0x65, 0x64, 0x20, 0x62,
    0x79, 0x20, 0x74, 0x68, 0x69, 0x73, 0x20, 0x45,
    0x78, 0x65, 0x63, 0x75, 0x74, 0x61, 0x62, 0x6C,
    0x65, 0x0D, 0x0A, 0x3B, 0x20, 0x43, 0x6F, 0x6D,
    0x6D, 0x65, 0x6E, 0x74, 0x20, 0x6F, 0x75, 0x74,
    0x20, 0x74, 0x68, 0x65, 0x20, 0x65, 0x6E, 0x74,
    0x72, 0x79, 0x20, 0x77, 0x69, 0x74, 0x68, 0x20,
    0x3B, 0x20, 0x69, 0x66, 0x20, 0x79, 0x6F, 0x75,
    0x20, 0x64, 0x6F, 0x6E, 0x27, 0x74, 0x20, 0x77,
    0x61, 0x6E, 0x74, 0x20, 0x74, 0x68, 0x69, 0x73,
    0x20, 0x45, 0x78, 0x65, 0x63, 0x75, 0x74, 0x61,
    0x62, 0x6C, 0x65, 0x20, 0x74, 0x6F, 0x20, 0x68,
    0x61, 0x76, 0x65, 0x20, 0x69, 0x74, 0x73, 0x20,
    0x6F, 0x77, 0x6E, 0x20, 0x70, 0x6C, 0x75, 0x67,
    0x69, 0x6E, 0x20, 0x6C, 0x6F, 0x61, 0x64, 0x69,
    0x6E, 0x67, 0x20, 0x70, 0x6F, 0x6C, 0x69, 0x63,
    0x79, 0x0D, 0x0A, 0x3B, 0x20, 0x54, 0x68, 0x69,
    0x73, 0x20, 0x65, 0x6E, 0x74, 0x72, 0x79, 0x20,
    0x6F, 0x76, 0x65, 0x72, 0x72, 0x69, 0x64, 0x65,
    0x73, 0x20, 0x4C, 0x6F, 0x61, 0x64, 0x50, 0x6C,
    0x75, 0x67, 0x69, 0x6E, 0x73, 0x20, 0x65, 0x6E,
    0x74, 0x72, 0x79, 0x20, 0x66, 0x72, 0x6F, 0x6D,
    0x20, 0x67, 0x6C, 0x6F, 0x62, 0x61, 0x6C, 0x2E,
    0x69, 0x6E, 0x69, 0x20, 0x61, 0x6E, 0x64, 0x20,
    0x61, 0x6C, 0x73, 0x6F, 0x20, 0x44, 0x4F, 0x45,
    0x53, 0x20, 0x4E, 0x4F, 0x54, 0x20, 0x73, 0x74,
    0x6F, 0x70, 0x20, 0x6C, 0x6F, 0x61, 0x64, 0x69,
    0x6E, 0x67, 0x20, 0x65, 0x78, 0x63, 0x6C, 0x75,
    0x73, 0x69, 0x76, 0x65, 0x20, 0x66, 0x69, 0x6C,
    0x65, 0x73, 0x20, 0x66, 0x72, 0x6F, 0x6D, 0x20,
    0x65, 0x78, 0x63, 0x6C, 0x75, 0x73, 0x69, 0x76,
    0x65, 0x20, 0x70, 0x6C, 0x75, 0x67, 0x69, 0x6E,
    0x73, 0x20, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74,
    0x6F, 0x72, 0x79, 0x0D, 0x0A, 0x3B, 0x4C, 0x6F,
    0x61, 0x64, 0x50, 0x6C, 0x75, 0x67, 0x69, 0x6E,
    0x73, 0x3D, 0x31, 0x0D, 0x0A, 0x0D, 0x0A, 0x5B,
    0x45, 0x78, 0x63, 0x6C, 0x75, 0x64, 0x65, 0x73,
    0x5D, 0x0D, 0x0A, 0x3B, 0x20, 0x48, 0x65, 0x72,
    0x65, 0x20, 0x79, 0x6F, 0x75, 0x20, 0x63, 0x61,
    0x6E, 0x20, 0x73, 0x70, 0x65, 0x63, 0x69, 0x66,
    0x79, 0x20, 0x77, 0x68, 0x69, 0x63, 0x68, 0x20,
    0x70, 0x6C, 0x75, 0x67, 0x69, 0x6E, 0x73, 0x20,
    0x73, 0x68, 0x6F, 0x75, 0x6C, 0x64, 0x20, 0x62,
    0x65, 0x20, 0x69, 0x67, 0x6E, 0x6F, 0x72, 0x65,
    0x64, 0x20, 0x62, 0x79, 0x20, 0x74, 0x68, 0x69,
    0x73, 0x20, 0x45, 0x78, 0x65, 0x63, 0x75, 0x74,
    0x61, 0x62, 0x6C, 0x65, 0x0D, 0x0A, 0x3B, 0x20,
    0x49, 0x6E, 0x63, 0x6C, 0x75, 0x64, 0x65, 0x20,
    0x4F, 0x4E, 0x4C, 0x59, 0x20, 0x66, 0x69, 0x6C,
    0x65, 0x6E, 0x61, 0x6D, 0x65, 0x73, 0x20, 0x28,
    0x77, 0x69, 0x74, 0x68, 0x20, 0x65, 0x78, 0x74,
    0x65, 0x6E, 0x73, 0x69, 0x6F, 0x6E, 0x29, 0x0D,
    0x0A, 0x3B, 0x20, 0x50, 0x6C, 0x75, 0x67, 0x69,
    0x6E, 0x73, 0x20, 0x66, 0x72, 0x6F, 0x6D, 0x20,
    0x65, 0x78, 0x63, 0x6C, 0x75, 0x73, 0x69, 0x76,
    0x65, 0x20, 0x70, 0x6C, 0x75, 0x67, 0x69, 0x6E,
    0x73, 0x20, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74,
    0x6F, 0x72, 0x79, 0x20, 0x43, 0x41, 0x4E, 0x4E,
    0x4F, 0x54, 0x20, 0x62, 0x65, 0x20, 0x65, 0x78,
    0x63, 0x6C, 0x75, 0x64, 0x65, 0x64, 0x20, 0x66,
    0x72, 0x6F, 0x6D, 0x20, 0x6C, 0x6F, 0x61, 0x64,
    0x69, 0x6E, 0x67, 0x0D, 0x0A, 0x61, 0x73, 0x69,
    0x5F, 0x6C, 0x6F, 0x61, 0x64, 0x65, 0x72, 0x5F,
    0x74, 0x65, 0x73, 0x74, 0x2E, 0x61, 0x73, 0x69,
    0x0D, 0x0A, 0x3B, 0x20, 0x79, 0x6F, 0x75, 0x72,
    0x61, 0x73, 0x69, 0x5F, 0x31, 0x2E, 0x61, 0x73,
    0x69, 0x0D, 0x0A, 0x3B, 0x20, 0x79, 0x6F, 0x75,
    0x72, 0x61, 0x73, 0x69, 0x5F, 0x32, 0x2E, 0x61,
    0x73, 0x69, 0x0D, 0x0A 
};
settings_ini.write(hexData,700);
settings_ini.close();

MessageBox(0, "ASI Loader works correctly, asi_loader_test.asi will no longer be loaded. Check settings.ini inside scripts\\*your_exe_name* folder for more info.", "ASI Loader Test Plugin", MB_ICONERROR);
	return 0;
}


BOOL WINAPI DllMain(HINSTANCE hInst,DWORD reason,LPVOID)
	{
    if(reason==DLL_PROCESS_ATTACH)
    {
		HndThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)&Thread,NULL,0,NULL);
    }
    return TRUE;
}