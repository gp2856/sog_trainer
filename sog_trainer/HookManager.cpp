#include "HookManager.h"
#include <algorithm>
std::shared_ptr<HookManager::AbstractHook> HookManager::GetHookByName(const std::string & function)
{
	auto got = hookList.find(function);
	if (got == hookList.end())
	{
		return 0;
	}
	return got->second;
}

void HookManager::CreateHook(HookType hookType, const std::string& name, uint8_t* hookAt, uint8_t* addressOfCallbackFunction)
{
	switch (hookType)
	{
	case HookType::Call:
	{
		hookList[name] = std::make_shared<CallHook>(hookAt, addressOfCallbackFunction);
		break;
	}
	default:
		std::cout << "[ERROR] Adding hook: Invalid hook type." << std::endl;
		break;
	}
}

void HookManager::PrintHookInfo()
{
	for (auto& e : hookList)
	{
		std::cout << "Hooked " << e.first << " at 0x" << std::hex << e.second->GetAddress() << std::endl;
	}
}

HookManager::AbstractHook::AbstractHook(uint8_t *hookAt, uint8_t *callbackAddress)
	:
	hookAt(hookAt),
	callbackAddress(callbackAddress)
{
}

uint32_t HookManager::AbstractHook::GetAddress()
{
	return reinterpret_cast<uint32_t>(hookAt);
}

uint32_t HookManager::AbstractHook::GetOriginal()
{
	return reinterpret_cast<uint32_t>(originalFunc);
}

void HookManager::CallHook::Hook()
{
	/* The disassembly of a near call will resemble something like this:
	0x308586DE:	E8 69 79 07 00
	Where E8 is the call opcode and 69 79 07 00 is the offset.  Offset is 0x00077969 because endianness
	Displacement is relative to next instruction so (address of next instruction + offset) = function
	Since length of a near call is 5 bytes, (hookAt + 5) = next instruction.
	Thus:
	1) Copy 4 bytes from hookAt + 1 to save the original offset
	2) Calculate the displacement between the next instruction and our callback function
	3) Copy the new offset into hookAt + 1
	4) Add to our hook index and save the original offset to unhook.*/

	VirtualProtect(hookAt, sizeof(uint32_t), PAGE_EXECUTE_READWRITE, &oldProtection);

	// If we don't already have an offset, get the offset of the original call
	if (!originalOffset)
	{
		memcpy(&originalOffset, hookAt + 1, sizeof(uint32_t));
	}

	// If we haven't already calculated the displacement between our callback and the target, do so now
	if (!callbackOffset)
	{
		callbackOffset = (uint32_t)callbackAddress - (uint32_t)hookAt - 5;
	}
	memcpy(hookAt + 1, &callbackOffset, sizeof(uint32_t));

	// Restore original protection just in case
	VirtualProtect(hookAt, sizeof(uint32_t), oldProtection, &oldProtection);
}

void HookManager::CallHook::Unhook()
{
	// Copy original offset back to hooked address
	VirtualProtect(hookAt, sizeof(uint32_t), PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy(hookAt + 1, &originalOffset, sizeof(uint32_t));
}

uint32_t HookManager::CallHook::GetOriginal()
{
	// Calculate the address of the original function if we haven't already done so
	if (!originalFunc)
	{
		originalFunc = hookAt + originalOffset + 5;
	}
	return reinterpret_cast<uint32_t>(originalFunc);
}
