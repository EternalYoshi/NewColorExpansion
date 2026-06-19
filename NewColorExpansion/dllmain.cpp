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
typedef unsigned __int64 QWORD;
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
DWORD_PTR BACKTOFUN_14041AA1B = 0;
DWORD_PTR FUN_140058F90 = 0;
DWORD_PTR aUiChsChsFaceAC = 0;
DWORD_PTR FUN_1404C4410 = 0;
DWORD_PTR FUN_140001B10 = 0;
DWORD_PTR FUN_140455260 = 0;
DWORD_PTR FUN_140151080 = 0;
DWORD_PTR FUN_140E17570 = 0;
DWORD_PTR FUN_14001DCA0 = 0;

DWORD_PTR FUN_140321020 = 0;
uint64_t uChrColorType_vftableAddr = 0;
DWORD_PTR FUN_1402C9D70 = 0;
DWORD_PTR FUN_1400012E0 = 0;
DWORD_PTR FUN_140D2AD20 = 0;
DWORD_PTR FUN_14035F770 = 0;
unsigned long ForColorBorderArray = 4278190080;
DWORD_PTR FUN_ = 0;
DWORD_PTR FUN_140EE0030 = 0;
DWORD_PTR FUN_14035F7E0_ADDR = 0;
DWORD_PTR sub_14045D4F0 = 0;
void** uChrColorType_vftable;
uint64_t uChrColorType_TypeInfo = 0x140D5B848;
uint64_t uUiBaseRelatedAddr = 0x140321020;
uint64_t DefaultRGBValue = 0xFF000000;
uint64_t ForTheRGBStuffPart1 = 0x1402C9D70;
uint64_t MaybeByteHandler = 0x1400012E0;
uint64_t SomeFunctionThatCallsTypeInfo = 0x14035F730;
uint64_t SomeFunction = 0x14035F7E0;
uint64_t YetAnotherFunction = 0x14050C900;

uint64_t FUN_14024E300 = 0x14024E300;
uint64_t FUN_1400046D0 = 0x1400046D0;
uint64_t FUN_140146560 = 0x140146560;
uint64_t FUN_14000AF80 = 0x14000AF80;
uint64_t FUN_1401461E0 = 0x1401461E0;
uint64_t FUN_140417C10 = 0x140417C10;
uint64_t FUN_1406CD4E0 = 0x1406CD4E0;
uint64_t FUN_1401CF670 = 0x1401CF670;
uint64_t BuildStageSelectArray = 0x1402BC5D0;
uint64_t getsGameUI = 0x140001AC0;

uint64_t CharacterColorLimitArray = 0; //Before 2026, it starts at 0x140A6F9F0.
uint64_t MagAltBlockPtr = 0;//Originally 0x14036577A;
uint64_t ForColor9UIA = 0;//Originally 0x140057896 -> 0x1400578A4. Need to offset by 0xE.
uint64_t ForColor9UIB = 0;//Originally 0x14036DAA3 -> 0x14036DAB0. Need to offset by 0xD.
uint64_t ForColor9UIC = 0;//Originally 0x1403704D3 -> 0x1403704DC. Need to offset by 0x9.
uint64_t ForColor9UID = 0;//Originally 0x1403741C9 -> 0x1403741D9. Need to offset by 0x10.
uint64_t ForCHSValueBorder = 0;
uint64_t ForMSDIndicesA = 0;//Originally 0x140420300. Offset by 0xC.
uint64_t ForMSDIndicesB = 0;
uint64_t ForMSDIndicesC = 0;
uint64_t ForMSDIndicesD = 0;
uint64_t ColorBorderDefeat = 0;
//uint64_t ForMSDIndicesE = 0;

size_t ProjectedModuleSize = 0xEBB000;

#pragma region AOB strings
//The first part of the pattern. This should definitely ONLY match the first part of this array.
const char* DefaultCharacterColorLimitArrayPattern = "01 00 00 00 08 00 00 00 08 00 00 00 09 00 00 00 08 00 00 00 09 00 00 00 08 00 00 00 08 00 00 00 08 00 00 00 08 00 00 00 08 00 00 00 08 00 00 00 08 00 00 00 08 00 00 00 08 00 00 00 08 00 00 00";
const char* AOBMagnetoAltBlock = "83 FB 1D ?? ?? 83 BC BE ?? ?? ?? ?? 07 ?? ?? 44 89 A4 BE ?? ?? ?? 00";
const char* AOBForColor9UIA = "48 89 74 24 58 41 8B B6 ?? ?? ?? ?? 83 FE 08";
const char* AOBForColor9UIB = "4C 8B C0 44 8B CB E8 ?? ?? ?? ?? 83 FB 08";
const char* AOBForColor9UIC = "83 F8 02 41 0F 44 DC 41 B9 08 00 00 00 45 33 C0 8B CB 41 8D 51 F9 E8 ?? ?? ?? ??";
const char* AOBForColor9UID = "48 8D 4C 24 40 4C 8B C0 E8 ?? ?? ?? ?? 83 7E ?? 08 74 ?? 48 8B 4E ?? 48 85 C9";
const char* AOBForMSDIndicesA = "8B 43 ?? 48 8B 4F ?? 83 F8 06 8D 90 E1 00 00 00 41 0F 44 D4 83 F8 07 41 0F 44 D5";
const char* AOBForMSDIndicesB = "C7 87 ?? ?? ?? ?? 00 00 00 00 8B 87 ?? ?? ?? ?? B9 ?? ?? ?? ?? 83 F8 06 8D 90 E1 00 00 00 0F 44 D1 B9 ?? ?? ?? ??";
const char* AOBForMSDIndicesC = "48 8B 03 FF 90 ?? ?? ?? ?? 8B 83 ?? ?? ?? ?? B9 ?? ?? 00 00 83 F8 06 8D 90 E1 00 00 00 0F 44 D1 B9 ?? ?? 00 00 83 F8 07 0F 44 D1";
const char* AOBForMSDIndicesD = "48 8B 9C 24 ?? ?? ?? ?? 49 8D 0C 3C 41 8B 04 8F B9 ?? ?? ?? ?? 83 F8 06 8D 90 E1 00 00 00 0F 44 D1 83 F8 07 B8 ?? ?? ?? ?? 48 8D 0C 1F 0F 44 D0 49 8B 4C CE ??";
const char* AOBForUnconditionalJump = "";


#pragma endregion

//Gotta make arrays of strings for the characters. I think this is what the SDL uses to lookup the RGB values.
#pragma region Char Arrays for uChrColorType

char aRyu[][20] = {
"RYU_0" ,
"RYU_1" ,
"RYU_2" ,
"RYU_3" ,
"RYU_4" ,
"RYU_5" ,
"RYU_6" ,
"RYU_7" ,
"RYU_8" ,
"RYU_9" ,
"RYU_10" ,
"RYU_11" ,
"RYU_12" ,
"RYU_13" ,
"RYU_14" ,
"RYU_15" ,
"RYU_16" ,
"RYU_17" ,
"RYU_18" ,
"RYU_19" ,
"RYU"
};


char aChunLi[][20] = {
"CHUNLI_0" ,
"CHUNLI_1" ,
"CHUNLI_2" ,
"CHUNLI_3" ,
"CHUNLI_4" ,
"CHUNLI_5" ,
"CHUNLI_6" ,
"CHUNLI_7" ,
"CHUNLI_8" ,
"CHUNLI_9" ,
"CHUNLI_10" ,
"CHUNLI_11" ,
"CHUNLI_12" ,
"CHUNLI_13" ,
"CHUNLI_14" ,
"CHUNLI_15" ,
"CHUNLI_16" ,
"CHUNLI_17" ,
"CHUNLI_18" ,
"CHUNLI_19" ,
"CHUNLI"
};


char aGouki[][20] = {
"GOUKI_0" ,
"GOUKI_1" ,
"GOUKI_2" ,
"GOUKI_3" ,
"GOUKI_4" ,
"GOUKI_5" ,
"GOUKI_6" ,
"GOUKI_7" ,
"GOUKI_8" ,
"GOUKI_9" ,
"GOUKI_10" ,
"GOUKI_11" ,
"GOUKI_12" ,
"GOUKI_13" ,
"GOUKI_14" ,
"GOUKI_15" ,
"GOUKI_16" ,
"GOUKI_17" ,
"GOUKI_18" ,
"GOUKI_19" ,
"GOUKI"
};


char aChris[][20] = {
"CHRIS_0" ,
"CHRIS_1" ,
"CHRIS_2" ,
"CHRIS_3" ,
"CHRIS_4" ,
"CHRIS_5" ,
"CHRIS_6" ,
"CHRIS_7" ,
"CHRIS_8" ,
"CHRIS_9" ,
"CHRIS_10" ,
"CHRIS_11" ,
"CHRIS_12" ,
"CHRIS_13" ,
"CHRIS_14" ,
"CHRIS_15" ,
"CHRIS_16" ,
"CHRIS_17" ,
"CHRIS_18" ,
"CHRIS_19" ,
"CHRIS"
};


char aWesker[][20] = {
"WESKER_0" ,
"WESKER_1" ,
"WESKER_2" ,
"WESKER_3" ,
"WESKER_4" ,
"WESKER_5" ,
"WESKER_6" ,
"WESKER_7" ,
"WESKER_8" ,
"WESKER_9" ,
"WESKER_10" ,
"WESKER_11" ,
"WESKER_12" ,
"WESKER_13" ,
"WESKER_14" ,
"WESKER_15" ,
"WESKER_16" ,
"WESKER_17" ,
"WESKER_18" ,
"WESKER_19" ,
"WESKER"
};


char aVJoe[][20] = {
"VJOE_0" ,
"VJOE_1" ,
"VJOE_2" ,
"VJOE_3" ,
"VJOE_4" ,
"VJOE_5" ,
"VJOE_6" ,
"VJOE_7" ,
"VJOE_8" ,
"VJOE_9" ,
"VJOE_10" ,
"VJOE_11" ,
"VJOE_12" ,
"VJOE_13" ,
"VJOE_14" ,
"VJOE_15" ,
"VJOE_16" ,
"VJOE_17" ,
"VJOE_18" ,
"VJOE_19" ,
"VJOE"
};


char aDante[][20] = {
"DANTE_0" ,
"DANTE_1" ,
"DANTE_2" ,
"DANTE_3" ,
"DANTE_4" ,
"DANTE_5" ,
"DANTE_6" ,
"DANTE_7" ,
"DANTE_8" ,
"DANTE_9" ,
"DANTE_10" ,
"DANTE_11" ,
"DANTE_12" ,
"DANTE_13" ,
"DANTE_14" ,
"DANTE_15" ,
"DANTE_16" ,
"DANTE_17" ,
"DANTE_18" ,
"DANTE_19" ,
"DANTE"
};


char aTrish[][20] = {
"TRISH_0" ,
"TRISH_1" ,
"TRISH_2" ,
"TRISH_3" ,
"TRISH_4" ,
"TRISH_5" ,
"TRISH_6" ,
"TRISH_7" ,
"TRISH_8" ,
"TRISH_9" ,
"TRISH_10" ,
"TRISH_11" ,
"TRISH_12" ,
"TRISH_13" ,
"TRISH_14" ,
"TRISH_15" ,
"TRISH_16" ,
"TRISH_17" ,
"TRISH_18" ,
"TRISH_19" ,
"TRISH"
};


char aFrank[][20] = {
"FRANK_0" ,
"FRANK_1" ,
"FRANK_2" ,
"FRANK_3" ,
"FRANK_4" ,
"FRANK_5" ,
"FRANK_6" ,
"FRANK_7" ,
"FRANK_8" ,
"FRANK_9" ,
"FRANK_10" ,
"FRANK_11" ,
"FRANK_12" ,
"FRANK_13" ,
"FRANK_14" ,
"FRANK_15" ,
"FRANK_16" ,
"FRANK_17" ,
"FRANK_18" ,
"FRANK_19" ,
"FRANK"
};


