#include "stdafx.h"
#include "SA2ModLoader.h"
#include <random>
extern "C"
{	
	int _seed = 0;
	void mindasrand(int seed)
	{
		_seed = seed;	
	}
	int mindarand()
	{
		_seed = 0x343FD * _seed + 0x269EC3;	
		return (_seed >> 16) & 0x7FFF;
	}
	LONGLONG __cdecl GenerateRandomSeed()
	{
		LARGE_INTEGER PerformanceCount; // [esp+0h] [ebp-8h]
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&PerformanceCount);
		return 1000000 * PerformanceCount.QuadPart / Frequency.QuadPart;
	}
	void __cdecl OverwriteSRand(int newSeed)
	{
		mindasrand(GenerateRandomSeed());
		srand(0);
	}
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		WriteCall((void*)0x0052B289, OverwriteSRand);
	}
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}

