#pragma once
#include <Windows.h>
#include <cstdio>
#include <cstdint>
class Console
{
public:
	Console();
	~Console();
	Console(const Console&) = delete;
	Console operator=(const Console&) = delete;
	void clear();
	void getConsoleInfo();
	void setCursorPos(COORD dwpos);
	void SetTitle(const char *title);
private:
	FILE * conIn;
	FILE * conOut;
	HANDLE hOut = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
};


