#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include "Memory.h"
#include <Windows.h>


class HookManager
{
public:
	enum class HookType
	{
		Call = 0xE8,
		Jump
	};

	HookManager() = default;
	HookManager(HookManager&&) = delete;
	HookManager& operator=(HookManager&&) = delete;
	~HookManager() = default;
	HookManager(const HookManager&) = delete;
	HookManager operator=(const HookManager&) = delete;

	size_t getNumHookedFunctions() { return hookList.size(); };
	uint32_t getHookedAddress(const std::string& function);
	uint32_t addHook(HookType hookType, uint8_t* hookAt, uint8_t* callback);
	void printHookInfo();

private:
	MemoryEditor memory;
	std::unordered_map<std::string, uint32_t> hookList;
};