char aSpencer[][20] = {
"SPENCER_0" ,
"SPENCER_1" ,
"SPENCER_2" ,
"SPENCER_3" ,
"SPENCER_4" ,
"SPENCER_5" ,
"SPENCER_6" ,
"SPENCER_7" ,
"SPENCER_8" ,
"SPENCER_9" ,
"SPENCER_10" ,
"SPENCER_11" ,
"SPENCER_12" ,
"SPENCER_13" ,
"SPENCER_14" ,
"SPENCER_15" ,
"SPENCER_16" ,
"SPENCER_17" ,
"SPENCER_18" ,
"SPENCER_19" ,
"SPENCER"
};


char aArthur[][20] = {
"ARTHUR_0" ,
"ARTHUR_1" ,
"ARTHUR_2" ,
"ARTHUR_3" ,
"ARTHUR_4" ,
"ARTHUR_5" ,
"ARTHUR_6" ,
"ARTHUR_7" ,
"ARTHUR_8" ,
"ARTHUR_9" ,
"ARTHUR_10" ,
"ARTHUR_11" ,
"ARTHUR_12" ,
"ARTHUR_13" ,
"ARTHUR_14" ,
"ARTHUR_15" ,
"ARTHUR_16" ,
"ARTHUR_17" ,
"ARTHUR_18" ,
"ARTHUR_19" ,
"ARTHUR"
};


char aAmaterasu[][20] = {
"AMATERASU_0" ,
"AMATERASU_1" ,
"AMATERASU_2" ,
"AMATERASU_3" ,
"AMATERASU_4" ,
"AMATERASU_5" ,
"AMATERASU_6" ,
"AMATERASU_7" ,
"AMATERASU_8" ,
"AMATERASU_9" ,
"AMATERASU_10" ,
"AMATERASU_11" ,
"AMATERASU_12" ,
"AMATERASU_13" ,
"AMATERASU_14" ,
"AMATERASU_15" ,
"AMATERASU_16" ,
"AMATERASU_17" ,
"AMATERASU_18" ,
"AMATERASU_19" ,
"AMATERASU"
};


char aZero[][20] = {
"ZERO_0" ,
"ZERO_1" ,
"ZERO_2" ,
"ZERO_3" ,
"ZERO_4" ,
"ZERO_5" ,
"ZERO_6" ,
"ZERO_7" ,
"ZERO_8" ,
"ZERO_9" ,
"ZERO_10" ,
"ZERO_11" ,
"ZERO_12" ,
"ZERO_13" ,
"ZERO_14" ,
"ZERO_15" ,
"ZERO_16" ,
"ZERO_17" ,
"ZERO_18" ,
"ZERO_19" ,
"ZERO"
};


char aTron[][20] = {
"TRON_0" ,
"TRON_1" ,
"TRON_2" ,
"TRON_3" ,
"TRON_4" ,
"TRON_5" ,
"TRON_6" ,
"TRON_7" ,
"TRON_8" ,
"TRON_9" ,
"TRON_10" ,
"TRON_11" ,
"TRON_12" ,
"TRON_13" ,
"TRON_14" ,
"TRON_15" ,
"TRON_16" ,
"TRON_17" ,
"TRON_18" ,
"TRON_19" ,
"TRON"
};


char aMorrigan[][20] = {
"MORRIGAN_0" ,
"MORRIGAN_1" ,
"MORRIGAN_2" ,
"MORRIGAN_3" ,
"MORRIGAN_4" ,
"MORRIGAN_5" ,
"MORRIGAN_6" ,
"MORRIGAN_7" ,
"MORRIGAN_8" ,
"MORRIGAN_9" ,
"MORRIGAN_10" ,
"MORRIGAN_11" ,
"MORRIGAN_12" ,
"MORRIGAN_13" ,
"MORRIGAN_14" ,
"MORRIGAN_15" ,
"MORRIGAN_16" ,
"MORRIGAN_17" ,
"MORRIGAN_18" ,
"MORRIGAN_19" ,
"MORRIGAN"
};


char aLeiLei[][20] = {
"LEILEI_0" ,
"LEILEI_1" ,
"LEILEI_2" ,
"LEILEI_3" ,
"LEILEI_4" ,
"LEILEI_5" ,
"LEILEI_6" ,
"LEILEI_7" ,
"LEILEI_8" ,
"LEILEI_9" ,
"LEILEI_10" ,
"LEILEI_11" ,
"LEILEI_12" ,
"LEILEI_13" ,
"LEILEI_14" ,
"LEILEI_15" ,
"LEILEI_16" ,
"LEILEI_17" ,
"LEILEI_18" ,
"LEILEI_19" ,
"LEILEI"
};


char aFelicia[][20] = {
"FELICIA_0" ,
"FELICIA_1" ,
"FELICIA_2" ,
"FELICIA_3" ,
"FELICIA_4" ,
"FELICIA_5" ,
"FELICIA_6" ,
"FELICIA_7" ,
"FELICIA_8" ,
"FELICIA_9" ,
"FELICIA_10" ,
"FELICIA_11" ,
"FELICIA_12" ,
"FELICIA_13" ,
"FELICIA_14" ,
"FELICIA_15" ,
"FELICIA_16" ,
"FELICIA_17" ,
"FELICIA_18" ,
"FELICIA_19" ,
"FELICIA"
};


char aCViper[][20] = {
"CVIPER_0" ,
"CVIPER_1" ,
"CVIPER_2" ,
"CVIPER_3" ,
"CVIPER_4" ,
"CVIPER_5" ,
"CVIPER_6" ,
"CVIPER_7" ,
"CVIPER_8" ,
"CVIPER_9" ,
"CVIPER_10" ,
"CVIPER_11" ,
"CVIPER_12" ,
"CVIPER_13" ,
"CVIPER_14" ,
"CVIPER_15" ,
"CVIPER_16" ,
"CVIPER_17" ,
"CVIPER_18" ,
"CVIPER_19" ,
"CVIPER"
};


char aHaggar[][20] = {
"HAGGAR_0" ,
"HAGGAR_1" ,
"HAGGAR_2" ,
"HAGGAR_3" ,
"HAGGAR_4" ,
"HAGGAR_5" ,
"HAGGAR_6" ,
"HAGGAR_7" ,
"HAGGAR_8" ,
"HAGGAR_9" ,
"HAGGAR_10" ,
"HAGGAR_11" ,
"HAGGAR_12" ,
"HAGGAR_13" ,
"HAGGAR_14" ,
"HAGGAR_15" ,
"HAGGAR_16" ,
"HAGGAR_17" ,
"HAGGAR_18" ,
"HAGGAR_19" ,
"HAGGAR"
};


char aJill[][20] = {
"JILL_0" ,
"JILL_1" ,
"JILL_2" ,
"JILL_3" ,
"JILL_4" ,
"JILL_5" ,
"JILL_6" ,
"JILL_7" ,
"JILL_8" ,
"JILL_9" ,
"JILL_10" ,
"JILL_11" ,
"JILL_12" ,
"JILL_13" ,
"JILL_14" ,
"JILL_15" ,
"JILL_16" ,
"JILL_17" ,
"JILL_18" ,
"JILL_19" ,
"JILL"
};


char aHiryu[][20] = {
"HIRYU_0" ,
"HIRYU_1" ,
"HIRYU_2" ,
"HIRYU_3" ,
"HIRYU_4" ,
"HIRYU_5" ,
"HIRYU_6" ,
"HIRYU_7" ,
"HIRYU_8" ,
"HIRYU_9" ,
"HIRYU_10" ,
"HIRYU_11" ,
"HIRYU_12" ,
"HIRYU_13" ,
"HIRYU_14" ,
"HIRYU_15" ,
"HIRYU_16" ,
"HIRYU_17" ,
"HIRYU_18" ,
"HIRYU_19" ,
"HIRYU"
};


char aVergil[][20] = {
"VERGIL_0" ,
"VERGIL_1" ,
"VERGIL_2" ,
"VERGIL_3" ,
"VERGIL_4" ,
"VERGIL_5" ,
"VERGIL_6" ,
"VERGIL_7" ,
"VERGIL_8" ,
"VERGIL_9" ,
"VERGIL_10" ,
"VERGIL_11" ,
"VERGIL_12" ,
"VERGIL_13" ,
"VERGIL_14" ,
"VERGIL_15" ,
"VERGIL_16" ,
"VERGIL_17" ,
"VERGIL_18" ,
"VERGIL_19" ,
"VERGIL"
};


char aNaruhodo[][20] = {
"NARUHODO_0" ,
"NARUHODO_1" ,
"NARUHODO_2" ,
"NARUHODO_3" ,
"NARUHODO_4" ,
"NARUHODO_5" ,
"NARUHODO_6" ,
"NARUHODO_7" ,
"NARUHODO_8" ,
"NARUHODO_9" ,
"NARUHODO_10" ,
"NARUHODO_11" ,
"NARUHODO_12" ,
"NARUHODO_13" ,
"NARUHODO_14" ,
"NARUHODO_15" ,
"NARUHODO_16" ,
"NARUHODO_17" ,
"NARUHODO_18" ,
"NARUHODO_19" ,
"NARUHODO"
};


char aRedArremer[][20] = {
"REDARREMER_0" ,
"REDARREMER_1" ,
"REDARREMER_2" ,
"REDARREMER_3" ,
"REDARREMER_4" ,
"REDARREMER_5" ,
"REDARREMER_6" ,
"REDARREMER_7" ,
"REDARREMER_8" ,
"REDARREMER_9" ,
"REDARREMER_10" ,
"REDARREMER_11" ,
"REDARREMER_12" ,
"REDARREMER_13" ,
"REDARREMER_14" ,
"REDARREMER_15" ,
"REDARREMER_16" ,
"REDARREMER_17" ,
"REDARREMER_18" ,
"REDARREMER_19" ,
"REDARREMER"
};


char aNemesis[][20] = {
"NEMESIS_0" ,
"NEMESIS_1" ,
"NEMESIS_2" ,
"NEMESIS_3" ,
"NEMESIS_4" ,
"NEMESIS_5" ,
"NEMESIS_6" ,
"NEMESIS_7" ,
"NEMESIS_8" ,
"NEMESIS_9" ,
"NEMESIS_10" ,
"NEMESIS_11" ,
"NEMESIS_12" ,
"NEMESIS_13" ,
"NEMESIS_14" ,
"NEMESIS_15" ,
"NEMESIS_16" ,
"NEMESIS_17" ,
"NEMESIS_18" ,
"NEMESIS_19" ,
"NEMESIS"
};


char aSpiderMan[][20] = {
"SPIDERMAN_0" ,
"SPIDERMAN_1" ,
"SPIDERMAN_2" ,
"SPIDERMAN_3" ,
"SPIDERMAN_4" ,
"SPIDERMAN_5" ,
"SPIDERMAN_6" ,
"SPIDERMAN_7" ,
"SPIDERMAN_8" ,
"SPIDERMAN_9" ,
"SPIDERMAN_10" ,
"SPIDERMAN_11" ,
"SPIDERMAN_12" ,
"SPIDERMAN_13" ,
"SPIDERMAN_14" ,
"SPIDERMAN_15" ,
"SPIDERMAN_16" ,
"SPIDERMAN_17" ,
"SPIDERMAN_18" ,
"SPIDERMAN_19" ,
"SPIDERMAN"
};


char aCapAmerica[][20] = {
"CAPAMERICA_0" ,
"CAPAMERICA_1" ,
"CAPAMERICA_2" ,
"CAPAMERICA_3" ,
"CAPAMERICA_4" ,
"CAPAMERICA_5" ,
"CAPAMERICA_6" ,
"CAPAMERICA_7" ,
"CAPAMERICA_8" ,
"CAPAMERICA_9" ,
"CAPAMERICA_10" ,
"CAPAMERICA_11" ,
"CAPAMERICA_12" ,
"CAPAMERICA_13" ,
"CAPAMERICA_14" ,
"CAPAMERICA_15" ,
"CAPAMERICA_16" ,
"CAPAMERICA_17" ,
"CAPAMERICA_18" ,
"CAPAMERICA_19" ,
"CAPAMERICA"
};


