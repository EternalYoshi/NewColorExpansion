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

short ToggleColorCount;
short ColorCount02;
bool UseIndividualColors;
HANDLE hProcess = 0;

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

void OnInitializeHook()
{

	//For Testing purposes.
	if(ToggleColorCount < 0 || ToggleColorCount == NULL)
	{
		MessageBoxA(0, "The entered value for the Color count is bogus, so it shall be set to 20 in game.\nPlease check the .ini file.", 0, MB_ICONINFORMATION);
		ToggleColorCount = 20;
	}
	//ToggleColorCount = 17;

	//Other Important Values.
	short SecondaryColorCount = ToggleColorCount - 1;
	short TertiaryColorCount = ToggleColorCount + 1;
	DWORD oldPageProtection = 0;
	short CHSValueBorder = (249 - (ToggleColorCount - 8));
	short MSDValue = 2905;
	/*
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	printf("Hi. This window is here for testing purposes.\n");
	printf("Color Expansion Kit v2 asi test by Eternal Yoshi with help and thanks from EddieLopesRJ, TGE, catboy_lover, and Gneiss.\n");

	printf("Value of ToggleColorCount from the ini is:\n");
	printf("%u\n", (unsigned int)ToggleColorCount);

	printf("meaning that the value of CHSValueBorder is:\n");
	printf("%u\n", (unsigned int)CHSValueBorder);

	printf("meaning that the value of UseIndividualColors is:\n");
	printf("%u\n", (unsigned int)UseIndividualColors);
	*/

	//First we unlock the Magneto Alt Costume.	
	SingleProtectedWriteByte(0x14036577A, 1, 0xFF, oldPageProtection);

	//Next we update the color limits that house the exact value and unlock slot 9.
	SingleProtectedWriteByte(0x1400578A4, 1, 0xFF, oldPageProtection);
	SingleProtectedWriteByte(0x1402B9AD5, 1, ToggleColorCount, oldPageProtection);
	SingleProtectedWriteByte(0x14036DAB0, 1, 0xFF, oldPageProtection);
	SingleProtectedWriteByte(0x1403704DC, 1, ToggleColorCount, oldPageProtection);
	SingleProtectedWriteByte(0x1403741D9, 1, 0xFF, oldPageProtection);
	//SingleProtectedWriteByte(0x14041AA18, 1, ToggleColorCount, oldPageProtection);

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
	//SingleProtectedWriteByte(0x140C510FF, 1, 0x0, oldPageProtection);

	//This is so Arcade Mode uses the Character Select Portraits for the Next Stage preview.
	//BYTE CHSPortraitRef[] = { 0xA4, 0xAF, 0x65 };
	//BYTE ForSomeFunctionB[] = { 0xB2, 0xB0,0x65 };

	//MultiProtectedWriteByteArray(0x14041471A, 3, CHSPortraitRef, oldPageProtection);
	//SingleProtectedWriteByte(0x14041473D, 1, 0x00, oldPageProtection);
	//SingleProtectedWriteByte(0x140414742, 1, 0x01, oldPageProtection);
	//SingleProtectedWriteByte(0x1402BDF3A, 1, 0xEB, oldPageProtection);
	//SingleProtectedWriteByte(0x140414610, 1, 0x01, oldPageProtection);
	//SingleProtectedWriteByte(0x14041460B, 1, 0x00, oldPageProtection);
	//MultiProtectedWriteByteArray(0x1404145E2, 3, ForSomeFunctionB, oldPageProtection);

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


	//Originallly written by Eddie to ignore all test function and simply return the result of CalculateNewColorID.
	BYTE ForSomeFunctionE[] =
	{ 0x83, 0xC8, 0xFF,
		0xBA, 0x01, 0x00, 0x00, 0x00, 0x45, 0x84, 0xC9, 0x0F, 0x45, 0xD0, 0x44, 0x89, 0xC1, 0x45, 0x31,
		0xC0, 0x41, 0xB9, 0x13, 0x00, 0x00, 0x00, 0xE8, 0xE4, 0x94, 0x19, 0x00, 0xE9, 0xE2, 0x00, 0x00,
		0x00 };
	MultiProtectedWriteByteArray(0x1402BC1AD, 36, ForSomeFunctionE, oldPageProtection);
	SingleProtectedWriteByte(0x1402BC1C3, 1, SecondaryColorCount, oldPageProtection);

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
	BYTE NewPathA[] = {0x43, 0x6F, 0x6C, 0x6F, 0x72, 0x45, 0x78, 0x70, 0x61, 0x6E, 0x64};

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
			//ToggleColorCount = 17;
			UseIndividualColors = ini.ReadInteger("Settings", "UseIndividualColorLimits", VK_SPACE);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)OnInitializeHook, hModule, 0, nullptr);
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

