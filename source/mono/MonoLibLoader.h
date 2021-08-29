#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <iostream>

class MonoLibLoader
{
public:
	static MonoLibLoader* GetInstance();
	void StartThread();
	void DoThreadWork(MonoLibLoader* object) { object->Inject(); };
private:
	MonoLibLoader();
	void Inject();
	static MonoLibLoader* instance;
	std::thread loaderThread;
};

 