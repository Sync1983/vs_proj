// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "import_export.h"
#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"
#include "NAPI1C.h"

static const wchar_t g_kClassNames[] = L"CAddInNative"; //"|OtherClass1|OtherClass2";
static wchar_t *g_PropNames[] = { L"IsEnabled", L"IsTimerPresent" };
static wchar_t *g_PropNamesRu[] = { L"Включен", L"ЕстьТаймер" };

static AppCapabilities g_capabilities = eAppCapabilitiesInvalid;

//---------------------------------------------------------------------------//
long GetClassObject(const WCHAR_T* wsName, IComponentBase** pInterface) {
	if (!*pInterface) {
		*pInterface = new NAPI1C;
		return (long)*pInterface;
	}
	return 0;
}
//---------------------------------------------------------------------------//
AppCapabilities SetPlatformCapabilities(const AppCapabilities capabilities) {
	g_capabilities = capabilities;
	return eAppCapabilitiesLast;
}
//---------------------------------------------------------------------------//
long DestroyObject(IComponentBase** pIntf) {
	if (!*pIntf)
		return -1;

	delete *pIntf;
	*pIntf = 0;
	return 0;
}
//---------------------------------------------------------------------------//
const WCHAR_T* GetClassNames() {
	return g_kClassNames;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