char aWolverine[][20] = {
"WOLVERINE_0" ,
"WOLVERINE_1" ,
"WOLVERINE_2" ,
"WOLVERINE_3" ,
"WOLVERINE_4" ,
"WOLVERINE_5" ,
"WOLVERINE_6" ,
"WOLVERINE_7" ,
"WOLVERINE_8" ,
"WOLVERINE_9" ,
"WOLVERINE_10" ,
"WOLVERINE_11" ,
"WOLVERINE_12" ,
"WOLVERINE_13" ,
"WOLVERINE_14" ,
"WOLVERINE_15" ,
"WOLVERINE_16" ,
"WOLVERINE_17" ,
"WOLVERINE_18" ,
"WOLVERINE_19" ,
"WOLVERINE"
};


char aMagneto[][20] = {
"MAGNETO_0" ,
"MAGNETO_1" ,
"MAGNETO_2" ,
"MAGNETO_3" ,
"MAGNETO_4" ,
"MAGNETO_5" ,
"MAGNETO_6" ,
"MAGNETO_7" ,
"MAGNETO_8" ,
"MAGNETO_9" ,
"MAGNETO_10" ,
"MAGNETO_11" ,
"MAGNETO_12" ,
"MAGNETO_13" ,
"MAGNETO_14" ,
"MAGNETO_15" ,
"MAGNETO_16" ,
"MAGNETO_17" ,
"MAGNETO_18" ,
"MAGNETO_19" ,
"MAGNETO"
};


char aHulk[][20] = {
"HULK_0" ,
"HULK_1" ,
"HULK_2" ,
"HULK_3" ,
"HULK_4" ,
"HULK_5" ,
"HULK_6" ,
"HULK_7" ,
"HULK_8" ,
"HULK_9" ,
"HULK_10" ,
"HULK_11" ,
"HULK_12" ,
"HULK_13" ,
"HULK_14" ,
"HULK_15" ,
"HULK_16" ,
"HULK_17" ,
"HULK_18" ,
"HULK_19" ,
"HULK"
};


char aSheHulk[][20] = {
"SHEHULK_0" ,
"SHEHULK_1" ,
"SHEHULK_2" ,
"SHEHULK_3" ,
"SHEHULK_4" ,
"SHEHULK_5" ,
"SHEHULK_6" ,
"SHEHULK_7" ,
"SHEHULK_8" ,
"SHEHULK_9" ,
"SHEHULK_10" ,
"SHEHULK_11" ,
"SHEHULK_12" ,
"SHEHULK_13" ,
"SHEHULK_14" ,
"SHEHULK_15" ,
"SHEHULK_16" ,
"SHEHULK_17" ,
"SHEHULK_18" ,
"SHEHULK_19" ,
"SHEHULK"
};


char aTaskMaster[][20] = {
"TASKMASTER_0" ,
"TASKMASTER_1" ,
"TASKMASTER_2" ,
"TASKMASTER_3" ,
"TASKMASTER_4" ,
"TASKMASTER_5" ,
"TASKMASTER_6" ,
"TASKMASTER_7" ,
"TASKMASTER_8" ,
"TASKMASTER_9" ,
"TASKMASTER_10" ,
"TASKMASTER_11" ,
"TASKMASTER_12" ,
"TASKMASTER_13" ,
"TASKMASTER_14" ,
"TASKMASTER_15" ,
"TASKMASTER_16" ,
"TASKMASTER_17" ,
"TASKMASTER_18" ,
"TASKMASTER_19" ,
"TASKMASTER"
};


char aIronMan[][20] = {
"IRONMAN_0" ,
"IRONMAN_1" ,
"IRONMAN_2" ,
"IRONMAN_3" ,
"IRONMAN_4" ,
"IRONMAN_5" ,
"IRONMAN_6" ,
"IRONMAN_7" ,
"IRONMAN_8" ,
"IRONMAN_9" ,
"IRONMAN_10" ,
"IRONMAN_11" ,
"IRONMAN_12" ,
"IRONMAN_13" ,
"IRONMAN_14" ,
"IRONMAN_15" ,
"IRONMAN_16" ,
"IRONMAN_17" ,
"IRONMAN_18" ,
"IRONMAN_19" ,
"IRONMAN"
};


char aThor[][20] = {
"THOR_0" ,
"THOR_1" ,
"THOR_2" ,
"THOR_3" ,
"THOR_4" ,
"THOR_5" ,
"THOR_6" ,
"THOR_7" ,
"THOR_8" ,
"THOR_9" ,
"THOR_10" ,
"THOR_11" ,
"THOR_12" ,
"THOR_13" ,
"THOR_14" ,
"THOR_15" ,
"THOR_16" ,
"THOR_17" ,
"THOR_18" ,
"THOR_19" ,
"THOR"
};


char aDrDoom[][20] = {
"DRDOOM_0" ,
"DRDOOM_1" ,
"DRDOOM_2" ,
"DRDOOM_3" ,
"DRDOOM_4" ,
"DRDOOM_5" ,
"DRDOOM_6" ,
"DRDOOM_7" ,
"DRDOOM_8" ,
"DRDOOM_9" ,
"DRDOOM_10" ,
"DRDOOM_11" ,
"DRDOOM_12" ,
"DRDOOM_13" ,
"DRDOOM_14" ,
"DRDOOM_15" ,
"DRDOOM_16" ,
"DRDOOM_17" ,
"DRDOOM_18" ,
"DRDOOM_19" ,
"DRDOOM"
};


char aPhoenix[][20] = {
"PHOENIX_0" ,
"PHOENIX_1" ,
"PHOENIX_2" ,
"PHOENIX_3" ,
"PHOENIX_4" ,
"PHOENIX_5" ,
"PHOENIX_6" ,
"PHOENIX_7" ,
"PHOENIX_8" ,
"PHOENIX_9" ,
"PHOENIX_10" ,
"PHOENIX_11" ,
"PHOENIX_12" ,
"PHOENIX_13" ,
"PHOENIX_14" ,
"PHOENIX_15" ,
"PHOENIX_16" ,
"PHOENIX_17" ,
"PHOENIX_18" ,
"PHOENIX_19" ,
"PHOENIX"
};


char aShuma[][20] = {
"SHUMA_0" ,
"SHUMA_1" ,
"SHUMA_2" ,
"SHUMA_3" ,
"SHUMA_4" ,
"SHUMA_5" ,
"SHUMA_6" ,
"SHUMA_7" ,
"SHUMA_8" ,
"SHUMA_9" ,
"SHUMA_10" ,
"SHUMA_11" ,
"SHUMA_12" ,
"SHUMA_13" ,
"SHUMA_14" ,
"SHUMA_15" ,
"SHUMA_16" ,
"SHUMA_17" ,
"SHUMA_18" ,
"SHUMA_19" ,
"SHUMA"
};


char aModok[][20] = {
"MODOK_0" ,
"MODOK_1" ,
"MODOK_2" ,
"MODOK_3" ,
"MODOK_4" ,
"MODOK_5" ,
"MODOK_6" ,
"MODOK_7" ,
"MODOK_8" ,
"MODOK_9" ,
"MODOK_10" ,
"MODOK_11" ,
"MODOK_12" ,
"MODOK_13" ,
"MODOK_14" ,
"MODOK_15" ,
"MODOK_16" ,
"MODOK_17" ,
"MODOK_18" ,
"MODOK_19" ,
"MODOK"
};


char aDormammu[][20] = {
"DORMAMMU_0" ,
"DORMAMMU_1" ,
"DORMAMMU_2" ,
"DORMAMMU_3" ,
"DORMAMMU_4" ,
"DORMAMMU_5" ,
"DORMAMMU_6" ,
"DORMAMMU_7" ,
"DORMAMMU_8" ,
"DORMAMMU_9" ,
"DORMAMMU_10" ,
"DORMAMMU_11" ,
"DORMAMMU_12" ,
"DORMAMMU_13" ,
"DORMAMMU_14" ,
"DORMAMMU_15" ,
"DORMAMMU_16" ,
"DORMAMMU_17" ,
"DORMAMMU_18" ,
"DORMAMMU_19" ,
"DORMAMMU"
};


char aDeadpool[][20] = {
"DEADPOOL_0" ,
"DEADPOOL_1" ,
"DEADPOOL_2" ,
"DEADPOOL_3" ,
"DEADPOOL_4" ,
"DEADPOOL_5" ,
"DEADPOOL_6" ,
"DEADPOOL_7" ,
"DEADPOOL_8" ,
"DEADPOOL_9" ,
"DEADPOOL_10" ,
"DEADPOOL_11" ,
"DEADPOOL_12" ,
"DEADPOOL_13" ,
"DEADPOOL_14" ,
"DEADPOOL_15" ,
"DEADPOOL_16" ,
"DEADPOOL_17" ,
"DEADPOOL_18" ,
"DEADPOOL_19" ,
"DEADPOOL"
};


char aStorm[][20] = {
"STORM_0" ,
"STORM_1" ,
"STORM_2" ,
"STORM_3" ,
"STORM_4" ,
"STORM_5" ,
"STORM_6" ,
"STORM_7" ,
"STORM_8" ,
"STORM_9" ,
"STORM_10" ,
"STORM_11" ,
"STORM_12" ,
"STORM_13" ,
"STORM_14" ,
"STORM_15" ,
"STORM_16" ,
"STORM_17" ,
"STORM_18" ,
"STORM_19" ,
"STORM"
};


char aSuperSkrull[][20] = {
"SUPERSKRULL_0" ,
"SUPERSKRULL_1" ,
"SUPERSKRULL_2" ,
"SUPERSKRULL_3" ,
"SUPERSKRULL_4" ,
"SUPERSKRULL_5" ,
"SUPERSKRULL_6" ,
"SUPERSKRULL_7" ,
"SUPERSKRULL_8" ,
"SUPERSKRULL_9" ,
"SUPERSKRULL_10" ,
"SUPERSKRULL_11" ,
"SUPERSKRULL_12" ,
"SUPERSKRULL_13" ,
"SUPERSKRULL_14" ,
"SUPERSKRULL_15" ,
"SUPERSKRULL_16" ,
"SUPERSKRULL_17" ,
"SUPERSKRULL_18" ,
"SUPERSKRULL_19" ,
"SUPERSKRULL"
};


char aSentinel[][20] = {
"SENTINEL_0" ,
"SENTINEL_1" ,
"SENTINEL_2" ,
"SENTINEL_3" ,
"SENTINEL_4" ,
"SENTINEL_5" ,
"SENTINEL_6" ,
"SENTINEL_7" ,
"SENTINEL_8" ,
"SENTINEL_9" ,
"SENTINEL_10" ,
"SENTINEL_11" ,
"SENTINEL_12" ,
"SENTINEL_13" ,
"SENTINEL_14" ,
"SENTINEL_15" ,
"SENTINEL_16" ,
"SENTINEL_17" ,
"SENTINEL_18" ,
"SENTINEL_19" ,
"SENTINEL"
};


char aX23[][20] = {
"X23_0" ,
"X23_1" ,
"X23_2" ,
"X23_3" ,
"X23_4" ,
"X23_5" ,
"X23_6" ,
"X23_7" ,
"X23_8" ,
"X23_9" ,
"X23_10" ,
"X23_11" ,
"X23_12" ,
"X23_13" ,
"X23_14" ,
"X23_15" ,
"X23_16" ,
"X23_17" ,
"X23_18" ,
"X23_19" ,
"X23"
};


char aNova[][20] = {
"NOVA_0" ,
"NOVA_1" ,
"NOVA_2" ,
"NOVA_3" ,
"NOVA_4" ,
"NOVA_5" ,
"NOVA_6" ,
"NOVA_7" ,
"NOVA_8" ,
"NOVA_9" ,
"NOVA_10" ,
"NOVA_11" ,
"NOVA_12" ,
"NOVA_13" ,
"NOVA_14" ,
"NOVA_15" ,
"NOVA_16" ,
"NOVA_17" ,
"NOVA_18" ,
"NOVA_19" ,
"NOVA"
};


char aRRaccoon[][20] = {
"RRACCOON_0" ,
"RRACCOON_1" ,
"RRACCOON_2" ,
"RRACCOON_3" ,
"RRACCOON_4" ,
"RRACCOON_5" ,
"RRACCOON_6" ,
"RRACCOON_7" ,
"RRACCOON_8" ,
"RRACCOON_9" ,
"RRACCOON_10" ,
"RRACCOON_11" ,
"RRACCOON_12" ,
"RRACCOON_13" ,
"RRACCOON_14" ,
"RRACCOON_15" ,
"RRACCOON_16" ,
"RRACCOON_17" ,
"RRACCOON_18" ,
"RRACCOON_19" ,
"RRACCOON"
};


