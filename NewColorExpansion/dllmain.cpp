// By Eternal Yoshi. Thanks to EddieLopesRJ, Gneiss, and TGE for help.
#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <vector>
#include <float.h>
#include "umvc3utils.h"
#include "MemoryMgr.h"
#include <TlHelp32.h> 
#include <memory.h>
#include "IniReader.h"
#include "framework.h"
#include "Trampoline.h"
#include <iostream>
#include <Windows.h>

using namespace Memory::VP;

#define longlong  long long
#define ulonglong  unsigned long long
#define undefined8  long long*
#define undefined7  long long
#define undefined2  int

typedef int(*code)(longlong* param_1);
typedef int(*codenoarg)();
typedef void(*method)(void);
#define undefined int
#define undefined4 int
#define CONCAT71(a,b) (a<<32 | b)
#define backupsize 10000//100000
#define prebackup 0 //100000

short ToggleColorCount;
short ColorCount02;
bool UseIndividualColors;
short RandomColorLimit;
HANDLE hProcess = 0;
uintptr_t moduleBase = 0;
DWORD_PTR ScrollerUpdater = 0;
char TCCForScroller = 0;
DWORD_PTR Fun_1402B9AE2 = 0;
char TCCForComparison = 0;

//bool FirstHook(void * toHook, void * ourFunct, int len)
//{
//	if(len <5)
//	{
//		return false;
//	}
//
//	DWORD curProtection;
//	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);
//
//	memset(toHook, 0x90, len);
//
//	DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;
//
//	*(BYTE*)toHook = 0xE9;
//	*(DWORD*)((DWORD)toHook + 1) = relativeAddress;
//
//	DWORD temp;
//	VirtualProtect(toHook, len, curProtection, &temp);
//
//	return true;
//
//}
//
//DWORD jmpBackaddy;
//void __declspec(naked) ourFunct(){
//	__asm{
//		lea edx, [r9 - (ToggleColorCount - 1)]
//		call 0x140455640
//		jmp[jmpBackaddy]
//	
//	}
//
//}

bool CheckGame()
{
	char* gameName = (char*)(_addr(0x140B12D10));

	if (strcmp(gameName, "umvc3") == 0)
	{
		return true;
	}
	else
	{
		MessageBoxA(0, "Sorry!\nColor Expansion only supports the most recent(or the version released from April 2017 onward) Steam Executable of Ultimate Marvel vs Capcom 3.", 0, MB_ICONINFORMATION);
		return false;
	}
}

DWORD SingleProtectedWriteByte(DWORD64 AddressToWrite, int length, BYTE ByteToWrite, DWORD oldPageProtection)
{
	oldPageProtection = 0;

	VirtualProtect((LPVOID)AddressToWrite, 1, PAGE_EXECUTE_READWRITE, &oldPageProtection);

	*((std::byte*)(AddressToWrite)) = (std::byte)ByteToWrite;

	VirtualProtect((LPVOID)AddressToWrite, 1, oldPageProtection, &oldPageProtection);
	return 0;
}

DWORD MultiProtectedWriteShort(DWORD64 AddressToWrite, int length, short ValuToWrite, DWORD oldPageProtection)
{
	DWORD errorMessageID = 0;
	LPSTR messageBuffer = nullptr;
	oldPageProtection = 0;

	VirtualProtect((LPVOID)AddressToWrite, 1, PAGE_EXECUTE_READWRITE, &oldPageProtection);

	if (!(*((short*)(AddressToWrite)) = ValuToWrite))
	{
		errorMessageID = ::GetLastError();
		messageBuffer = nullptr;

		std::cout << "Nope! For some reason, cannot write to " << std::hex << AddressToWrite;
		std::cout << "\nBecause of: " << messageBuffer << std::endl;
	}

	VirtualProtect((LPVOID)AddressToWrite, 1, oldPageProtection, &oldPageProtection);
	return 0;
}

