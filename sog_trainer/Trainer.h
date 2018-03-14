#pragma once
#include "HookManager.h"
#include "Console.h"
#include "SoG.h"

class Trainer
{
public:
	Trainer() = default;
	Trainer(Trainer&&) = delete;
	Trainer& operator=(Trainer&&) = delete;
	~Trainer() = default;
	Trainer(const Trainer&) = delete;
	Trainer operator=(const Trainer&) = delete;
	void HookTakeDamage();

	void Run();
private:
	HookManager hookManager;
	Console console;
	
};