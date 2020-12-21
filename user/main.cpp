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
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";



void DoNothingMethod(MethodInfo* method)
{
	// nothing
	// printf("Hit DoNothingMethod\n");
}

bool File_Exists_Hook(String* str,MethodInfo* method)
{
	//the only dll it looks for using File.Exists() are version.dll, winhttp.dll and winmm.dll
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)str)->chars), ((Il2CppString*)str)->length));

	//printf("Searching for %s\n", skey.c_str());

	if (skey.find("dll") != std::string::npos)
	{
		printf("Searching for %s blocked\n", skey.c_str());
		return false;
	}

	return File_Exists(str, method);
}

// Custom injected code entry point
void Run()
{

	NewConsole();

	printf("Starting bypass\n");

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


	// I haven't been able to find where exactly it looks for the dll files, so I'm just hooking File.Exists(), and returning false manually when it looks for a dll

	DetourAttach(&(PVOID&)File_Exists, File_Exists_Hook);

	DetourTransactionCommit();

	printf("Bypass hooked\n");
	
}