DWORD MultiProtectedWriteByteArray(DWORD64 AddressToWrite, int length, BYTE BytesToWrite[], DWORD oldPageProtection)
{
	DWORD errorMessageID = 0;
	LPSTR messageBuffer = nullptr;

	oldPageProtection = 0;

	VirtualProtect((LPVOID)AddressToWrite, length, PAGE_EXECUTE_READWRITE, &oldPageProtection);

	DWORD64 TempAddr = AddressToWrite;
	int TempLength = length - 1;
	for (int i = 0; i < length; i++)
	{

		*((std::byte*)(TempAddr)) = (std::byte)BytesToWrite[i];
		TempAddr++;

	}

	/*
	if(!(*((LPVOID*)(AddressToWrite)) = BytesToWrite))
	{
		errorMessageID = ::GetLastError();
		messageBuffer = nullptr;

		std::cout << "Nope! For some reason, cannot write to " << std::hex << AddressToWrite;
		std::cout << "\nBecause of: " << messageBuffer << std::endl;
	}
	else
	{
		std::cout << "Succesfully wrote to " << std::hex << AddressToWrite << std::endl;
	}
	*/

	VirtualProtect((LPVOID)AddressToWrite, length, oldPageProtection, &oldPageProtection);
	return 0;
}

//typedef int(__stdcall* _sub_14001E9B0)(int value);
//_sub_14001E9B0 _14001E9B0;
//
//typedef void(__stdcall* sub_1402BC1C7)();
//sub_1402BC1C7 _1402BC1C7;
//
//void __stdcall ForTheColorcounter(__int64 param_1, __int64 param_2, __int64 param_3, __int64 PossibleHighlightedColor, __int64 param_5, __int64 param_6, __int64 SomePointer, __int32 param_8, __int64 param_9, __int64 param_10, __int64 HighlightedCharacterID, __int64 param_12, __int64 param_13, __int64 param_14, __int64 param_15, __int64 param_16, __int64 param_17, __int64 param_18)
//{
//	//Gets the color limit of the character from the Color Limit Array.
//	_14001E9B0 = (_sub_14001E9B0)(0x14001E9B0);	
//	__int64 ResultColorTest = _14001E9B0(HighlightedCharacterID);
//
//	//param_2 = ResultColorTest;
//	//How do I fix the game crashing?
//
//	//Throw Result in RAX Before Leaving?
//
//	/*
//	Gotta convert this.
//	  push ecx
//		mov ecx,r14d
//		call umvc3.exe+1E9B0
//		dec eax
//		 mov r9d,eax
//		pop ecx
//		jmp umvc3.exe+2BC1C7
//	*/
//
//
//	
//}

//typedef void(*HookTake2_wrapper)();
//HookTake2_wrapper Hook_wrapper;
//
////assembly snippet wrapper around our mid function hook
//extern "C" void my_hook_wrapper();
//
//void HookTake2(void* src, void* dst, size_t len) 
//{
//
//	void* PtLoc = (void*)((uintptr_t)src - off);
//
//	void* Trampoline = nullptr;
//
//	void* retloc = nullptr;
//
//	char pJump[] = {0xFF,0x25,0x00,0x00,0x00,0x00};
//	char pCall[] = {0x08,0xEB,0x00,0x00,0x00,0x02,0x15,0xFF};
//
//	while (!Trampoline)
//	{
//
//		Trampoline = VirtualAlloc(PtLoc, 50, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
//		PtLoc = (void*)((uintptr_t)PtLoc + 0x50);
//
//	}
//
//	tramp_loc = Trampoline;
//
//	memcpy(StolenByte, (char*)src, len);
//
//	//write call
//	*(UINT64*)Trampoline = INST_CALL;
//	PtLoc = (void*)((u64)Trampoline + ARRAYSIZE(pCall));
//
//	//dst = our detour function
//	*(uintptr_t*)PtLoc = (u64)dst;
//
//	PtLoc = (void*)((u64)PtLoc + 8);
//
//	// set retloc pointer where code will return after our detour function to execute stolen bytes
//	retLoc = PtLoc;
//
//	//write stolen bytes back
//	memcpy(PtLoc, StolenByte, len);
//
//	PtLoc = (void*)((u64)PtLoc + len);
//
//	// write a normal jump to our original function
//	*(char*)PtLoc = (char)0xE9;
//	PtLoc = (void*)((u64)PtLoc + 1);
//
//	*(int*)PtLoc = (uintptr_t)src - (uintptr_t)PtLoc + off2;
//
//	//hook original function to our trampoline
//	Hook((char*)src, (char*)Trampoline, len);
//}



