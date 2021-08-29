#pragma once
#include "MonoLibLoader.h"
#include <string>

//For base reference see https://www.unknowncheats.me/forum/rust/114627-loader-titanium-alternative.html
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
	HANDLE hSs, hThread;
	THREADENTRY32 t;
	FILETIME CreationTime, ExitTime, KernelTime, UserTime;
	CONTEXT context = { CONTEXT_CONTROL };

	// poll for mono
	while ((this->monoDll.dll = GetModuleHandle(L"mono.dll")) == NULL) Sleep(10);

	// acquire functions
	auto test = GetProcAddress(this->monoDll.dll, "mono_security_get_mode");
	monoDll.mono_security_get_mode = (LP_mono_security_get_mode)GetProcAddress(monoDll.dll, "mono_security_get_mode");
	monoDll.mono_security_set_mode = (LP_mono_security_set_mode)GetProcAddress(monoDll.dll, "mono_security_set_mode");
	monoDll.mono_domain_get = (LP_mono_domain_get)GetProcAddress(monoDll.dll, "mono_domain_get");
	monoDll.mono_domain_assembly_open = (LP_mono_domain_assembly_open)GetProcAddress(monoDll.dll, "mono_domain_assembly_open");
	monoDll.mono_assembly_get_image = (LP_mono_assembly_get_image)GetProcAddress(monoDll.dll, "mono_assembly_get_image");
	monoDll.mono_class_from_name = (LP_mono_class_from_name)GetProcAddress(monoDll.dll, "mono_class_from_name");
	monoDll.mono_class_get_method_from_name = (LP_mono_class_get_method_from_name)GetProcAddress(monoDll.dll, "mono_class_get_method_from_name");
	monoDll.mono_runtime_invoke = (LP_mono_runtime_invoke)GetProcAddress(monoDll.dll, "mono_runtime_invoke");

#undef MONO_PROC
}


