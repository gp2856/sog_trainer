
namespace SoG
{
	typedef void(__fastcall *tTakeBaseDamage)(void *, int);
	tTakeBaseDamage oTakeBaseDamage;

	void __fastcall hkTakeBaseDamage(void *pThis, int iDamage)
	{
		// Do stuff
		oTakeBaseDamage(pThis, 99999);
	}
}