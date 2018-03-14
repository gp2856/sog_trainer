#pragma once
#include <cstdint>
namespace sog
{
	typedef void(__fastcall *tTakeBaseDamage)(void*, int);
	void __fastcall hkTakeBaseDamage(void *pThis, int iDamage);


	static uint32_t oTakeBaseDamageAddress;
	static void(__fastcall* oTakeBaseDamage)(void *, int);
}