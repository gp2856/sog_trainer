#include "Trainer.h"
#include <Windows.h>

void Trainer::HookTakeDamage()
{
	// Set the hook
	sog::oTakeBaseDamageAddress = hookManager.addHook(HookManager::HookType::Call, (uint8_t*)0x30B886DE, (uint8_t*)&sog::hkTakeBaseDamage);
	// Save the original function
	sog::oTakeBaseDamage = reinterpret_cast<sog::tTakeBaseDamage>(sog::oTakeBaseDamageAddress);
}

void Trainer::Run()
{
	console.SetTitle("SoG Trainer");
	HookTakeDamage();
	hookManager.printHookInfo();
	std::cout << "[SoG] TakeBaseDamage Addr: " << std::hex << "0x" << sog::oTakeBaseDamageAddress << std::endl;
	while (1)
	{
		if (GetAsyncKeyState(VK_DELETE) & 0x1)
		{
			break;
		}
	}
}
