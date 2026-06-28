#include "pch.h"
#include "framework.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		if (Framework::Get().Initialize())
			Framework::Get().Run();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		Framework::Get().Shutdown();
	}

	return TRUE;
}
