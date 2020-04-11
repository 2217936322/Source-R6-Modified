/*

	Entry-point for usermode, handles connection to driver,
	and essentially glues every function together.

*/

#include "globals.h"
#include "ConsoleColor.h"

#include <iostream>
#include <Psapi.h>
#include <string>
#include <thread>
#include <TlHelp32.h>
#include "Game/Game.h"
#include "Game/game.cpp"
using namespace std;

// For getting game process (credit to alxbrn for this, I got it from him but idk)
std::uint32_t find_process_by_id(const std::string& name)
{
	const auto snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE) {
		return 0;
	}

	PROCESSENTRY32 proc_entry{};
	proc_entry.dwSize = sizeof proc_entry;

	auto found_process = false;
	if (!!Process32First(snap, &proc_entry)) {
		do {
			if (name == proc_entry.szExeFile) {
				found_process = true;
				break;
			}
		} while (!!Process32Next(snap, &proc_entry));
	}

	CloseHandle(snap);
	return found_process
		? proc_entry.th32ProcessID
		: 0;
}

// Credit: https://github.com/Guliveer/r6s_external_wallhack-updated-by-Guliveer/blob/master/epic%20r6/Memory.cpp for this function
uintptr_t GetProcessBaseAddress(HANDLE Handle)
{
	HMODULE hMods[1024];
	DWORD cbNeeded;
	unsigned int i;

	if (EnumProcessModules(Handle, hMods, sizeof(hMods), &cbNeeded))
	{
		for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(Handle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				std::string wstrModName = szModName;
				std::string wstrModContain = "RainbowSix.exe";
				if (wstrModName.find(wstrModContain) != std::string::npos)
				{
					base_address = (uintptr_t)hMods[i];
					return base_address;
				}
			}
		}
	}

	return false;
}

void update()
{
	std::cout << "\b" << bCaveiraESPStatus;
	return;
}

int main()
{
	SetConsoleTitle("by: getdundDid Modified: 卐 Ciz ★");

	{
		pid = find_process_by_id("RainbowSix.exe");
		if (!pid)
		{
			MessageBox(NULL, "Error, Code: 1", NULL, MB_ICONHAND);
			exit(-1);
		}

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);
		if (hProcess == INVALID_HANDLE_VALUE || !hProcess)
		{
			MessageBox(NULL, "Error, Code: 0", NULL, MB_ICONHAND);
			exit(-1);
		}

		base_address = GetProcessBaseAddress(hProcess);
		if (!base_address)
		{
			MessageBox(NULL, "Error, Code: 2", NULL, MB_ICONHAND);
			exit(-1);
		}
	}

	int n,y;
	std::cout << std::endl << blue << " $ Made by: getdundDid  Modified: MANICRAFT4K \n" << std::endl;
	std::cout << green << "\t\tCHEETOS MODIFIED BY: MANICRAFT4K  \n";
	std::cout << yellow << " [F5]Cav ESP  \n";
	std::cout << yellow << " [F4]Glow  \n" ;
	std::cout << yellow << " [F3]Outline  \n" ;
	std::cout << yellow << " [F2]Freeze  \n\n" ;

	cout << blue << " Choose What u Want  = ";
	cin >> n;

	Beep(523, 500);
	
	if (n == 5) {
		cout << red << " Actived ";
		RainbowSix::esp();
		bCaveiraESPStatus = !bCaveiraESPStatus;
		bool Method();
	}
    else if (n == 4) {
		cout << red << " Actived ";
		RainbowSix::glow();
		void glow();
		bool Method();
	}
	else if (n==2) {
		cout << red << " Actived ";
		cout << green  << " Inset The Value 0 For Freeze ";
		void freeze(bool isEnable);
		bool Method();
	}
	else if (n == 3) {
		cout << red << " Actived ";
		RainbowSix::outline();
		void outline();
		bool Method();
	}
	// OR 
	while (true)
	{
		RainbowSix::esp();

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			bCaveiraESPStatus = !bCaveiraESPStatus;
			update();
		}

		if (GetAsyncKeyState(VK_END))
		{
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	while ( true)
	{
	     RainbowSix::outline();

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			void outline();
			update();
		}

		if (GetAsyncKeyState(VK_END))
		{
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	while ( true)
	{


		if (GetAsyncKeyState(VK_F2) & 1)
		{
			void  freeze(bool isEnable);
			update();
		}

		if (GetAsyncKeyState(VK_END))
		{
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return 0;
}