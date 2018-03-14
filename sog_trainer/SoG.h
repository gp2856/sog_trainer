#pragma once
#include <cstdint>

namespace sog
{
	typedef void(__fastcall* tTakeBaseDamage)(void *, int);
	static tTakeBaseDamage oTakeBaseDamage;
	static uint32_t addrTakeBaseDamage;
	
	
}