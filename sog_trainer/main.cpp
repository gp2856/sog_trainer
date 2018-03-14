#include <Windows.h>
#include "Trainer.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Trainer trainer;
	trainer.Run();
	return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CreateThread(0, 0x1000, MainThread, hModule, 0, 0);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}