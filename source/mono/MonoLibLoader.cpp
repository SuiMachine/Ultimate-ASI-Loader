#pragma once
#include "MonoLibLoader.h"
#include <string>

DWORD(*mono_security_get_mode)();
VOID(*mono_security_set_mode)(DWORD mode);

PVOID(*mono_domain_get)();
PVOID(*mono_domain_assembly_open)(PVOID domain, PCHAR file);
PVOID(*mono_assembly_get_image)(PVOID assembly);
PVOID(*mono_class_from_name)(PVOID image, PCHAR namespaceT, PCHAR name);
PVOID(*mono_class_get_method_from_name)(PVOID classT, PCHAR name, DWORD param_count);
PVOID(*mono_runtime_invoke)(PVOID method, PVOID instance, PVOID* params, PVOID exc);
#define MONO_PROC(NAME)\
	NAME = GetProcAddress(hMono, #NAME); }

MonoLibLoader* MonoLibLoader::instance = NULL;

MonoLibLoader* MonoLibLoader::GetInstance()
{
	if (!instance)
	{
		instance = new MonoLibLoader();
		instance->StartThread();
		return instance;
	}
	else
		return instance;
}

void MonoLibLoader::StartThread()
{
	loaderThread = std::thread(&MonoLibLoader::DoThreadWork, this, this);
}

MonoLibLoader::MonoLibLoader()
{


}



void MonoLibLoader::Inject()
{
	DWORD id, pid;
	HMODULE hMono;
	HANDLE hSs, hThread;
	THREADENTRY32 t;
	FILETIME CreationTime, ExitTime, KernelTime, UserTime;
	CONTEXT context = { CONTEXT_CONTROL };

	// poll for mono
	while ((hMono = GetModuleHandle(L"mono.dll")) == NULL) Sleep(10);

	// acquire functions
	auto test = GetProcAddress(hMono, "mono_security_set_mode");
	//(PVOID)MONO_PROC(mono_security_set_mode);
	//(PVOID)MONO_PROC(mono_domain_get);
	//(PVOID)MONO_PROC(mono_domain_assembly_open);
	//(PVOID)MONO_PROC(mono_assembly_get_image);
	//(PVOID)MONO_PROC(mono_class_from_name);
	//(PVOID)MONO_PROC(mono_class_get_method_from_name);
	//(PVOID)MONO_PROC(mono_runtime_invoke);

#undef MONO_PROC
}


