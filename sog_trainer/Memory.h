#pragma once
#include <Windows.h>
#include <cstdint>
#include <cstring>
#include <vector>

class MemoryEditor
{
public:
	MemoryEditor() = default;
	~MemoryEditor() = default;
	MemoryEditor(const MemoryEditor&) = delete;
	MemoryEditor& operator=(const MemoryEditor&) = delete;
	
	template<class T>
	T readMemory(const uint32_t address);

	template<class T>
	bool writeMemory(const uint32_t address, T val);

	template <class T>
	bool protectMemory(const uint32_t address);
	template<class T>
	bool protectMemory(const uint32_t address, const DWORD protection);

	LPVOID findPattern(char *pPattern, size_t patternSize, uint8_t wildcard, uint8_t* scanStart, size_t scanSize);
	// Direct byte manipulation
	const std::vector<uint8_t> bytePatch(uint8_t* address, const std::vector<uint8_t>&patchBytes);
private:
	DWORD dwOldProtection;
};

template<class T>
inline T MemoryEditor::readMemory(const uint32_t address)
{
	// Dereference address as a pointer to T
	return *(reinterpret_cast<T*>(address));
}

template<class T>
inline bool MemoryEditor::writeMemory(const uint32_t address, T val)
{
	// Make sure the memory we are writing to is readable
	if (protectMemory<T>(address, PAGE_EXECUTE_READWRITE))
	{
		memcpy(reinterpret_cast<T*>(address), &val, sizeof(val));
		return true;
	}
		
	return false;
}


template<class T>
inline bool MemoryEditor::protectMemory(const uint32_t address)
{
	return VirtualProtect(reinterpret_cast<T*>(address), sizeof(T), dwOldProtection, &dwOldProtection);
}
template<class T>
inline bool MemoryEditor::protectMemory(const uint32_t address, const DWORD protection)
{
	return VirtualProtect(reinterpret_cast<T*>(address), sizeof(T), protection, &dwOldProtection);
}