char aGhostRider[][20] = {
"GHOSTRIDER_0" ,
"GHOSTRIDER_1" ,
"GHOSTRIDER_2" ,
"GHOSTRIDER_3" ,
"GHOSTRIDER_4" ,
"GHOSTRIDER_5" ,
"GHOSTRIDER_6" ,
"GHOSTRIDER_7" ,
"GHOSTRIDER_8" ,
"GHOSTRIDER_9" ,
"GHOSTRIDER_10" ,
"GHOSTRIDER_11" ,
"GHOSTRIDER_12" ,
"GHOSTRIDER_13" ,
"GHOSTRIDER_14" ,
"GHOSTRIDER_15" ,
"GHOSTRIDER_16" ,
"GHOSTRIDER_17" ,
"GHOSTRIDER_18" ,
"GHOSTRIDER_19" ,
"GHOSTRIDER"
};


char aIronFist[][20] = {
"IRONFIST_0" ,
"IRONFIST_1" ,
"IRONFIST_2" ,
"IRONFIST_3" ,
"IRONFIST_4" ,
"IRONFIST_5" ,
"IRONFIST_6" ,
"IRONFIST_7" ,
"IRONFIST_8" ,
"IRONFIST_9" ,
"IRONFIST_10" ,
"IRONFIST_11" ,
"IRONFIST_12" ,
"IRONFIST_13" ,
"IRONFIST_14" ,
"IRONFIST_15" ,
"IRONFIST_16" ,
"IRONFIST_17" ,
"IRONFIST_18" ,
"IRONFIST_19" ,
"IRONFIST"
};


char aDrStrange[][20] = {
"DRSTRANGE_0" ,
"DRSTRANGE_1" ,
"DRSTRANGE_2" ,
"DRSTRANGE_3" ,
"DRSTRANGE_4" ,
"DRSTRANGE_5" ,
"DRSTRANGE_6" ,
"DRSTRANGE_7" ,
"DRSTRANGE_8" ,
"DRSTRANGE_9" ,
"DRSTRANGE_10" ,
"DRSTRANGE_11" ,
"DRSTRANGE_12" ,
"DRSTRANGE_13" ,
"DRSTRANGE_14" ,
"DRSTRANGE_15" ,
"DRSTRANGE_16" ,
"DRSTRANGE_17" ,
"DRSTRANGE_18" ,
"DRSTRANGE_19" ,
"DRSTRANGE"
};


char aHawkeye[][20] = {
"HAWKEYE_0" ,
"HAWKEYE_1" ,
"HAWKEYE_2" ,
"HAWKEYE_3" ,
"HAWKEYE_4" ,
"HAWKEYE_5" ,
"HAWKEYE_6" ,
"HAWKEYE_7" ,
"HAWKEYE_8" ,
"HAWKEYE_9" ,
"HAWKEYE_10" ,
"HAWKEYE_11" ,
"HAWKEYE_12" ,
"HAWKEYE_13" ,
"HAWKEYE_14" ,
"HAWKEYE_15" ,
"HAWKEYE_16" ,
"HAWKEYE_17" ,
"HAWKEYE_18" ,
"HAWKEYE_19" ,
"HAWKEYE"
};


char aGalactus[][20] = {
"GALACTUS_0" ,
"GALACTUS_1" ,
"GALACTUS_2" ,
"GALACTUS_3" ,
"GALACTUS_4" ,
"GALACTUS_5" ,
"GALACTUS_6" ,
"GALACTUS_7" ,
"GALACTUS_8" ,
"GALACTUS_9" ,
"GALACTUS_10" ,
"GALACTUS_11" ,
"GALACTUS_12" ,
"GALACTUS_13" ,
"GALACTUS_14" ,
"GALACTUS_15" ,
"GALACTUS_16" ,
"GALACTUS_17" ,
"GALACTUS_18" ,
"GALACTUS_19" ,
"GALACTUS"
};



#pragma endregion

#pragma region Old Char Arrays for uChrColorType

char OLDRyu[][20] = {
"RYU_0" ,
"RYU_1" ,
"RYU_2" ,
"RYU_3" ,
"RYU_4" ,
"RYU_5" ,
"RYU_6" ,
"RYU_7" ,
"RYU_8" ,
"RYU"
};


char OLDChunLi[][20] = {
"CHUNLI_0" ,
"CHUNLI_1" ,
"CHUNLI_2" ,
"CHUNLI_3" ,
"CHUNLI_4" ,
"CHUNLI_5" ,
"CHUNLI_6" ,
"CHUNLI_7" ,
"CHUNLI_8" ,
"CHUNLI"
};


char OLDGouki[][20] = {
"GOUKI_0" ,
"GOUKI_1" ,
"GOUKI_2" ,
"GOUKI_3" ,
"GOUKI_4" ,
"GOUKI_5" ,
"GOUKI_6" ,
"GOUKI_7" ,
"GOUKI_8" ,
"GOUKI"
};


char OLDChris[][20] = {
"CHRIS_0" ,
"CHRIS_1" ,
"CHRIS_2" ,
"CHRIS_3" ,
"CHRIS_4" ,
"CHRIS_5" ,
"CHRIS_6" ,
"CHRIS_7" ,
"CHRIS_8" ,
"CHRIS"
};


char OLDWesker[][20] = {
"WESKER_0" ,
"WESKER_1" ,
"WESKER_2" ,
"WESKER_3" ,
"WESKER_4" ,
"WESKER_5" ,
"WESKER_6" ,
"WESKER_7" ,
"WESKER_8" ,
"WESKER"
};


char OLDVJoe[][20] = {
"VJOE_0" ,
"VJOE_1" ,
"VJOE_2" ,
"VJOE_3" ,
"VJOE_4" ,
"VJOE_5" ,
"VJOE_6" ,
"VJOE_7" ,
"VJOE_8" ,
"VJOE"
};


char OLDDante[][20] = {
"DANTE_0" ,
"DANTE_1" ,
"DANTE_2" ,
"DANTE_3" ,
"DANTE_4" ,
"DANTE_5" ,
"DANTE_6" ,
"DANTE_7" ,
"DANTE_8" ,
"DANTE"
};


char OLDTrish[][20] = {
"TRISH_0" ,
"TRISH_1" ,
"TRISH_2" ,
"TRISH_3" ,
"TRISH_4" ,
"TRISH_5" ,
"TRISH_6" ,
"TRISH_7" ,
"TRISH_8" ,
"TRISH"
};


char OLDFrank[][20] = {
"FRANK_0" ,
"FRANK_1" ,
"FRANK_2" ,
"FRANK_3" ,
"FRANK_4" ,
"FRANK_5" ,
"FRANK_6" ,
"FRANK_7" ,
"FRANK_8" ,
"FRANK"
};


char OLDSpencer[][20] = {
"SPENCER_0" ,
"SPENCER_1" ,
"SPENCER_2" ,
"SPENCER_3" ,
"SPENCER_4" ,
"SPENCER_5" ,
"SPENCER_6" ,
"SPENCER_7" ,
"SPENCER_8" ,
"SPENCER"
};


char OLDArthur[][20] = {
"ARTHUR_0" ,
"ARTHUR_1" ,
"ARTHUR_2" ,
"ARTHUR_3" ,
"ARTHUR_4" ,
"ARTHUR_5" ,
"ARTHUR_6" ,
"ARTHUR_7" ,
"ARTHUR_8" ,
"ARTHUR"
};


char OLDAmaterasu[][20] = {
"AMATERASU_0" ,
"AMATERASU_1" ,
"AMATERASU_2" ,
"AMATERASU_3" ,
"AMATERASU_4" ,
"AMATERASU_5" ,
"AMATERASU_6" ,
"AMATERASU_7" ,
"AMATERASU_8" ,
"AMATERASU"
};


char OLDZero[][20] = {
"ZERO_0" ,
"ZERO_1" ,
"ZERO_2" ,
"ZERO_3" ,
"ZERO_4" ,
"ZERO_5" ,
"ZERO_6" ,
"ZERO_7" ,
"ZERO_8" ,
"ZERO"
};


char OLDTron[][20] = {
"TRON_0" ,
"TRON_1" ,
"TRON_2" ,
"TRON_3" ,
"TRON_4" ,
"TRON_5" ,
"TRON_6" ,
"TRON_7" ,
"TRON_8" ,
"TRON"
};


char OLDMorrigan[][20] = {
"MORRIGAN_0" ,
"MORRIGAN_1" ,
"MORRIGAN_2" ,
"MORRIGAN_3" ,
"MORRIGAN_4" ,
"MORRIGAN_5" ,
"MORRIGAN_6" ,
"MORRIGAN_7" ,
"MORRIGAN_8" ,
"MORRIGAN"
};


char OLDLeiLei[][20] = {
"LEILEI_0" ,
"LEILEI_1" ,
"LEILEI_2" ,
"LEILEI_3" ,
"LEILEI_4" ,
"LEILEI_5" ,
"LEILEI_6" ,
"LEILEI_7" ,
"LEILEI_8" ,
"LEILEI"
};


char OLDFelicia[][20] = {
"FELICIA_0" ,
"FELICIA_1" ,
"FELICIA_2" ,
"FELICIA_3" ,
"FELICIA_4" ,
"FELICIA_5" ,
"FELICIA_6" ,
"FELICIA_7" ,
"FELICIA_8" ,
"FELICIA"
};


char OLDCViper[][20] = {
"CVIPER_0" ,
"CVIPER_1" ,
"CVIPER_2" ,
"CVIPER_3" ,
"CVIPER_4" ,
"CVIPER_5" ,
"CVIPER_6" ,
"CVIPER_7" ,
"CVIPER_8" ,
"CVIPER"
};


char OLDHaggar[][20] = {
"HAGGAR_0" ,
"HAGGAR_1" ,
"HAGGAR_2" ,
"HAGGAR_3" ,
"HAGGAR_4" ,
"HAGGAR_5" ,
"HAGGAR_6" ,
"HAGGAR_7" ,
"HAGGAR_8" ,
"HAGGAR"
};


char OLDJill[][20] = {
"JILL_0" ,
"JILL_1" ,
"JILL_2" ,
"JILL_3" ,
"JILL_4" ,
"JILL_5" ,
"JILL_6" ,
"JILL_7" ,
"JILL_8" ,
"JILL"
};


char OLDHiryu[][20] = {
"HIRYU_0" ,
"HIRYU_1" ,
"HIRYU_2" ,
"HIRYU_3" ,
"HIRYU_4" ,
"HIRYU_5" ,
"HIRYU_6" ,
"HIRYU_7" ,
"HIRYU_8" ,
"HIRYU"
};


char OLDVergil[][20] = {
"VERGIL_0" ,
"VERGIL_1" ,
"VERGIL_2" ,
"VERGIL_3" ,
"VERGIL_4" ,
"VERGIL_5" ,
"VERGIL_6" ,
"VERGIL_7" ,
"VERGIL_8" ,
"VERGIL"
};


char OLDNaruhodo[][20] = {
"NARUHODO_0" ,
"NARUHODO_1" ,
"NARUHODO_2" ,
"NARUHODO_3" ,
"NARUHODO_4" ,
"NARUHODO_5" ,
"NARUHODO_6" ,
"NARUHODO_7" ,
"NARUHODO_8" ,
"NARUHODO"
};


char OLDRedArremer[][20] = {
"REDARREMER_0" ,
"REDARREMER_1" ,
"REDARREMER_2" ,
"REDARREMER_3" ,
"REDARREMER_4" ,
"REDARREMER_5" ,
"REDARREMER_6" ,
"REDARREMER_7" ,
"REDARREMER_8" ,
"REDARREMER"
};


char OLDNemesis[][20] = {
"NEMESIS_0" ,
"NEMESIS_1" ,
"NEMESIS_2" ,
"NEMESIS_3" ,
"NEMESIS_4" ,
"NEMESIS_5" ,
"NEMESIS_6" ,
"NEMESIS_7" ,
"NEMESIS_8" ,
"NEMESIS"
};


