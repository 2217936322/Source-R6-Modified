/*

	Definitions for features and whatnot

*/

#include "Game.h"
#include "Offsets.h"
#include <iostream>
#include <iostream>
#include <Psapi.h>
#include <string>
#include <thread>
#include <TlHelp32.h>
#include "Vector/SVector.h"
using namespace std;

namespace RainbowSix
{
	bool esp()
	{
		uintptr_t game_manager = RPM<uintptr_t>(base_address + address_game_manager);
		if (!game_manager) return false;

		uintptr_t entity_list = RPM<uintptr_t>(game_manager + offset_entity_list);
		int entity_count = RPM<DWORD>(game_manager + offset_entity_count) & 0x3fffffff;
		if (!entity_list || !entity_count) return false;

		for (int i = 0; i < entity_count; i++)
		{
			uintptr_t entity_object = RPM<uintptr_t>(entity_list + i * 0x8);
			if (!entity_object) continue;

			uintptr_t chain2 = RPM<uintptr_t>(entity_object + 0x28); if (!chain2) continue;
			uintptr_t chain3 = RPM<uintptr_t>(chain2 + 0xD8); if (!chain3) continue;

			for (auto current_component = 0x80; current_component < 0xf0; current_component += sizeof(uintptr_t))
			{
				uintptr_t chain4 = RPM<uintptr_t>(chain3 + current_component);
				if (!chain4) continue;

				if (RPM<uintptr_t>(chain4) != (base_address + address_v_table)) continue;

				WPM<BYTE>(chain4 + 0x552, bCaveiraESPStatus);
				WPM<BYTE>(chain4 + 0x554, bCaveiraESPStatus);
			}
		}
	}
	int y,n;
	inline std::ostream& blue(std::ostream& s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
			| FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}
	bool Method() 
	{
		cout << blue << " More? ";
		cin >> y;
		if (y == 1) {
			cout << blue << " Choose What u Want More  = ";
			cin >> n;
		}
		cout << blue << " More? ";
		cin >> y;
		if (y == 1) {
			cout << blue << " Choose What u Want More  = ";
			cin >> n;
		}
	}
		
	
	void glow()
	{
		constexpr uintptr_t glow_manager_base = 0x605c388;
		constexpr uintptr_t glow_base = 0xb8;
		float red = 255.0f;
		float green = 0.0f;
		float blue = 0.0f;
		float alpha = 0.0f;
		float opacity = 255.0f;
		float distance = 0.0f;

		uintptr_t chain = RPM<uintptr_t>(glow_manager_base + glow_base);
		if (chain != 0) {
			WPM<float>(chain  + 0xD0, red);
			WPM<float>(chain  + 0xD4, green);
			WPM<float>(chain  + 0xD8, blue);
			WPM<float>(chain + 0x118, alpha);
			WPM<float>(chain + 0x118, opacity);
			WPM<float>(chain + 0x118, distance); // other
			WPM<float>(chain + 0x110 + 0x4, 255.f); // local
		}
    }
	
	void freeze(bool isEnable){
		DWORD_PTR FreezeManager = RPM<DWORD_PTR>(base_address + ADDRESS_FREEZEMANAGER);
		WPM<BYTE>(FreezeManager + 0x5c, 0);
	}

	void outline()
	{

		uintptr_t game_manager = RPM<uintptr_t>(base_address + address_game_manager);
		if (!game_manager) return;

		uintptr_t GMComponentContainer = RPM<uintptr_t>(game_manager + 0x250);
		uintptr_t outlineComp = RPM<uintptr_t>(GMComponentContainer + 0xBB8); // GMComponentMarkAndOutline
	}
}