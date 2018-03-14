#include "HookManager.h"

uint32_t HookManager::getHookedAddress(const std::string & function)
{
	return hookList[function];
}

uint32_t HookManager::addHook(HookType hookType, uint8_t* hookAt, uint8_t* callback)
{
	switch (hookType)
	{
	case HookType::Call:
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

		uint32_t originalOffset = 0x0;
		// Of course we must first make sure that we are accessing memory with R/W/X
			if (memory.protectMemory<uint32_t>(reinterpret_cast<uint32_t>(hookAt), PAGE_EXECUTE_READWRITE))
			{
				// Copy 4 bytes from the address past the call opcode
				memcpy(&originalOffset, hookAt + 1, sizeof(uint32_t));
				uint32_t newOffset = (uint32_t)callback - (uint32_t)hookAt - 5;
				memcpy(hookAt+1, &newOffset, sizeof(uint32_t));

				// Restore original protection just in case
				memory.protectMemory<uint32_t>(reinterpret_cast<uint32_t>(hookAt));
				hookList.insert(std::make_pair<std::string, uint32_t>("TakeBaseDamage", (uint32_t)hookAt));
				return originalOffset + (uint32_t)hookAt + 5;
			}
		}
	default:
		return 0;
	}
}

void HookManager::printHookInfo()
{
	for (auto& e : hookList)
	{
		std::cout << "Hooked " << e.first << " at 0x" << std::hex << e.second << std::endl;
	}
}
