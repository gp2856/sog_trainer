#include "SoG.h"
#include <iostream>

void __fastcall sog::hkTakeBaseDamage(void * pThis, int iDamage)
{
	// Call original function back with 999 damage
	oTakeBaseDamage = reinterpret_cast<tTakeBaseDamage>(oTakeBaseDamageAddress);
	oTakeBaseDamage(pThis, 1);
}