DWORD_PTR ForTheCSSColorCounter_JmpBack = 0;
//This is to ensure the color counter stays in sync on Character Select, regardless of whether or not it goes past 130.
__attribute__((naked)) void ForTheCSSColorCounter_Hook()
{
	__asm
	{
		mov r8, r9
		inc r8
		sub r8, r9
		lea edx, [r8]
		call qword ptr [ScrollerUpdater]
		jmp qword ptr [ForTheCSSColorCounter_JmpBack]
	}
}

DWORD_PTR FUN_1402B9AD0_JmpBack = 0;
//This is to ensure the function doesn't spit out negative numbers for the number it's meant to be comparing to.
__attribute__((naked)) void FUN_1402B9AD0()
{
	__asm
	{
		xor eax, eax
		cmp r8d, [TCCForComparison]
		jnl [Fun_1402B9AE2]
		test r8d, r8d
		cmovs r8d, eax
		mov eax, r8d
		repe ret
	}
}


void OnInitializeHook()
{
	//First off the module base.
	moduleBase = (uintptr_t)GetModuleHandle(L"umvc3.exe");

	//For Testing purposes.
	if (ToggleColorCount < 0 || ToggleColorCount == NULL || ToggleColorCount > 255)
	{
		MessageBoxA(0, "The entered value for the Color count is bogus, so it shall be set to 20 in game.\nPlease check the .ini file.", 0, MB_ICONINFORMATION);
		ToggleColorCount = 20;
		RandomColorLimit = 20;
	}
	//ToggleColorCount = 17;

	//Other Important Values.
	short SecondaryColorCount = ToggleColorCount - 1;
	short TertiaryColorCount = ToggleColorCount + 1;
	DWORD oldPageProtection = 0;
	short CHSValueBorder = (249 - (ToggleColorCount - 8));

	short MSDValue = 2905;

	//First we unlock the Magneto Alt Costume.	
	SingleProtectedWriteByte((moduleBase + 0x36577A), 1, 0xFF, oldPageProtection);

	//Next we update the color limits that house the exact value and unlock slot 9.
	SingleProtectedWriteByte((moduleBase + 0x578A4), 1, 0xFF, oldPageProtection);
	SingleProtectedWriteByte(0x1402B9AD5, 1, ToggleColorCount, oldPageProtection);
	SingleProtectedWriteByte(0x14036DAB0, 1, 0xFF, oldPageProtection);
	SingleProtectedWriteByte(0x1403704DC, 1, ToggleColorCount, oldPageProtection);
	SingleProtectedWriteByte(0x1403741D9, 1, 0xFF, oldPageProtection);
	SingleProtectedWriteByte(0x14041AA18, 1, ToggleColorCount, oldPageProtection);

	if (UseIndividualColors == 0)
	{
		//Now for the characters. Galactus' color limit stays as is.
		SingleProtectedWriteByte(0x140A6F9F4, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6F9F8, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6F9FC, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA00, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA04, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA08, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA0C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA10, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA14, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA18, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA1C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA20, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA24, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA28, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA2C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA30, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA34, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA38, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA3C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA40, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA44, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA48, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA4C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA50, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA54, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA58, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA5C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA60, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA64, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA68, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA6C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA70, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA74, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA78, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA7C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA80, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA84, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA88, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA8C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA90, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA94, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA98, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA9C, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FAA0, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAA4, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAA8, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAAC, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FAB0, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAB4, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAB8, 1, ToggleColorCount, oldPageProtection);

		//These last 8 are for the child characters. They gotta be updated along with the host characters.
		SingleProtectedWriteByte(0x140A6FAC0, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAC4, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAC8, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FACC, 1, ToggleColorCount, oldPageProtection);

		SingleProtectedWriteByte(0x140A6FAD0, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAD4, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAD8, 1, ToggleColorCount, oldPageProtection);
		SingleProtectedWriteByte(0x140A6FADC, 1, ToggleColorCount, oldPageProtection);

	}
	else
	{
		//Now for the characters controlled by the individual character settings in the ini. Galactus' color limit stays as is.
		CIniReader ini;
		SingleProtectedWriteByte(0x140A6F9F4, 1, ini.ReadInteger("Settings", "ColorLimitRyu", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6F9F8, 1, ini.ReadInteger("Settings", "ColorLimitChunLi", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6F9FC, 1, ini.ReadInteger("Settings", "ColorLimitAkuma", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA00, 1, ini.ReadInteger("Settings", "ColorLimitChris", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA04, 1, ini.ReadInteger("Settings", "ColorLimitWesker", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA08, 1, ini.ReadInteger("Settings", "ColorLimitVJoe", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA0C, 1, ini.ReadInteger("Settings", "ColorLimitDante", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA10, 1, ini.ReadInteger("Settings", "ColorLimitTrish", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA14, 1, ini.ReadInteger("Settings", "ColorLimitFrank", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA18, 1, ini.ReadInteger("Settings", "ColorLimitSpencer", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA1C, 1, ini.ReadInteger("Settings", "ColorLimitArthur", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA20, 1, ini.ReadInteger("Settings", "ColorLimitAmmy", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA24, 1, ini.ReadInteger("Settings", "ColorLimitZero", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA28, 1, ini.ReadInteger("Settings", "ColorLimitTron", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA2C, 1, ini.ReadInteger("Settings", "ColorLimitMorrigan", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA30, 1, ini.ReadInteger("Settings", "ColorLimitHsienKo", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA34, 1, ini.ReadInteger("Settings", "ColorLimitFelciia", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA38, 1, ini.ReadInteger("Settings", "ColorLimitCViper", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA3C, 1, ini.ReadInteger("Settings", "ColorLimitHaggar", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA40, 1, ini.ReadInteger("Settings", "ColorLimitJill", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA44, 1, ini.ReadInteger("Settings", "ColorLimitStrider", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA48, 1, ini.ReadInteger("Settings", "ColorLimitVergil", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA4C, 1, ini.ReadInteger("Settings", "ColorLimitMrWright", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA50, 1, ini.ReadInteger("Settings", "ColorLimitFirebrand", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA54, 1, ini.ReadInteger("Settings", "ColorLimitNemesis", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA58, 1, ini.ReadInteger("Settings", "ColorLimitSpiderMan", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA5C, 1, ini.ReadInteger("Settings", "ColorLimitCap", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA60, 1, ini.ReadInteger("Settings", "ColorLimitWolverine", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA64, 1, ini.ReadInteger("Settings", "ColorLimitMagneto", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA68, 1, ini.ReadInteger("Settings", "ColorLimitHulk", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA6C, 1, ini.ReadInteger("Settings", "ColorLimitSheHulk", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA70, 1, ini.ReadInteger("Settings", "ColorLimitTaskmaster", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA74, 1, ini.ReadInteger("Settings", "ColorLimitIronMan", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA78, 1, ini.ReadInteger("Settings", "ColorLimitThor", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA7C, 1, ini.ReadInteger("Settings", "ColorLimitDoom", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA80, 1, ini.ReadInteger("Settings", "ColorLimitJean", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA84, 1, ini.ReadInteger("Settings", "ColorLimitShuma", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA88, 1, ini.ReadInteger("Settings", "ColorLimitMODOK", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA8C, 1, ini.ReadInteger("Settings", "ColorLimitDormammu", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FA90, 1, ini.ReadInteger("Settings", "ColorLimitDeadpool", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA94, 1, ini.ReadInteger("Settings", "ColorLimitStorm", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA98, 1, ini.ReadInteger("Settings", "ColorLimitSkrull", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FA9C, 1, ini.ReadInteger("Settings", "ColorLimitSentinel", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FAA0, 1, ini.ReadInteger("Settings", "ColorLimitX23", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAA4, 1, ini.ReadInteger("Settings", "ColorLimitNova", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAA8, 1, ini.ReadInteger("Settings", "ColorLimitRR", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAAC, 1, ini.ReadInteger("Settings", "ColorLimitGhostRider", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FAB0, 1, ini.ReadInteger("Settings", "ColorLimitIronFist", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAB4, 1, ini.ReadInteger("Settings", "ColorLimitDrStrange", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAB8, 1, ini.ReadInteger("Settings", "ColorLimitHawkeye", VK_SPACE), oldPageProtection);

		//These last 8 are for the child characters. They gotta be updated along with the host characters and have the same values.
		SingleProtectedWriteByte(0x140A6FAC0, 1, ini.ReadInteger("Settings", "ColorLimitZero", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAC4, 1, ini.ReadInteger("Settings", "ColorLimitMorrigan", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAC8, 1, ini.ReadInteger("Settings", "ColorLimitFelciia", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FACC, 1, ini.ReadInteger("Settings", "ColorLimitFelciia", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte(0x140A6FAD0, 1, ini.ReadInteger("Settings", "ColorLimitFrank", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAD4, 1, ini.ReadInteger("Settings", "ColorLimitMrWright", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FAD8, 1, ini.ReadInteger("Settings", "ColorLimitFirebrand", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte(0x140A6FADC, 1, ini.ReadInteger("Settings", "ColorLimitDrStrange", VK_SPACE), oldPageProtection);

	}

	//This is for text on character select. Ensures the text range is in sync.
	SingleProtectedWriteByte(0x1403704E8, 1, CHSValueBorder, oldPageProtection);
	MultiProtectedWriteShort(0x140420300, 4, MSDValue, oldPageProtection);
	MultiProtectedWriteShort(0x1404219FF, 4, MSDValue, oldPageProtection);
	MultiProtectedWriteShort(0x140421CB2, 4, MSDValue, oldPageProtection);
	MultiProtectedWriteShort(0x1404222E6, 4, MSDValue, oldPageProtection);

	//For Testing Purposes.
	//Licensing Board Portraits?
	SingleProtectedWriteByte(0x140C510FF, 1, 0x0, oldPageProtection);

	//This is for the rest of the Color Expansion Code to defeat checks for color borders.
	BYTE ForSomeFunction[] = { 0x83, 0xC8 };

	//I think this ensures the text doesn't go to H or DL in text scroll.
	BYTE ForSomeFunctionC[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, };

	//This I believe is for Color 9. UPDATED with function rewrite to basically preserve the conditions that picking a color out
	//of the character's chosen color range but also eliminate the part that prevents selecting color 9.
	BYTE ForSomeFunctionD[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	MultiProtectedWriteByteArray(0x1402BC1AD, 2, ForSomeFunction, oldPageProtection);
	MultiProtectedWriteByteArray(0x140421CB6, 14, ForSomeFunctionC, oldPageProtection);


	//This makes the jnz into an unconditional jump.
	SingleProtectedWriteByte(0x1402BCA88, 1, 0xEB, oldPageProtection);

	//This rewrites the final part to return 1.
	BYTE ForColor9[] = { 0xEB,0x1A,0x90,0x90,0x90 };
	MultiProtectedWriteByteArray(0x1402BCAB6, 5, ForColor9, oldPageProtection);

	//Originallly written by Eddie to ignore all test function and simply return the result of CalculateNewColorID. Modified.
	BYTE ForSomeFunctionE[] =
	{																				  0x83, 0xC8, 0xFF,
		0xBA, 0x01, 0x00, 0x00, 0x00, 0x45, 0x84, 0xC9, 0x0F, 0x45, 0xD0, 0x44, 0x89, 0xC1, 0x45, 0x31,
		0xC0, 0xEB, 0x1D, 0x90, 0x00, 0x00, 0x90, 0xE8, 0xE4, 0x94, 0x19, 0x00, 0xE9, 0xE2, 0x00, 0x00, 
		0x00, 0xCC, 0xCC, 0xCC ,0xCC ,0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC};
	MultiProtectedWriteByteArray(0x1402BC1AD, 51, ForSomeFunctionE, oldPageProtection);

	//Also written by Eddie for the sake of the numerical text. I believe this is actually the array of colors.
	BYTE ForSomeFunctionF[] =
	{ 0x48, 0x89, 0xC1, 0x44, 0x89 ,0xF8 ,0x05 ,0x58, 0x0B, 0x00, 0x00, 0x89, 0xC2, 0x90, 0x90, 0x90,
	  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	MultiProtectedWriteByteArray(0x1403705E0, 107, ForSomeFunctionF, oldPageProtection);

	//This for the license board's numerical text.
	BYTE ForSomeFunctionG[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	MultiProtectedWriteByteArray(0x140421CB6, 14, ForSomeFunctionG, oldPageProtection);

	//This is for the new paths.
	BYTE NewPathA[] = { 0x43, 0x6F, 0x6C, 0x6F, 0x72, 0x45, 0x78, 0x70, 0x61, 0x6E, 0x64 };

	//The main path with wild card for language choice msg_sys_menu_**.msd.
	MultiProtectedWriteByteArray(0x140B162E0, 11, NewPathA, oldPageProtection);

	//Most of the language paths for msg_sys_menu_**.msd.
	MultiProtectedWriteByteArray(0x140B145B8, 11, NewPathA, oldPageProtection);
	MultiProtectedWriteByteArray(0x140B145D8, 11, NewPathA, oldPageProtection);
	MultiProtectedWriteByteArray(0x140B145F8, 11, NewPathA, oldPageProtection);
	MultiProtectedWriteByteArray(0x140B14618, 11, NewPathA, oldPageProtection);
	MultiProtectedWriteByteArray(0x140B14638, 11, NewPathA, oldPageProtection);
	MultiProtectedWriteByteArray(0x140B14658, 11, NewPathA, oldPageProtection);

	//Portugal language's path offset is separate from the rest. I don't know why.
	MultiProtectedWriteByteArray(0x140B21D50, 11, NewPathA, oldPageProtection);

	//For Random & Random All. Rewrites the function so it selects the range of colors from default to color 19(20 externally).
	BYTE ForCHSRandom[] =
	{
		0xE8, 0x87, 0x9B, 0x6E, 0x00, 0x31, 0xD2, 0xB9, 0x14, 0x00, 0x00, 0x00, 0xF7, 0xF1, 0x8B, 0xC2,
		0xC3, 0x90, 0x90, 0x90, 0x90
	};

	MultiProtectedWriteByteArray(0x1402BC410, 21, ForCHSRandom, oldPageProtection);

	//Sets it based on the Color Limit chosen by the user.
	SingleProtectedWriteByte(0x1402BC418, 1, RandomColorLimit, oldPageProtection);


	//An adjustment on Arcade Mode's Random generator for colors. Sets the modulo to 20 and moves the rest of the code one byte after.	
	BYTE ForArcadeRandomRewrite[] =
	{
		0x33, 0x74, 0x2D, 0xE8, 0x28, 0x6B, 0xDB, 0xFF, 0x48, 0x8B, 0xC8, 0xE8, 0xEC, 0x83, 0x75, 0x00,
		0x8B, 0xF8, 0xB8, 0x67, 0x66, 0x66, 0x66, 0xF7, 0xE7, 0xC1, 0xEA, 0x03, 0x8D, 0x0C, 0x92, 0xC1,
		0xE1, 0x02, 0x2B, 0xF9, 0xE8, 0x37, 0x6B, 0xDB, 0xFF, 0x49, 0x8D, 0x0C, 0x2F, 0x89, 0x3C, 0x88,
		0x8B, 0x13, 0x48, 0x8B, 0xCE, 0xE8, 0xF6, 0xD8, 0xFF, 0xFF, 0x48, 0xFF, 0xC5, 0x48, 0x83, 0xC3,
		0x04, 0x49, 0xFF, 0xCE, 0x75, 0xAE, 0x49, 0x83, 0xC4, 0x04, 0x49, 0x83, 0xC7, 0x03, 0x49, 0xFF,
		0xCD, 0x75, 0x8F, 0xC7, 0x44, 0x24, 0x20, 0x03, 0x00, 0x00, 0x00, 0xC7, 0x44, 0x24, 0x24, 0x23,
		0x00, 0x00, 0x00, 0xC7, 0x44, 0x24, 0x28, 0x05, 0x00, 0x00, 0x00, 0xC7, 0x44, 0x24, 0x2C, 0x27,
		0x00, 0x00, 0x00, 0xC7, 0x44, 0x24, 0x30, 0x23, 0x00, 0x00, 0x00, 0xC7, 0x44, 0x24, 0x34, 0x05,
		0x00, 0x00, 0x00, 0xC7, 0x44, 0x24, 0x38, 0x27, 0x00, 0x00, 0x00, 0xC7, 0x44, 0x24, 0x3C, 0x03,
		0x00, 0x00, 0x00, 0xE8, 0xC8, 0x6A, 0xDB, 0xFF, 0x48, 0x8B, 0xC8, 0xE8, 0x10, 0xD0, 0xEA, 0xFF,
		0x83, 0xF8, 0x03, 0x76, 0x10, 0xE8, 0x86, 0x6A, 0xDB, 0xFF, 0x48, 0x8B, 0xC8, 0xE8, 0x2E, 0xD3,
		0xDB, 0xFF, 0x83, 0xE0, 0x03, 0x48, 0x98, 0xC7, 0x86, 0x84, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00,
		0x00, 0x48, 0x8D, 0x0C, 0xC5, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x44, 0x0C, 0x20, 0x89, 0x86, 0x88,
		0x00, 0x00, 0x00, 0x8B, 0x44, 0x0C, 0x24, 0x89, 0x86, 0x8C, 0x00, 0x00, 0x00, 0xE8, 0x7E, 0x6A,
		0xDB, 0xFF, 0xC7, 0x80, 0x18, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x6F, 0x6A, 0xDB,
		0xFF, 0xC7, 0x80, 0x1C, 0x09, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xE8, 0x60, 0x6A, 0xDB, 0xFF,
		0xC7, 0x80, 0x20, 0x09, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xE8, 0x11, 0x3E, 0xDB, 0xFF, 0xBA,
		0x12, 0x00, 0x00, 0x00, 0x48, 0x8B, 0xC8, 0xE8, 0x14, 0xE9, 0x06, 0x00, 0x89, 0x86, 0xA8, 0x00,
		0x00, 0x00, 0x48, 0x63, 0x5E, 0x38, 0xE8, 0x35, 0x6A, 0xDB, 0xFF, 0x8B, 0x94, 0x9E, 0x90, 0x00,
		0x00, 0x00, 0x48, 0x8B, 0xC8, 0xE8, 0x96, 0x19, 0xF8, 0xFF, 0xE8, 0xE1, 0x3D, 0xDB, 0xFF, 0x48,
		0x85, 0xC0, 0x74, 0x14, 0x48, 0x63, 0x4E, 0x38, 0x8B, 0x94, 0x8E, 0x90, 0x00, 0x00, 0x00, 0x48,
		0x8B, 0xC8, 0xE8, 0x49, 0x04, 0x00, 0x00, 0x48, 0x8B, 0x5C, 0x24, 0x70, 0x48, 0x8B, 0x6C, 0x24,
		0x78, 0x48, 0x8B, 0xB4, 0x24, 0x80, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x40, 0x41, 0x5F, 0x41,
		0x5E, 0x41, 0x5D, 0x41, 0x5C, 0x5F, 0xC3, 0xCC

	};

	MultiProtectedWriteByteArray(0x14024DBA0, 376, ForArcadeRandomRewrite, oldPageProtection);

	//Thanks to Gneiss for his gift that showed me what to change and how.
	BYTE ForTheScroller[] = 
	{ 0x51, 0x41, 0x8B, 0xCE, 0xE8, 0xC7, 0x27, 0xD6, 0xFF, 0xFF, 0xC8, 0x44, 0x8B, 0xC8, 0x59, 0xEB,
	  0xD6, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xC3, 0xCC, 0xCC, 0xCC };
	MultiProtectedWriteByteArray(0x1402BC1E0, 32, ForTheScroller, oldPageProtection);

	//Reroute the Silhouette portrait to 255 instead of 99.
	BYTE ForColorOneHundred[] =
	{ 0x68, 0x73, 0x5F, 0x62, 0x6F, 0x64, 0x79, 0x5C, 0x62, 0x5F, 0x25, 0x73, 0x32, 0x35, 0x35, 0x5F,
	  0x42, 0x4D, 0x5F, 0x48, 0x51, 0x5F, 0x4E, 0x4F, 0x4D, 0x49, 0x50
	};
	MultiProtectedWriteByteArray(0x140B2A380, 27, ForColorOneHundred, oldPageProtection);


	//Sets up Trampoline Hook for the Scroller.
	SingleProtectedWriteByte(0x1403704EA, 1, 0x90, oldPageProtection);
	SingleProtectedWriteByte(0x1403704EB, 1, 0x90, oldPageProtection);
	SingleProtectedWriteByte(0x1403704EC, 1, 0x90, oldPageProtection);
	SingleProtectedWriteByte(0x1403704ED, 1, 0x90, oldPageProtection);
	ScrollerUpdater = moduleBase + 0x455640;
	ForTheCSSColorCounter_JmpBack = moduleBase + 0x3704EE;
	TCCForScroller = ToggleColorCount - 1;
	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(_addr(0x1403704E5), tramp->Jump(ForTheCSSColorCounter_Hook), PATCH_JUMP);

	Fun_1402B9AE2 = moduleBase + 0x2B9AE2;
	TCCForComparison = ToggleColorCount;
	BYTE NoppingTheRest[] =
	{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	  0x90, 0x90, 0x90, 0x90, 0x90
	};
	MultiProtectedWriteByteArray(0x1402B9AD5, 21, NoppingTheRest, oldPageProtection);

	InjectHook(_addr(0x1402B9AD0), tramp->Jump(FUN_1402B9AD0), PATCH_JUMP);


	//For Taskmaster.
	//BYTE ForTaskmaster[] =
	//{
	//	0x7D, 0x13
	//};
	//Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	//InjectHook(_addr(0x1402BC1C1), tramp->Jump(ForTheColorcounter), PATCH_JUMP);

}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (CheckGame())
		{
			CIniReader ini;
			ToggleColorCount = ini.ReadInteger("Settings", "ToggleColorCount", VK_SPACE);
			UseIndividualColors = ini.ReadInteger("Settings", "UseIndividualColorLimits", VK_SPACE);
			RandomColorLimit = ini.ReadInteger("Settings", "RandomColorLimit", VK_SPACE);

			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)OnInitializeHook, hModule, 0, nullptr);
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

