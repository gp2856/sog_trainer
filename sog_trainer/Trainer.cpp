#include "Trainer.h"
#include <Windows.h>

void Trainer::HookTakeDamage()
{
	// Set the hook and save the address
	addrTakeBaseDamage = hookManager.addHook(HookManager::HookType::Call, (uint8_t*)0x302486DE, (uint8_t*)&hkTakeBaseDamage);
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
	// call original function with modified parameters
	(decltype(tTakeBaseDamage)(addrTakeBaseDamage))(pThis, 999);
}
