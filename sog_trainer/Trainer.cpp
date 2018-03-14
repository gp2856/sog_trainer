#include "Trainer.h"
#include <Windows.h>

void Trainer::HookTakeDamage()
{
	// Set the hook and save the address
	auto hook = hookManager.createHook(HookManager::HookType::Call, (uint8_t*)0x30CD86DE, (uint8_t*)&hkTakeBaseDamage);
	hook->Hook();
	addrTakeBaseDamage = hook->GetOriginal();
	std::cout << hook->GetAddress() << std::endl;
	std::cout << hook->GetOriginal() << std::endl;
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
//	(decltype(tTakeBaseDamage)(addrTakeBaseDamage))(pThis, 999);
	auto func = reinterpret_cast<decltype(tTakeBaseDamage)>(addrTakeBaseDamage);
	func(pThis, 999);
}
