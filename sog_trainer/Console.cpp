#pragma once
#include "Console.h"
#include <iostream>

Console::Console()
{
	AllocConsole();
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// Redirect to stdin and stdout
	freopen_s(&conIn, "CONIN$", "r", stdin);
	freopen_s(&conOut, "CONOUT$", "w", stdout);
	// Populate screen buffer info
	getConsoleInfo();
}

Console::~Console()
{
	hOut = 0;
	fclose(conIn);
	fclose(conOut);
	conIn = nullptr;
	conOut = nullptr;
	FreeConsole();
}





void Console::clear()
{
	setCursorPos({ 0,0 });
	for (int x = 0; x < csbi.dwCursorPosition.X * csbi.dwCursorPosition.Y; x++)
	{
			std::cout << " ";
	}
}

void Console::getConsoleInfo()
{
	GetConsoleScreenBufferInfo(hOut, &csbi);
}

void Console::setCursorPos(COORD dwpos)
{
	csbi.dwCursorPosition = dwpos;
	SetConsoleCursorPosition(hOut, dwpos);
}

void Console::SetTitle(const char * title)
{
	SetConsoleTitle(title);
}