char OLDSpiderMan[][20] = {
"SPIDERMAN_0" ,
"SPIDERMAN_1" ,
"SPIDERMAN_2" ,
"SPIDERMAN_3" ,
"SPIDERMAN_4" ,
"SPIDERMAN_5" ,
"SPIDERMAN_6" ,
"SPIDERMAN_7" ,
"SPIDERMAN_8" ,
"SPIDERMAN"
};


char OLDCapAmerica[][20] = {
"CAPAMERICA_0" ,
"CAPAMERICA_1" ,
"CAPAMERICA_2" ,
"CAPAMERICA_3" ,
"CAPAMERICA_4" ,
"CAPAMERICA_5" ,
"CAPAMERICA_6" ,
"CAPAMERICA_7" ,
"CAPAMERICA_8" ,
"CAPAMERICA"
};


char OLDWolverine[][20] = {
"WOLVERINE_0" ,
"WOLVERINE_1" ,
"WOLVERINE_2" ,
"WOLVERINE_3" ,
"WOLVERINE_4" ,
"WOLVERINE_5" ,
"WOLVERINE_6" ,
"WOLVERINE_7" ,
"WOLVERINE_8" ,
"WOLVERINE"
};


char OLDMagneto[][20] = {
"MAGNETO_0" ,
"MAGNETO_1" ,
"MAGNETO_2" ,
"MAGNETO_3" ,
"MAGNETO_4" ,
"MAGNETO_5" ,
"MAGNETO_6" ,
"MAGNETO_7" ,
"MAGNETO_8" ,
"MAGNETO"
};


char OLDHulk[][20] = {
"HULK_0" ,
"HULK_1" ,
"HULK_2" ,
"HULK_3" ,
"HULK_4" ,
"HULK_5" ,
"HULK_6" ,
"HULK_7" ,
"HULK_8" ,
"HULK"
};


char OLDSheHulk[][20] = {
"SHEHULK_0" ,
"SHEHULK_1" ,
"SHEHULK_2" ,
"SHEHULK_3" ,
"SHEHULK_4" ,
"SHEHULK_5" ,
"SHEHULK_6" ,
"SHEHULK_7" ,
"SHEHULK_8" ,
"SHEHULK"
};


char OLDTaskMaster[][20] = {
"TASKMASTER_0" ,
"TASKMASTER_1" ,
"TASKMASTER_2" ,
"TASKMASTER_3" ,
"TASKMASTER_4" ,
"TASKMASTER_5" ,
"TASKMASTER_6" ,
"TASKMASTER_7" ,
"TASKMASTER_8" ,
"TASKMASTER"
};


char OLDIronMan[][20] = {
"IRONMAN_0" ,
"IRONMAN_1" ,
"IRONMAN_2" ,
"IRONMAN_3" ,
"IRONMAN_4" ,
"IRONMAN_5" ,
"IRONMAN_6" ,
"IRONMAN_7" ,
"IRONMAN_8" ,
"IRONMAN"
};


char OLDThor[][20] = {
"THOR_0" ,
"THOR_1" ,
"THOR_2" ,
"THOR_3" ,
"THOR_4" ,
"THOR_5" ,
"THOR_6" ,
"THOR_7" ,
"THOR_8" ,
"THOR"
};


char OLDDrDoom[][20] = {
"DRDOOM_0" ,
"DRDOOM_1" ,
"DRDOOM_2" ,
"DRDOOM_3" ,
"DRDOOM_4" ,
"DRDOOM_5" ,
"DRDOOM_6" ,
"DRDOOM_7" ,
"DRDOOM_8" ,
"DRDOOM"
};


char OLDPhoenix[][20] = {
"PHOENIX_0" ,
"PHOENIX_1" ,
"PHOENIX_2" ,
"PHOENIX_3" ,
"PHOENIX_4" ,
"PHOENIX_5" ,
"PHOENIX_6" ,
"PHOENIX_7" ,
"PHOENIX_8" ,
"PHOENIX"
};


char OLDShuma[][20] = {
"SHUMA_0" ,
"SHUMA_1" ,
"SHUMA_2" ,
"SHUMA_3" ,
"SHUMA_4" ,
"SHUMA_5" ,
"SHUMA_6" ,
"SHUMA_7" ,
"SHUMA_8" ,
"SHUMA"
};


char OLDModok[][20] = {
"MODOK_0" ,
"MODOK_1" ,
"MODOK_2" ,
"MODOK_3" ,
"MODOK_4" ,
"MODOK_5" ,
"MODOK_6" ,
"MODOK_7" ,
"MODOK_8" ,
"MODOK"
};


char OLDDormammu[][20] = {
"DORMAMMU_0" ,
"DORMAMMU_1" ,
"DORMAMMU_2" ,
"DORMAMMU_3" ,
"DORMAMMU_4" ,
"DORMAMMU_5" ,
"DORMAMMU_6" ,
"DORMAMMU_7" ,
"DORMAMMU_8" ,
"DORMAMMU"
};


char OLDDeadpool[][20] = {
"DEADPOOL_0" ,
"DEADPOOL_1" ,
"DEADPOOL_2" ,
"DEADPOOL_3" ,
"DEADPOOL_4" ,
"DEADPOOL_5" ,
"DEADPOOL_6" ,
"DEADPOOL_7" ,
"DEADPOOL_8" ,
"DEADPOOL"
};


char OLDStorm[][20] = {
"STORM_0" ,
"STORM_1" ,
"STORM_2" ,
"STORM_3" ,
"STORM_4" ,
"STORM_5" ,
"STORM_6" ,
"STORM_7" ,
"STORM_8" ,
"STORM"
};


char OLDSuperSkrull[][20] = {
"SUPERSKRULL_0" ,
"SUPERSKRULL_1" ,
"SUPERSKRULL_2" ,
"SUPERSKRULL_3" ,
"SUPERSKRULL_4" ,
"SUPERSKRULL_5" ,
"SUPERSKRULL_6" ,
"SUPERSKRULL_7" ,
"SUPERSKRULL_8" ,
"SUPERSKRULL"
};


char OLDSentinel[][20] = {
"SENTINEL_0" ,
"SENTINEL_1" ,
"SENTINEL_2" ,
"SENTINEL_3" ,
"SENTINEL_4" ,
"SENTINEL_5" ,
"SENTINEL_6" ,
"SENTINEL_7" ,
"SENTINEL_8" ,
"SENTINEL"
};


char OLDX23[][20] = {
"X23_0" ,
"X23_1" ,
"X23_2" ,
"X23_3" ,
"X23_4" ,
"X23_5" ,
"X23_6" ,
"X23_7" ,
"X23_8" ,
"X23"
};


char OLDNova[][20] = {
"NOVA_0" ,
"NOVA_1" ,
"NOVA_2" ,
"NOVA_3" ,
"NOVA_4" ,
"NOVA_5" ,
"NOVA_6" ,
"NOVA_7" ,
"NOVA_8" ,
"NOVA"
};


char OLDRRaccoon[][20] = {
"RRACCOON_0" ,
"RRACCOON_1" ,
"RRACCOON_2" ,
"RRACCOON_3" ,
"RRACCOON_4" ,
"RRACCOON_5" ,
"RRACCOON_6" ,
"RRACCOON_7" ,
"RRACCOON_8" ,
"RRACCOON"
};


char OLDGhostRider[][20] = {
"GHOSTRIDER_0" ,
"GHOSTRIDER_1" ,
"GHOSTRIDER_2" ,
"GHOSTRIDER_3" ,
"GHOSTRIDER_4" ,
"GHOSTRIDER_5" ,
"GHOSTRIDER_6" ,
"GHOSTRIDER_7" ,
"GHOSTRIDER_8" ,
"GHOSTRIDER"
};


char OLDIronFist[][20] = {
"IRONFIST_0" ,
"IRONFIST_1" ,
"IRONFIST_2" ,
"IRONFIST_3" ,
"IRONFIST_4" ,
"IRONFIST_5" ,
"IRONFIST_6" ,
"IRONFIST_7" ,
"IRONFIST_8" ,
"IRONFIST"
};


char OLDDrStrange[][20] = {
"DRSTRANGE_0" ,
"DRSTRANGE_1" ,
"DRSTRANGE_2" ,
"DRSTRANGE_3" ,
"DRSTRANGE_4" ,
"DRSTRANGE_5" ,
"DRSTRANGE_6" ,
"DRSTRANGE_7" ,
"DRSTRANGE_8" ,
"DRSTRANGE"
};


char OLDHawkeye[][20] = {
"HAWKEYE_0" ,
"HAWKEYE_1" ,
"HAWKEYE_2" ,
"HAWKEYE_3" ,
"HAWKEYE_4" ,
"HAWKEYE_5" ,
"HAWKEYE_6" ,
"HAWKEYE_7" ,
"HAWKEYE_8" ,
"HAWKEYE"
};


char OLDGalactus[][20] = {
"GALACTUS_0" ,
"GALACTUS_1" ,
"GALACTUS_2" ,
"GALACTUS_3" ,
"GALACTUS_4" ,
"GALACTUS_5" ,
"GALACTUS_6" ,
"GALACTUS_7" ,
"GALACTUS_8" ,
"GALACTUS"
};



#pragma endregion

#pragma region Original Char Aray Pointers
uint64_t aCharArray00 = 0x140D024B0;
uint64_t aCharArray01 = 0x140D02500;
uint64_t aCharArray02 = 0x140D02550;
uint64_t aCharArray03 = 0x140D025A0;
uint64_t aCharArray04 = 0x140D025F0;
uint64_t aCharArray05 = 0x140D02640;
uint64_t aCharArray06 = 0x140D02690;
uint64_t aCharArray07 = 0x140D026E0;
uint64_t aCharArray08 = 0x140D02730;
uint64_t aCharArray09 = 0x140D02780;
uint64_t aCharArray10 = 0x140D027D0;
uint64_t aCharArray11 = 0x140D02820;
uint64_t aCharArray12 = 0x140D02870;
uint64_t aCharArray13 = 0x140D028C0;
uint64_t aCharArray14 = 0x140D02910;
uint64_t aCharArray15 = 0x140D02960;
uint64_t aCharArray16 = 0x140D029B0;
uint64_t aCharArray17 = 0x140D02A00;
uint64_t aCharArray18 = 0x140D02A50;
uint64_t aCharArray19 = 0x140D02AA0;
uint64_t aCharArray20 = 0x140D02AF0;
uint64_t aCharArray21 = 0x140D02B40;
uint64_t aCharArray22 = 0x140D02B90;
uint64_t aCharArray23 = 0x140D02BE0;
uint64_t aCharArray24 = 0x140D02C30;
uint64_t aCharArray25 = 0x140D02C80;
uint64_t aCharArray26 = 0x140D02CD0;
uint64_t aCharArray27 = 0x140D02D20;
uint64_t aCharArray28 = 0x140D02D70;
uint64_t aCharArray29 = 0x140D02DC0;
uint64_t aCharArray30 = 0x140D02E10;
uint64_t aCharArray31 = 0x140D02E60;
uint64_t aCharArray32 = 0x140D02EB0;
uint64_t aCharArray33 = 0x140D02F00;
uint64_t aCharArray34 = 0x140D02F50;
uint64_t aCharArray35 = 0x140D02FA0;
uint64_t aCharArray36 = 0x140D02FF0;
uint64_t aCharArray37 = 0x140D03040;
uint64_t aCharArray38 = 0x140D03090;
uint64_t aCharArray39 = 0x140D030E0;
uint64_t aCharArray40 = 0x140D03130;
uint64_t aCharArray41 = 0x140D03180;
uint64_t aCharArray42 = 0x140D031D0;
uint64_t aCharArray43 = 0x140D03220;
uint64_t aCharArray44 = 0x140D03270;
uint64_t aCharArray45 = 0x140D032C0;
uint64_t aCharArray46 = 0x140D03310;
uint64_t aCharArray47 = 0x140D03360;
uint64_t aCharArray48 = 0x140D033B0;
uint64_t aCharArray49 = 0x140D03400;
uint64_t aCharArray50 = 0x140D03450;

#pragma endregion

