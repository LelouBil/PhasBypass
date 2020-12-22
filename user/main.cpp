// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <codecvt>
#include <Windows.h>
#include <iostream>
#include <detours.h>
#include <locale>

#include "il2cpp-appdata.h"
#include "helpers.h"

using namespace app;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"bypass-log.txt";

const std::string NotMelonLoader = "totally_not_melon_loader";

String* not_melon_loader;

void DoNothingMethod(MethodInfo* method)
{
	// nothing
	LogWrite("Hit DoNothingMethod\n");
}

bool File_Exists_Hook(String* str,MethodInfo* method)
{
	//the only dll it looks for using File.Exists() are version.dll, winhttp.dll and winmm.dll
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)str)->chars), ((Il2CppString*)str)->length));

	//printf("Searching for %s\n", skey.c_str());

	char p[500];

	sprintf_s(p, "Searching for file %s", skey.c_str());
	
	LogWrite(p);

	if (skey.find("dll") != std::string::npos || skey.find(NotMelonLoader) != std::string::npos)
	{
		LogWrite(" blocked\n");
		return false;
	}

	LogWrite("\n");
	return File_Exists(str, method);
}

bool Directory_Exists_Hook(String* str,MethodInfo* method)
{
	
	//the only dll it looks for using File.Exists() are version.dll, winhttp.dll and winmm.dll
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)str)->chars), ((Il2CppString*)str)->length));

	//printf("Searching for %s\n", skey.c_str());

	char p[500];

	sprintf_s(p, "Searching for directory %s", skey.c_str());

	LogWrite(p);

	if (skey.find("MelonLoader") != std::string::npos || skey.find(NotMelonLoader) != std::string::npos)
	{
		LogWrite(" blocked\n");
		return false;
	}

	LogWrite("\n");
	return Directory_Exists(str, method);
}


// IntPtr \u0924\u0929\u091F\u091B\u091A\u091C\u0927\u091E\u0928\u0927\u0926(String)
// 1818b0190
void* TryGetModuleHandleHook(String* str, MethodInfo* method)
{

	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)str)->chars), ((Il2CppString*)str)->length));

	char buf[500]{};

	sprintf_s(buf,"blocked module handle of %s\n", skey.c_str());
	LogWrite(buf);
	return nullptr;
}


// String \u0926\u0926\u0920\u0923\u091A\u0921\u0923\u0927\u091D\u091E\u091C(Byte[], Boolean)
// in __202 class
// 1814491c0
String* GetMelonLoaderSearchStrings(Byte__Array* theArray, bool b, MethodInfo* method)
{
	/*String* res = __202_____________29(theArray, b, method);
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)res)->chars), ((Il2CppString*)res)->length));
	
	char buf[500]{};

	sprintf_s(buf, "ComparString called, res is %s\n", skey.c_str());

	LogWrite(buf);*/

	//log muted for this because it is called A LOT

	return not_melon_loader;
}

// Custom injected code entry point
void Run()
{

	NewConsole();

	LogWrite("Starting bypass\n");

	not_melon_loader = (String*)il2cpp_string_new(NotMelonLoader.c_str());

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	// This method checks if the following apps are running.
	// It gets all the system's process and compares their names with the ones below, if any matches it calls Application.Quit()
	// - cheatengine
	// - sharpmonoinjector
	// - fiddler
	// - dnspy
	// - ollydbd
	// NOTE: this seems to be buggy because before finding this I got Phasmophobia running with Cheat Engine in the background.
	DetourAttach(&(PVOID&)__105_____________1, DoNothingMethod);

	// This method checks for the following files in the games data directory, on the first one found, it deletes it and calls Application.Quit()
	// - modconfig.cfg
	// - sharpmonoinjector.dll
	// - coolphobialauncher.exe
	// - loader.exe
	// - launcher.exe
	DetourAttach(&(PVOID&)__105_____________2, DoNothingMethod);


	// This method just checks your money and clamps it to 250000 if it's above it
	DetourAttach(&(PVOID&)__105____________, DoNothingMethod);


	// this method calls GetModuleHandle, it is only called by the game's code and is used to detect loaded dlls
	DetourAttach(&(PVOID&)__103_____________7, TryGetModuleHandleHook);


	// I haven't been able to find where exactly it looks for the dll files, so I'm just hooking File.Exists(), and returning false manually when it looks for a dll

	DetourAttach(&(PVOID&)File_Exists, File_Exists_Hook);

	// same for Directory.Exists()
	DetourAttach(&(PVOID&)Directory_Exists, Directory_Exists_Hook);


	// replaces the text it checks for

	
	DetourAttach(&(PVOID&)__202_____________13, GetMelonLoaderSearchStrings);

	// hooks quit for debugging
	/*DetourAttach(&(PVOID&) Application_Quit_1, DoNothingMethod);
	DetourAttach(&(PVOID&) Application_Quit, DoNothingMethod);
	DetourAttach(&(PVOID&)Utils_1_ForceCrash, DoNothingMethod);*/


	DetourTransactionCommit();
	LogWrite("Bypass hooked\n");
	
}
