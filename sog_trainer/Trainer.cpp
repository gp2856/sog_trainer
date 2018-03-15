#include "Trainer.h"
#include <Windows.h>

void Trainer::HookTakeDamage()
{
	// Creates a near call hook and saves it to the hook list.
	// Hook list: std::unordered_map<std::string, std::shared_ptr<AbstractHook>> hookList;
	hookManager.createHook(HookManager::HookType::Call, "TakeBaseDamage", (uint8_t*)0x30D486DE, (uint8_t*)&hkTakeBaseDamage);

	// Searches the list for a hook keyed with the string "TakeBaseDamage" and returns the hook if found, otherwise returns a null pointer.
	auto hook = hookManager.getHookByName("TakeBaseDamage");
	// Set the hook
	hook->Hook();
	// Get the address of the original function that was being called
	addrTakeBaseDamage = hook->GetOriginal();
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
			auto hook = hookManager.getHookByName("TakeBaseDamage");
			hook->Unhook();
		}
	}
}

void Trainer::hkTakeBaseDamage(void * pThis, int iDamage)
{
	// call original function with modified parameters
	(decltype(tTakeBaseDamage)(addrTakeBaseDamage))(pThis, 999);
}