bool CheckGame()
{
	char* gameName = (char*)(_addr(0x140B12D10));

	if (strcmp(gameName, "umvc3") == 0)
	{
		return true;
	}
	else
	{
		MessageBoxA(0, "Sorry!\nColor Expansion only supports the most recent(or the version released from April 2017 - Somewhere in 2026) Steam Executable of Ultimate Marvel vs Capcom 3.", 0, MB_ICONINFORMATION);
		return false;
	}
}

#pragma region ProtectedWrites

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

#pragma endregion

//Originally based on HeathHowren's PatterScanning function. Adjusted to better suit the target game, which is x64.

static inline uint8_t ReadHexNibble(char c) {
	if (c >= '0' && c <= '9') 
	{
		return c - '0';
	}
	c &= ~0x20;
	if (c >= 'A' && c <= 'F') 
	{
		return c - 'A' + 0xA;
	}
	return 0;
}

static inline bool ParseNextCharacter(const char*& pat, uint8_t& outByte) {
	
	//Skip leading spaces.
	while (*pat == ' ') ++pat;

	if (!*pat) 
	{
		//The pattern's end.
		return false;
	}

	bool wild = (pat[0] == '?');

	if (!wild) 
	{
		outByte = (ReadHexNibble(pat[0]) << 4) | ReadHexNibble(pat[1]);
	}

	//Advances a character and past any trailing spaces.
	if (pat[0] == '?' && pat[1] != '?' && pat[1] != ' ' && pat[1] != '\0')
	{
		pat += 1;
	}
	else if (pat[0] == '?' && (pat[1] == '?'))
	{
		pat += 2;
	}
	else if (pat[0] == '?')
	{
		pat += 1;
	}
	else
	{
		pat += 2;
	}

	while (*pat == ' ') 
	{
		//Skip whatever trailing spaces remain.
		++pat;
	}
	return wild;
}

uint64_t FindBytePattern(uint64_t baseAddr, size_t ScanSize, const char* DataPattern) 
{
	//Some checking of validity.
	if (baseAddr <= 0 || ScanSize <= 0 || !DataPattern)
	{
		return 0;
	}

	const char* CPattern = DataPattern;
	uint64_t    FirstMatchLocation = 0;

	for (uint64_t pCur = baseAddr; pCur < (baseAddr + ScanSize); ++pCur)
	{
		while (*CPattern == ' ')
		{
			++CPattern;
		}
		if (!*CPattern)
		{
			break;
		}

		uint8_t    patByte = 0;
		const char* patSave = CPattern;
		bool wild = ParseNextCharacter(CPattern, patByte);
		uint8_t curByte = *reinterpret_cast<uint8_t*>(pCur);

		if (wild || curByte == patByte) 
		{
			if (!FirstMatchLocation) FirstMatchLocation = pCur;
			{
				if (!*CPattern) 
				{
					break;
				}
			}
		}
		else {
			//Resets on mismatch.
			CPattern = DataPattern;
			FirstMatchLocation = 0;
		}
	}


	if (!FirstMatchLocation) 
	{ 
		return 0; 
	}

	return FirstMatchLocation;

}

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
		call qword ptr[ScrollerUpdater]
		jmp qword ptr[ForTheCSSColorCounter_JmpBack]
	}
}

//This is to ensure the function doesn't spit out negative numbers for the number it's meant to be comparing to.
__attribute__((naked)) void FUN_1402B9AD0()
{
	__asm
	{
		xor eax, eax
		cmp r8d, [TCCForComparison]
		jnl[Fun_1402B9AE2]
		test r8d, r8d
		cmovs r8d, eax
		mov eax, r8d
		repe ret
	}
}

__attribute__((naked)) void ForTheLicenseBoardPart1()
{
	__asm
	{
		mov ecx, r12d
		call[FUN_140058F90]
		lea rdx, [aUiChsChsFaceAC]
		lea rcx, [rbp + 0x17F8]
		mov r8, rax
		mov r9d, r14d
		call[FUN_1404C4410]
		call[FUN_140001B10]
		lea rcx, [rbp + 0x17F8]
		mov rdi, [rax]
		mov rbx, rax
		call[FUN_14001DCA0]
		lea rcx, [rbp + 0x15C0]
		mov r9b, 0x01
		xor edx, edx
		mov r8, rax
		call[FUN_140455260]
		mov rcx, rax
		call[FUN_140151080]
		lea rdx, [FUN_140E17570]
		mov r9d, 0x80
		mov r8, rax
		mov rcx, rbx
		call qword ptr[rdi + 0x60]
		inc r14d
		lea r15, [r15 + 0x08]
		mov[r15 - 0x08], rax
		cmp r14d, [TCCForComparison]
		jb[ForTheLicenseBoardPart1]
		jmp qword ptr[BACKTOFUN_14041AA1B]
	}
}

void UpdateThePointerValues()
{
	uChrColorType_vftableAddr = *((uint64_t*)uChrColorType_vftableAddr);
}

__attribute__((naked)) void FUN_14035FEF0()
{
	__asm
	{
		lea rcx, dword ptr[uChrColorType_TypeInfo]
		jmp     sub_14045D4F0
	}
}

__attribute__((naked)) void FUN_14035F7E0()
{
	__asm
	{
		mov[rsp + 0x08], rbx
		mov[rsp + 0x10], rbp
		mov[rsp + 0x18], rsi
		push rdi
		sub rsp, 0x20
		mov esi, edx
		mov rbp, rcx
		//call umvc3.exe+35FEF0
	}
}

//This is to try and get the game to allocate more room for uChrColorType when creating it.
__attribute__((naked)) void FUN_140A29BF0()
{
	__asm
	{
		sub rsp, 0x38
		call qword ptr[0x140321120]
		lea rdx, [0x140B3B0E0] //uChrColorType
		lea rcx, [0x140D5B848] //uChrColorType_TypeInfo
		mov r8, rax
		xor eax, eax
		//mov r9d, 0x000006C8 //The size of the old data type.
		mov r9d, 0x1050 //The size of the new data type.
		mov[rsp + 0x28], eax
		mov[rsp + 0x20], eax
		call qword ptr[0x14035F6F0]
		lea rcx, [0x140A53E20]
		add rsp, 0x38
		jmp qword ptr[0x1409A1564]
		int 3
		movss xmm0, [0x140D02448]
		movss[0x140D02454], xmm0
		retn
	}
}

__attribute__((naked)) void OLD_140A29BF0()
{
	__asm
	{
		sub rsp, 0x38
		call qword ptr[0x140321120]
		lea rdx, [0x140B3B0E0] //uChrColorType
		lea rcx, [0x140D5B848] //uChrColorType_TypeInfo
		mov r8, rax
		xor eax, eax
		mov r9d, 0x6C8 //The size of the data type.
		mov[rsp + 0x28], eax
		mov[rsp + 0x20], eax
		call qword ptr[0x14035F6F0]
		lea rcx, [0x140A53E20]
		add rsp, 0x38
		jmp qword ptr[0x1409A1564]
		int 3
		movss xmm0, [0x140D02448]
		movss[0x140D02454], xmm0
		retn
	}
}

//This one is an attempt to update how the game defines uChrColorType. Looks like some sort of constructor.
__attribute__((naked)) void FUN_14035F730()
{
	__asm
	{

		//push rbx
		sub rsp, 0x20
		mov rbx, rcx
		call qword ptr[uUiBaseRelatedAddr]//is this calling uUiBase? it seems to be writing its vftable to the location that was in rcx.
		mov rax, [uChrColorType_vftableAddr]
		lea rcx, [rbx + 0x48]
		mov r9, ForTheRGBStuffPart1//Just decided to copy the raw value of the thing it originally pointed to.
		mov edx, 0x4
		mov r8d, 0x410 //Estimated size of the allocated data for the color codes? 52*8 = 416/1A0.
		//mov r8d, 0x1A0 Original Code
		mov[rbx], rax //Overwrites uUiBase's vftaddress with uChrColorType's vftable address as it's in rax at this point in the code.
		call qword ptr[MaybeByteHandler]
		lea rax, [rbx + 0x4C]//Seems to go to the location where uChrColorTable will be built + 0x4C.
		mov edx, 0x34
		nop dword ptr[rax + 0x00]

		LOC_14035F770: //label attempt borrowed from IDA. Does this iterate for 51 times to account for the whole roster...?
		mov ecx, [DefaultRGBValue]//Seems to fill in 4 bytes with 0xFF000000, and this runs once for each color.
			lea rax, [rax + 0x50]//Determines the endpoint for the writing.
			//ea rax, [rax + 0x20] <- Original Code.

			//This loops for each color for a character.
			mov[rax - 0x54], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x50], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x4C], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x48], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x44], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x40], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x3C], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x38], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x34], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x30], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x2C], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x28], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x24], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x20], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x1C], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x18], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x14], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x10], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0xC], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x8], ecx
			dec rdx
			jne LOC_14035F770
			mov rax, rbx
			add rsp, 0x20//Actually relates to pointers?
			pop rbx
			retn

	}
}

__attribute__((naked)) void OLD_14035F730()
{
	__asm
	{

		push rbx
		sub rsp, 0x20
		mov rbx, rcx
		call qword ptr[uUiBaseRelatedAddr]//is this calling uUiBase? it seems to be writing its vftable to the location that was in rcx.
		mov rax, [uChrColorType_vftableAddr]
		lea rcx, [rbx + 0x48]
		mov r9, ForTheRGBStuffPart1//Just decided to copy the raw value of the thing it originally pointed to.
		mov edx, 0x4
		mov r8d, 0x1A0 //Estimated size of the allocated data for the color codes? 52*8 = 416/1A0.
		mov[rbx], rax //Overwrites uUiBase's vftaddress with uChrColorType's vftable address as it's in rax at this point in the code.
		call qword ptr[MaybeByteHandler]
		lea rax, [rbx + 0x4C]//Seems to go to the location where uChrColorTable will be built + 0x4C.
		mov edx, 0x34
		nop dword ptr[rax + 0x00]

		LOC_14035F770: //label attempt borrowed from IDA. Does this iterate for 51 times to account for the whole roster...?
		mov ecx, [DefaultRGBValue]//Seems to fill in 4 bytes with 0xFF000000, and this runs once for each color.
			lea rax, [rax + 0x20]//Determines the endpoint for the writing.
			//ea rax, [rax + 0x20] <- Original Code.
			//nop dword ptr [rax+00]
			//This loops for each color for a character.
			mov[rax - 0x24], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x20], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x1C], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x18], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x14], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x10], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0xC], ecx
			mov ecx, [DefaultRGBValue]
			mov[rax - 0x8], ecx
			dec rdx
			jne LOC_14035F770
			mov rax, rbx
			add rsp, 0x20//Actually relates to pointers?
			pop rbx
			retn

	}
}

