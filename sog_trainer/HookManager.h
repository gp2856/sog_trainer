#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <Windows.h>
#include <memory>


class HookManager
{
public:
	class AbstractHook
	{
	public:
		explicit AbstractHook(uint8_t *hookAt, uint8_t *callbackAddress);
		virtual ~AbstractHook() = default;
		virtual void Hook() {};
		virtual void Unhook() {};
		virtual uint32_t GetAddress();
		virtual uint32_t GetOriginal();

	protected:
		DWORD oldProtection = 0;
		uint8_t *hookAt = nullptr;
		uint8_t *originalFunc = nullptr;
		uint8_t *callbackAddress = nullptr;
	};

	class CallHook : public AbstractHook
	{
	public:
		using AbstractHook::AbstractHook;
		 void Hook() override;
		 void Unhook() override;
		 virtual uint32_t GetOriginal() override;
	private:
		uint32_t originalOffset = 0;
		uint32_t callbackOffset = 0;
	};
	enum class HookType
	{
		Call,
		Jump,
		Vtable,
		IAT,
		VEH
	};

	HookManager() = default;
	HookManager(HookManager&&) = delete;
	HookManager& operator=(HookManager&&) = delete;
	~HookManager() = default;
	HookManager(const HookManager&) = delete;
	HookManager operator=(const HookManager&) = delete;

	size_t getNumHookedFunctions() { return hookList.size(); };
	/*AbstractHook* getHookByName(const std::string& function);*/
	std::unique_ptr<AbstractHook> createHook(HookType hookType, uint8_t* hookAt,  uint8_t* addressOfCallbackFunction);
	void printHookInfo();

private:
	std::unordered_map<std::string, std::shared_ptr<AbstractHook>> hookList;
};