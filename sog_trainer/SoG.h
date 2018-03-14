#pragma once
#include <cstdint>

namespace sog
{
	typedef void(__fastcall* tTakeBaseDamage)(void *, int);
	/*((decltype(tTakeBaseDamage))sog::oTakeBaseDamageAddress)(pThis, 999);*/
	static tTakeBaseDamage oTakeBaseDamage;
	static uint32_t addrTakeBaseDamage;
	
	
}