//Unfortunately have to rewrite the function to point to our new char* arrays with all the border names.
__attribute__((naked)) void FUN_14035F890()
{
	__asm
	{
		mov[rsp + 0x08], rbx
		push rdi
		sub rsp, 0x20
		//sub rsp, 0x20 <- Original Code
		mov rbx, rdx
		mov rdi, rcx
		call qword ptr[YetAnotherFunction]
		mov rax, [rdi]
		lea r8, [aRyu]
		mov r9d, 0x01
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aChunLi]
		mov r9d, 0x02
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aGouki]
		mov r9d, 0x03
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aChris]
		mov r9d, 0x04
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aWesker]
		mov r9d, 0x05
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aVJoe]
		mov r9d, 0x06
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aDante]
		mov r9d, 0x07
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aTrish]
		mov r9d, 0x08
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aFrank]
		mov r9d, 0x09
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aSpencer]
		mov r9d, 0x0A
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aArthur]
		mov r9d, 0x0B
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aAmaterasu]
		mov r9d, 0x0C
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aZero]
		mov r9d, 0x0D
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aTron]
		mov r9d, 0x0E
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aMorrigan]
		mov r9d, 0x0F
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aLeiLei]
		mov r9d, 0x10
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aFelicia]
		mov r9d, 0x11
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCViper]
		mov r9d, 0x12
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aHaggar]
		mov r9d, 0x13
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aJill]
		mov r9d, 0x14
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aHiryu]
		mov r9d, 0x15
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aVergil]
		mov r9d, 0x16
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aNaruhodo]
		mov r9d, 0x17
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aRedArremer]
		mov r9d, 0x18
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aNemesis]
		mov r9d, 0x19
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aSpiderMan]
		mov r9d, 0x1A
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		mov r9d, 0x1B
		lea r8, [aCapAmerica]
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aWolverine]
		mov r9d, 0x1C
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aMagneto]
		mov r9d, 0x1D
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aHulk]
		mov r9d, 0x1E
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aSheHulk]
		mov r9d, 0x1F
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aTaskMaster]
		mov r9d, 0x20
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aIronMan]
		mov r9d, 0x21
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aThor]
		mov r9d, 0x22
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aDrDoom]
		mov r9d, 0x23
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aPhoenix]
		mov r9d, 0x24
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aShuma]
		mov r9d, 0x25
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aModok]
		mov r9d, 0x26
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aDormammu]
		mov r9d, 0x27
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aDeadpool]
		mov r9d, 0x28
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aStorm]
		mov r9d, 0x29
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aSuperSkrull]
		mov r9d, 0x2A
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aSentinel]
		mov r9d, 0x2B
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aX23]
		mov r9d, 0x2C
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aNova]
		mov r9d, 0x2D
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aRRaccoon]
		mov r9d, 0x2E
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aGhostRider]
		mov r9d, 0x2F
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aIronFist]
		mov r9d, 0x30
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aDrStrange]
		mov r9d, 0x31
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aHawkeye]
		mov r9d, 0x32
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aGalactus]
		mov r9d, 0x33
		mov rdx, rbx
		mov rcx, rdi
		mov rbx, [rsp + 30]
		add rsp, 20
		pop rdi
		jmp qword ptr[rax + 0x88]

	}

}

__attribute__((naked)) void OLD_14035F890()
{
	__asm
	{
		mov[rsp + 0x08], rbx
		push rdi
		sub rsp, 0x20
		//sub rsp, 0x20 <- Original Code
		mov rbx, rdx
		mov rdi, rcx
		call qword ptr[YetAnotherFunction]
		mov rax, [rdi]
		lea r8, [aCharArray00]
		mov r9d, 0x01
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray01]
		mov r9d, 0x02
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray02]
		mov r9d, 0x03
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray03]
		mov r9d, 0x04
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray04]
		mov r9d, 0x05
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray05]
		mov r9d, 0x06
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray06]
		mov r9d, 0x07
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray07]
		mov r9d, 0x08
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray08]
		mov r9d, 0x09
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray09]
		mov r9d, 0x0A
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray10]
		mov r9d, 0x0B
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray11]
		mov r9d, 0x0C
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray12]
		mov r9d, 0x0D
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray13]
		mov r9d, 0x0E
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray14]
		mov r9d, 0x0F
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray15]
		mov r9d, 0x10
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray16]
		mov r9d, 0x11
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray17]
		mov r9d, 0x12
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray18]
		mov r9d, 0x13
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray19]
		mov r9d, 0x14
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray20]
		mov r9d, 0x15
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray21]
		mov r9d, 0x16
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray22]
		mov r9d, 0x17
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray23]
		mov r9d, 0x18
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray24]
		mov r9d, 0x19
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray25]
		mov r9d, 0x1A
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		mov r9d, 0x1B
		lea r8, [aCharArray26]
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray27]
		mov r9d, 0x1C
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray28]
		mov r9d, 0x1D
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray29]
		mov r9d, 0x1E
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray30]
		mov r9d, 0x1F
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray31]
		mov r9d, 0x20
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray32]
		mov r9d, 0x21
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray33]
		mov r9d, 0x22
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray34]
		mov r9d, 0x23
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray35]
		mov r9d, 0x24
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray36]
		mov r9d, 0x25
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray37]
		mov r9d, 0x26
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray38]
		mov r9d, 0x27
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray39]
		mov r9d, 0x28
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray40]
		mov r9d, 0x29
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray41]
		mov r9d, 0x2A
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray42]
		mov r9d, 0x2B
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray43]
		mov r9d, 0x2C
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray44]
		mov r9d, 0x2D
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray45]
		mov r9d, 0x2E
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray46]
		mov r9d, 0x2F
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray47]
		mov r9d, 0x30
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray48]
		mov r9d, 0x31
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray49]
		mov r9d, 0x32
		mov rdx, rbx
		mov rcx, rdi
		call qword ptr[rax + 0x88]
		mov rax, [rdi]
		lea r8, [aCharArray50]
		mov r9d, 0x33
		mov rdx, rbx
		mov rcx, rdi
		mov rbx, [rsp + 30]
		add rsp, 20
		pop rdi
		jmp qword ptr[rax + 0x88]

	}

}

//Have to remake this function because one of the commands is too big.
__attribute__((naked)) void FUN_14035FF60()
{
	__asm
	{

		sub rsp, 0x28
		mov edx, 0x10
		mov ecx, 0x1050
		call qword ptr SomeFunction//0x14035F7E0
		test rax, rax
		je LOC_14035FF84
		mov rcx, rax
		add rsp, 0x28
		jmp FUN_14035F730

		LOC_14035FF84 :

		add rsp, 0x28
			ret


	}
}

__attribute__((naked)) void OLD_14035FF60()
{
	__asm
	{

		sub rsp, 0x28
		mov edx, 0x10
		mov ecx, 0x6C8
		call qword ptr SomeFunction//0x14035F7E0
		test rax, rax
		je LOC_14035FF84
		mov rcx, rax
		add rsp, 0x28
		jmp OLD_14035F730

		LOC_14035FF84 :

		add rsp, 0x28
			ret


	}
}

