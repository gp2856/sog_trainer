#include "Memory.h"
#include <algorithm>

LPVOID MemoryEditor::findPattern(char * pPattern, size_t patternSize, uint8_t wildcard, uint8_t * scanStart, size_t scanSize)
{
	auto res = std::search(scanStart, scanStart + scanSize, pPattern, pPattern + patternSize,
		[&wildcard](uint8_t val1, uint8_t val2) { return (val1 == val2 || val2 == wildcard); });

	return (res >= scanStart + scanSize) ? nullptr : res;
}

const std::vector<uint8_t> MemoryEditor::bytePatch(uint8_t* address, const std::vector<uint8_t>& patchBytes)
{
	std::vector<uint8_t> oldBytes(patchBytes.size());
	std::copy(address, address + patchBytes.size(), oldBytes.begin());

	// Need to make sure we can actually write to memory here
	VirtualProtect(address, patchBytes.size(), PAGE_EXECUTE_READWRITE, &dwOldProtection);
	memcpy(address, patchBytes.data(), patchBytes.size());
	VirtualProtect(address, patchBytes.size(), dwOldProtection, &dwOldProtection);
	return oldBytes;
}


