#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <iostream>
#include <winnt.h>
#include <queue>

typedef DWORD(*LP_mono_security_get_mode)();
typedef void*(*LP_mono_security_set_mode)(DWORD mode);
typedef void*(*LP_mono_domain_get)();
typedef void*(*LP_mono_domain_assembly_open)(void* domain, const char* file);
typedef void*(*LP_mono_assembly_get_image)(void* assembly);
typedef void*(*LP_mono_class_from_name)(void* image, const char* _namespace, const char* name);
typedef void*(*LP_mono_class_get_method_from_name)(void* _class, const char* name, DWORD param_count);
typedef void*(*LP_mono_runtime_invoke)(void* method, void* instance, void* params, void* exc);

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

struct LibInfo
{
	std::string library;
	std::string nameSpace;
	std::string className;
	std::string initializerMethodName;

	LibInfo(std::string library, std::string nameSpace, std::string className, std::string initializerMethodName)
	{
		this->library = library;
		this->nameSpace = nameSpace;
		this->className = className;
		this->initializerMethodName = initializerMethodName;
	}
};


class MonoLibLoader
{
public:
	static MonoLibLoader* GetInstance();
	MonoDLL monoDll;
	std::vector<LibInfo> LibsToLoad;
	void StartThread();
	void DoThreadWork(MonoLibLoader* object) { object->Inject(); };
	void Deinject(const WCHAR* text);
	void SetMainThread(HANDLE mod) { MonoThread = mod; }	//I guess that's one advantage of wrapper DLL
private:
	HANDLE MonoThread;
	void Inject();
	void InjectLibraries();
	static MonoLibLoader* instance;
	std::thread loaderThread;
};

 