__attribute__((naked)) void ForAttractMode()
{
	__asm
	{
	
		//Function that determines random colors.

		mov[rsp + 0x08], rbx
		mov[rsp + 0x10], rbp
		mov[rsp + 0x18], rsi
		push rdi
		push r14
		push r15
		sub rsp, 0x20
		mov r15, rcx
		mov dword ptr[rcx + 0x44], 0x0000FFFF
		mov dword ptr[rcx + 0x0000009C], 0x0000FFFF
		mov dword ptr[rcx + 0x000000F4], 0x0000FFFF
		mov dword ptr[rcx + 0x0000014C], 0x0000FFFF
		mov dword ptr[rcx + 0x000001A4], 0x0000FFFF
		mov dword ptr[rcx + 0x000001FC], 0x0000FFFF
		call FUN_14024E300
		call FUN_1400046D0
		lea rsi, [r15 + 0x38]
		mov r14, rax
		lea rdi, [r15 + 0x000005B0]
		mov rbx, rsi
		mov ebp, 0x6

		LOC_14024D804:

		mov edx, [rdi]
			mov rcx, rbx
			call FUN_140146560
			mov rcx, r14
			call FUN_14000AF80
			mov ecx, eax
			//Original Code was here.
			//mov eax, 0xAAAAAAAB
			//mul ecx
			//shr edx, 0x02
			//lea eax, [rdx + rdx * 2]
			//add eax, eax
			//sub ecx, eax
			//mov edx, ecx
			
			mov ecx, eax
			mov eax, ecx
			xor edx, edx
			mov ecx, [RandomColorLimit]
			div ecx

			mov rcx, rbx
			call FUN_1401461E0
			add rbx, 0x58
			lea rdi, [rdi + 0x04]
			dec rbp
			jne LOC_14024D804
			xor r14d, r14d

			LOC_14024D843 :

		xor ebx, ebx

			LOC_14024D845 :

		cmp r14d, ebx
			je LOC_14024D885
			movsxd  rbp, ebx
			lea rcx, [r15 + 0x38]
			imul rbp, rbp, 0x58
			add rcx, rbp
			call FUN_140417C10
			mov rcx, rsi
			mov edi, eax
			call FUN_140417C10
			cmp eax, edi
			jne LOC_14024D885
			lea rcx, [r15 + 0x38]
			add rcx, rbp
			call FUN_1406CD4E0
			mov rcx, rsi
			mov edi, eax
			call FUN_1406CD4E0
			cmp eax, edi
			je LOC_14024D88E

			LOC_14024D885 :

		inc ebx
			cmp ebx, 0x06
			jl LOC_14024D845
			jmp LOC_14024D8AB

			LOC_14024D88E :

		mov rcx, rsi
			call FUN_1406CD4E0
			mov rcx, rsi
			test eax, eax
			je LOC_14024D8A1
			xor edx, edx
			jmp LOC_14024D8A6

			LOC_14024D8A1 :

		mov edx, 0x00000001

			LOC_14024D8A6 :

			call FUN_1401461E0

			LOC_14024D8AB :

		inc r14d
			add rsi, 0x58
			cmp r14d, 0x06
			jl LOC_14024D843
			call getsGameUI
			mov edx, 0x00000013
			mov rcx, rax
			call BuildStageSelectArray//0x1402BC5D0
			mov rcx, r15
			mov edx, eax
			mov rbx, [rsp + 0x40]
			mov rbp, [rsp + 0x48]
			mov rsi, [rsp + 0x50]
			add rsp, 0x20
			pop r15
			pop r14
			pop rdi
			jmp FUN_1401CF670


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

#pragma region ClassicCode - AOB Edition
	//First we unlock the Magneto Alt Costume.	
	uint64_t MagAltBlockPtr = 0x2 + FindBytePattern(moduleBase, ProjectedModuleSize, AOBMagnetoAltBlock);
	SingleProtectedWriteByte((MagAltBlockPtr), 1, 0xFF, oldPageProtection);

	//Next we update the color limits that house the exact value and unlock slot 9.
	ForColor9UIA = 0xE + FindBytePattern(moduleBase, ProjectedModuleSize, AOBForColor9UIA);
	SingleProtectedWriteByte((ForColor9UIA), 1, 0xFF, oldPageProtection);

	ForColor9UIB = 0xD + FindBytePattern(moduleBase, ProjectedModuleSize, AOBForColor9UIB);
	SingleProtectedWriteByte((ForColor9UIB), 1, 0xFF, oldPageProtection);

	ForColor9UIC = 0x9 + FindBytePattern(moduleBase, ProjectedModuleSize, AOBForColor9UIC);
	SingleProtectedWriteByte(ForColor9UIC, 1, ToggleColorCount, oldPageProtection);

	ForColor9UID = 0x10 + FindBytePattern(moduleBase, ProjectedModuleSize, AOBForColor9UID);
	SingleProtectedWriteByte(ForColor9UID, 1, 0xFF, oldPageProtection);

	//SingleProtectedWriteByte(0x14041AA18, 1, ToggleColorCount, oldPageProtection);

	CharacterColorLimitArray = 0x4 + FindBytePattern(moduleBase, ProjectedModuleSize, DefaultCharacterColorLimitArrayPattern);
	uint64_t CharColorLimitPtr = CharacterColorLimitArray;

	if (UseIndividualColors == 0)
	{
		//Now for the characters. Galactus' color limit stays as is.
		for (int v = 0; v < 50; v++)
		{
			SingleProtectedWriteByte(CharColorLimitPtr, 1, ToggleColorCount, oldPageProtection);
			CharColorLimitPtr = CharColorLimitPtr + 4;
		}

		//Skipping Galactus.
		CharColorLimitPtr = CharColorLimitPtr + 4;

		//These last 8 are for the child characters. They gotta be updated along with the host characters.
		for (int v = 0; v < 8; v++)
		{
			SingleProtectedWriteByte(CharColorLimitPtr, 1, ToggleColorCount, oldPageProtection);
			CharColorLimitPtr = CharColorLimitPtr + 4;
		}
	}
	else
	{
		CIniReader ini;
		SingleProtectedWriteByte(CharColorLimitPtr, 1, ini.ReadInteger("Settings", "ColorLimitRyu", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x4), 1, ini.ReadInteger("Settings", "ColorLimitChunLi", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x8), 1, ini.ReadInteger("Settings", "ColorLimitAkuma", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0xC), 1, ini.ReadInteger("Settings", "ColorLimitChris", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x10), 1, ini.ReadInteger("Settings", "ColorLimitWesker", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x14), 1, ini.ReadInteger("Settings", "ColorLimitVJoe", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x18), 1, ini.ReadInteger("Settings", "ColorLimitDante", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x1C), 1, ini.ReadInteger("Settings", "ColorLimitTrish", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x20), 1, ini.ReadInteger("Settings", "ColorLimitFrank", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x24), 1, ini.ReadInteger("Settings", "ColorLimitSpencer", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x28), 1, ini.ReadInteger("Settings", "ColorLimitArthur", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x2C), 1, ini.ReadInteger("Settings", "ColorLimitAmmy", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x30), 1, ini.ReadInteger("Settings", "ColorLimitZero", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x34), 1, ini.ReadInteger("Settings", "ColorLimitTron", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x38), 1, ini.ReadInteger("Settings", "ColorLimitMorrigan", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x3C), 1, ini.ReadInteger("Settings", "ColorLimitHsienKo", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x40), 1, ini.ReadInteger("Settings", "ColorLimitFelciia", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x44), 1, ini.ReadInteger("Settings", "ColorLimitCViper", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x48), 1, ini.ReadInteger("Settings", "ColorLimitHaggar", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x4C), 1, ini.ReadInteger("Settings", "ColorLimitJill", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x50), 1, ini.ReadInteger("Settings", "ColorLimitStrider", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x54), 1, ini.ReadInteger("Settings", "ColorLimitVergil", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x58), 1, ini.ReadInteger("Settings", "ColorLimitMrWright", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x5C), 1, ini.ReadInteger("Settings", "ColorLimitFirebrand", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x60), 1, ini.ReadInteger("Settings", "ColorLimitNemesis", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x64), 1, ini.ReadInteger("Settings", "ColorLimitSpiderMan", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x68), 1, ini.ReadInteger("Settings", "ColorLimitCap", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x6C), 1, ini.ReadInteger("Settings", "ColorLimitWolverine", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x70), 1, ini.ReadInteger("Settings", "ColorLimitMagneto", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x74), 1, ini.ReadInteger("Settings", "ColorLimitHulk", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x78), 1, ini.ReadInteger("Settings", "ColorLimitSheHulk", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x7C), 1, ini.ReadInteger("Settings", "ColorLimitTaskmaster", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x80), 1, ini.ReadInteger("Settings", "ColorLimitIronMan", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x84), 1, ini.ReadInteger("Settings", "ColorLimitThor", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x88), 1, ini.ReadInteger("Settings", "ColorLimitDoom", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x8C), 1, ini.ReadInteger("Settings", "ColorLimitJean", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x90), 1, ini.ReadInteger("Settings", "ColorLimitShuma", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x94), 1, ini.ReadInteger("Settings", "ColorLimitMODOK", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0x98), 1, ini.ReadInteger("Settings", "ColorLimitDormammu", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0x9C), 1, ini.ReadInteger("Settings", "ColorLimitDeadpool", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xA0), 1, ini.ReadInteger("Settings", "ColorLimitStorm", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xA4), 1, ini.ReadInteger("Settings", "ColorLimitSkrull", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xA8), 1, ini.ReadInteger("Settings", "ColorLimitSentinel", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0xAC), 1, ini.ReadInteger("Settings", "ColorLimitX23", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xB0), 1, ini.ReadInteger("Settings", "ColorLimitNova", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xB4), 1, ini.ReadInteger("Settings", "ColorLimitRR", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xB8), 1, ini.ReadInteger("Settings", "ColorLimitGhostRider", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0xBC), 1, ini.ReadInteger("Settings", "ColorLimitIronFist", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xC0), 1, ini.ReadInteger("Settings", "ColorLimitDrStrange", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xC4), 1, ini.ReadInteger("Settings", "ColorLimitHawkeye", VK_SPACE), oldPageProtection);

		//These last 8 are for the child characters. They gotta be updated along with the host characters and have the same values.
		SingleProtectedWriteByte((CharColorLimitPtr + 0xCC), 1, ini.ReadInteger("Settings", "ColorLimitZero", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xD0), 1, ini.ReadInteger("Settings", "ColorLimitMorrigan", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xD4), 1, ini.ReadInteger("Settings", "ColorLimitFelciia", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xD8), 1, ini.ReadInteger("Settings", "ColorLimitFelciia", VK_SPACE), oldPageProtection);

		SingleProtectedWriteByte((CharColorLimitPtr + 0xDC), 1, ini.ReadInteger("Settings", "ColorLimitFrank", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xE0), 1, ini.ReadInteger("Settings", "ColorLimitMrWright", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xE4), 1, ini.ReadInteger("Settings", "ColorLimitFirebrand", VK_SPACE), oldPageProtection);
		SingleProtectedWriteByte((CharColorLimitPtr + 0xE8), 1, ini.ReadInteger("Settings", "ColorLimitDrStrange", VK_SPACE), oldPageProtection);


	}
	ForCHSValueBorder = ForColor9UIC + 0xC;

	//This is for text on character select. Ensures the text range is in sync.
	SingleProtectedWriteByte((ForCHSValueBorder), 1, CHSValueBorder, oldPageProtection);

	ForMSDIndicesA = 0xC + FindBytePattern(moduleBase, ProjectedModuleSize, AOBForMSDIndicesA);
	MultiProtectedWriteShort(ForMSDIndicesA, 4, MSDValue, oldPageProtection);

	ForMSDIndicesB = 0x1A + FindBytePattern(moduleBase, ProjectedModuleSize, AOBForMSDIndicesB);
	MultiProtectedWriteShort(ForMSDIndicesB, 4, MSDValue, oldPageProtection);

	ForMSDIndicesC = 0x19 + FindBytePattern(moduleBase, ProjectedModuleSize, AOBForMSDIndicesC);
	MultiProtectedWriteShort(ForMSDIndicesC, 4, MSDValue, oldPageProtection);
	
	ForMSDIndicesD = 0x1A + FindBytePattern(moduleBase, ProjectedModuleSize, AOBForMSDIndicesD);
	MultiProtectedWriteShort(ForMSDIndicesD, 4, MSDValue, oldPageProtection);


	//For Testing Purposes.
	//Licensing Board Portraits?
	//SingleProtectedWriteByte(0x140C510FF, 1, 0x0, oldPageProtection);

	//This makes the jnz into an unconditional jump.
	SingleProtectedWriteByte(0x1402BCA88, 1, 0xEB, oldPageProtection);

	//This rewrites the final part to return 1.
	BYTE ForColor9[] = { 0xEB,0x1A,0x90,0x90,0x90 };
	MultiProtectedWriteByteArray(0x1402BCAB6, 5, ForColor9, oldPageProtection);

	//Originallly written by Eddie to ignore all test function and simply return the result of CalculateNewColorID. Modified.
	BYTE ForSomeFunctionE[] =
	{ 0x83, 0xC8, 0xFF,
		0xBA, 0x01, 0x00, 0x00, 0x00, 0x45, 0x84, 0xC9, 0x0F, 0x45, 0xD0, 0x44, 0x89, 0xC1, 0x45, 0x31,
		0xC0, 0xEB, 0x1D, 0x90, 0x00, 0x00, 0x90, 0xE8, 0xE4, 0x94, 0x19, 0x00, 0xE9, 0xE2, 0x00, 0x00,
		0x00, 0xCC, 0xCC, 0xCC ,0xCC ,0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC };
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

#pragma endregion

	//Sets up Trampoline Hook for the Scroller.
	
	BYTE ForSomeFunctionD[] = { 0x90, 0x90, 0x90, 0x90};

	
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

	InjectHook(_addr(0x1402B9AD0), tramp->Jump(FUN_1402B9AD0), PATCH_JUMP);

	//License Board fixes.
	BACKTOFUN_14041AA1B = moduleBase + 0x41AA1B;

	FUN_140058F90 = moduleBase + 0x58F90;
	aUiChsChsFaceAC = moduleBase + 0xB02F40;
	FUN_1404C4410 = moduleBase + 0x4C4410;
	FUN_140001B10 = moduleBase + 0x1B10;
	FUN_140455260 = moduleBase + 0x455260;
	FUN_140151080 = moduleBase + 0x151080;
	FUN_140E17570 = moduleBase + 0xE17570;
	FUN_14001DCA0 = moduleBase + 0x1DCA0;
	//InjectHook(_addr(0x14041A9A0), tramp->Jump(ForTheLicenseBoardPart1), PATCH_JUMP);

	FUN_140321020 = moduleBase + 0x321020;
	uChrColorType_vftableAddr = moduleBase + 0xB3B050;
	//uChrColorType_vftable = *((QWORD*)moduleBase + 0xB3B050);
	FUN_1402C9D70 = moduleBase + 0x2C9D70;
	FUN_1400012E0 = moduleBase + 0x12E0;
	FUN_140D2AD20 = moduleBase + 0xD2AD20;
	FUN_14035F770 = moduleBase + 0x35F770;

	//InjectHook(_addr(0x14035FF7F), tramp->Jump(ForTheColorBorders), PATCH_JUMP);
	//InjectHook(_addr(0x14035FF60), tramp->Jump(ForTheColorBorders_uChrColorTypeTypeInfo), PATCH_JUMP);

	//For Taskmaster.
	//BYTE ForTaskmaster[] =
	//{
	//	0x7D, 0x13
	//};
	//Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	//InjectHook(_addr(0x1402BC1C1), tramp->Jump(ForTheColorcounter), PATCH_JUMP);

#pragma region TestingGround For Borders
	////This section meant for the color borders. Needs intensive testing.
	////Don't think I can use a Trampoline Hook for this first part.
	////(Hopefully)Adjusts the amount of space the game allocates for uChrColorType.
	//SingleProtectedWriteByte(0x140A29C0F, 1, 0x10, oldPageProtection);
	//SingleProtectedWriteByte(0x140A29C0E, 1, 0x50, oldPageProtection);


	////My attempt at getting the Vtable AND changing the address cleanly in a way that doesn't cause the game to reject me.
	//void** uChrColorType_vftable = *(void***)0x140B3B050;
	//void** PtrToFunction = (void**)0x140B3B068;
	//void** PtrToThingAbovevftable = (void**)0x140B3B048;
	//DWORD oldProtect;
	//VirtualProtect(PtrToFunction, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect);
	//VirtualProtect(PtrToThingAbovevftable, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect);
	//*PtrToFunction = (void*)&FUN_14035F890;
	//*PtrToThingAbovevftable = (void*)&FUN_14035FF60;
	//VirtualProtect(PtrToFunction, sizeof(void*), oldProtect, &oldProtect);
	//VirtualProtect(PtrToThingAbovevftable, sizeof(void*), oldProtect, &oldProtect);
#pragma endregion

#pragma region TestingGround For Borders
//This section meant for the color borders. Needs intensive testing.
//Don't think I can use a Trampoline Hook for this first part.
//(Hopefully)Adjusts the amount of space the game allocates for uChrColorType.
	//SingleProtectedWriteByte(0x140A29C0F, 1, 0x10, oldPageProtection);
	//SingleProtectedWriteByte(0x140A29C0E, 1, 0x50, oldPageProtection);


	//My attempt at getting the Vtable AND changing the address cleanly in a way that doesn't cause the game to reject me.
	void** uChrColorType_vftable = *(void***)0x140B3B050;
	void** PtrToFunction = (void**)0x140B3B068;
	void** PtrToThingAbovevftable = (void**)0x140B3B048;

	DWORD oldProtect;
	DWORD oldProtect2;
	DWORD oldProtect3;

	//VirtualProtect(PtrToFunction, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect);
	//VirtualProtect(PtrToThingAbovevftable, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect2);

	//*PtrToFunction = (void*)&OLD_14035F890;
	//*PtrToThingAbovevftable = (void*)&OLD_14035FF60;


	//VirtualProtect(PtrToFunction, sizeof(void*), oldProtect, &oldProtect);
	//VirtualProtect(PtrToThingAbovevftable, sizeof(void*), oldProtect, &oldProtect2);

	//InjectHook(_addr(0x14035FF7F), tramp->Jump(OLD_14035F730), PATCH_JUMP);

#pragma endregion

	//For attract mode.
	InjectHook(_addr(0x14024E277), tramp->Jump(ForAttractMode), PATCH_CALL);

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
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

