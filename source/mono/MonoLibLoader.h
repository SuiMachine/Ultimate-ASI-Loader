#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <iostream>
#include <winnt.h>
typedef DWORD(*LP_mono_security_get_mode)();
typedef void(*LP_mono_security_set_mode)(DWORD mode);
typedef void*(*LP_mono_domain_get)();
typedef void(*LP_mono_domain_assembly_open)(void* domain, const char* file);
typedef void(*LP_mono_assembly_get_image)(void* assembly);
typedef void(*LP_mono_class_from_name)(void* image, const char* _namespace, const char* name);
typedef void(*LP_mono_class_get_method_from_name)(void* _class, const char* name, DWORD param_count);
typedef void(*LP_mono_runtime_invoke)(void* method, void* instance, void* params, void* exc);

struct MonoDLL
{
	HMODULE dll;
	LP_mono_security_get_mode mono_security_get_mode;
	LP_mono_security_set_mode mono_security_set_mode;
	LP_mono_domain_get mono_domain_get;
	LP_mono_domain_assembly_open mono_domain_assembly_open;
	LP_mono_assembly_get_image mono_assembly_get_image;
	LP_mono_class_from_name mono_class_from_name;
	LP_mono_class_get_method_from_name mono_class_get_method_from_name;
	LP_mono_runtime_invoke mono_runtime_invoke;
};


class MonoLibLoader
{
public:
	static MonoLibLoader* GetInstance();
	MonoDLL monoDll;
	void StartThread();
	void DoThreadWork(MonoLibLoader* object) { object->Inject(); };
	void Deinject(const WCHAR* text);
private:
	void Inject();
	static MonoLibLoader* instance;
	std::thread loaderThread;
};

 