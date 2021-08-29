#pragma once
#include "MonoLibLoader.h"
#include <string>

//For base reference see https://www.unknowncheats.me/forum/rust/114627-loader-titanium-alternative.html
intptr_t dwReturn;

void DoTheHighLevelMonoThing()
{
	auto instance = MonoLibLoader::GetInstance();

	instance->monoDll.mono_security_set_mode(NULL);

	auto domain = instance->monoDll.mono_domain_get();
	try
	{
		for (int i = 0; i < instance->LibsToLoad.size(); i++)
		{
			auto domainAssemblyOpen = instance->monoDll.mono_domain_assembly_open(domain, "G:\\Steam\\steamapps\\common\\Deus Ex The Fall\\mono_plugins\\TestLibrary.dll");
			if (domainAssemblyOpen != NULL)
			{
				auto assemblyImage = instance->monoDll.mono_assembly_get_image(domainAssemblyOpen);
				if (assemblyImage != NULL)
				{
					auto className = instance->monoDll.mono_class_from_name(assemblyImage, "TestLibrary", "TestLibrary");
					if (className != NULL)
					{
						auto methodFromName = instance->monoDll.mono_class_get_method_from_name(className, "Initialize", 0);
						if (methodFromName != NULL)
						{
							auto result = instance->monoDll.mono_runtime_invoke(methodFromName, NULL, NULL, NULL);
							if(result == NULL)
								OutputDebugString(L"Fuck!");
						}
						else
							OutputDebugString(L"Method name ended up being null!");
					}
					else
						OutputDebugString(L"Class name ended up being null!");
				}
				else
					OutputDebugString(L"Assembly Image ended up being null!");
			}
			else
				OutputDebugString(L"Domain Assembly Open returned null!");
		}
	}
	catch (const std::exception e)
	{

	}

}

__declspec(naked) int MonoInject()
{
	__asm
	{
		push dwReturn;
		pushfd;
		pushad;
	};

	DoTheHighLevelMonoThing();

	__asm {
		// restore the execution state
		popad;
		popfd;
		// go about original game 'bidness
		ret;
	}
}


MonoLibLoader* MonoLibLoader::instance = NULL;

MonoLibLoader* MonoLibLoader::GetInstance()
{
	if (!instance)
	{
		instance = new MonoLibLoader();
		return instance;
	}
	else
		return instance;
}

void MonoLibLoader::StartThread()
{
	loaderThread = std::thread(&MonoLibLoader::DoThreadWork, this, this);
}

void MonoLibLoader::Deinject(const WCHAR* text)
{
	if (text)
	{
		MessageBox(NULL, text, L"Error", MB_OK | MB_ICONERROR | MB_TOPMOST);
	}
}

void MonoLibLoader::Inject()
{
	FILETIME CreationTime, ExitTime, KernelTime, UserTime;
	CONTEXT context = { CONTEXT_CONTROL };

	// poll for mono
	while ((this->monoDll.dll = GetModuleHandle(L"mono.dll")) == NULL) Sleep(10);

	// acquire functions
	auto test = GetProcAddress(this->monoDll.dll, "mono_security_get_mode");
	//monoDll.mono_security_get_mode = (LP_mono_security_get_mode)(void))GetProcAddress(monoDll.dll, "mono_security_get_mode");
	monoDll.mono_security_set_mode = (LP_mono_security_set_mode)GetProcAddress(monoDll.dll, "mono_security_set_mode");
	monoDll.mono_domain_get = (LP_mono_domain_get)GetProcAddress(monoDll.dll, "mono_domain_get");
	monoDll.mono_domain_assembly_open = (LP_mono_domain_assembly_open)GetProcAddress(monoDll.dll, "mono_domain_assembly_open");
	monoDll.mono_assembly_get_image = (LP_mono_assembly_get_image)GetProcAddress(monoDll.dll, "mono_assembly_get_image");
	monoDll.mono_class_from_name = (LP_mono_class_from_name)GetProcAddress(monoDll.dll, "mono_class_from_name");
	monoDll.mono_class_get_method_from_name = (LP_mono_class_get_method_from_name)GetProcAddress(monoDll.dll, "mono_class_get_method_from_name");
	monoDll.mono_runtime_invoke = (LP_mono_runtime_invoke)GetProcAddress(monoDll.dll, "mono_runtime_invoke");

	DWORD id = NULL;
	DWORD pID = GetCurrentProcessId();
	HANDLE hSs = CreateToolhelp32Snapshot(TH32CS_SNAPALL, pID);
	THREADENTRY32 t;
	t.dwSize = sizeof(THREADENTRY32);
	if (hSs)
	{
		unsigned long time = 0xFFFFFFFFFFFFFFFF;
		if (Thread32First(hSs, &t))
		{
			do
			{
				if (t.th32OwnerProcessID == pID)
				{
					HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, t.th32ThreadID);
					if (hThread)
					{
						if (GetThreadTimes(hThread, &CreationTime, &ExitTime, &KernelTime, &UserTime))
						{
							// nasty casting lol
							if (time > (unsigned long)&CreationTime)
							{
								time = (unsigned long)&CreationTime;
								id = t.th32ThreadID;
							}
						}
						CloseHandle(hThread);
					}
				}
			} while (Thread32Next(hSs, &t));
		}
		else
		{
			Deinject(L"Couldn't acquire the main thread.");
			return;
		}
	}

	if (id)
	{
		Sleep(2000);
		HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | THREAD_SET_CONTEXT, FALSE, id);
		if (hThread)
		{
			SuspendThread(hThread);
			if (GetThreadContext(hThread, &context))
			{
				dwReturn = context.Eip;
				context.Eip = (intptr_t)MonoInject;
				SetThreadContext(hThread, &context);
			}
			else
			{
				Deinject(L"Couldn't hijack the main thread!");
				return;
			}
			ResumeThread(hThread);
		}
	}
}



