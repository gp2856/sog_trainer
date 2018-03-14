#include "Trainer.h"
#include <Windows.h>

void Trainer::HookTakeDamage()
{
	// Set the hook
	auto origAddress = hookManager.addHook(HookManager::HookType::Call, (uint8_t*)0x307286DE, (uint8_t*)&hkTakeBaseDamage);
	// Save the original function
	
	sog::addrTakeBaseDamage = origAddress;
}

void Trainer::Run()
{
	console.SetTitle("SoG Trainer");
	HookTakeDamage();
	hookManager.printHookInfo();
	while (1)
	{
		if (GetAsyncKeyState(VK_DELETE) & 0x1)
		{
			break;
		}
	}
}

void Trainer::hkTakeBaseDamage(void * pThis, int iDamage)
{
	auto oTakeBaseDamage = reinterpret_cast<sog::tTakeBaseDamage>(sog::addrTakeBaseDamage);
	oTakeBaseDamage(pThis, 999);
}
