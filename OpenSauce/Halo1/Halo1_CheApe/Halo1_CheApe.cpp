/*
    Yelo: Open Sauce SDK
		Halo 1 (Editing Kit) Edition
    Copyright (C) 2005-2010  Kornner Studios (http://kornner.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Common/Precompile.hpp"

#include "Common/YeloSettings.hpp"
#include "Engine/EngineFunctions.hpp"
#include "CheApeInterface.hpp"
#include "Yelo/MemoryFixups.hpp"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH) {
		Yelo::CheApe::UnProtectMemoryRegion();

		Yelo::Settings::Initialize();
		Yelo::c_memory_fixups::InitializePaths();

		Yelo::CheApe::PhysicalMemoryMapInitialize();
		Yelo::CheApe::LoadCacheFile();
		if(Yelo::CheApe::_InitError == Yelo::CheApe::k_error_LoadCacheFile)
		{
			YELO_ERROR(_error_message_priority_none, 
				"CheApe: cache failure");
			goto dispose;
		}
		Yelo::CheApe::SetupTagGroupPointers();
		Yelo::CheApe::SetupTagGroupCounts();
		Yelo::CheApe::UpdateTagGroupReferences();

		if(Yelo::CheApe::_InitError == Yelo::CheApe::k_error_none)
		{
			// Sapien requires earlier hooking in order to properly override tag paths, so 
			// we place a hook where we use to load CheApe.DLL from
#if PLATFORM_ID == PLATFORM_SAPIEN
			Yelo::Memory::WriteRelativeCall(Yelo::Initialize, CAST_PTR(void*,0x418A50));
			Yelo::Memory::WriteRelativeCall(Yelo::Initialize, CAST_PTR(void*,0x4141E5)); // for no render cases
#else
			Yelo::Initialize();
#endif
		}
		else
		{	Yelo::EngineFunctions::error(Yelo::Enums::_error_message_priority_none, "CheApe: Yelo initialization failed!"); }
	}
	else if(ul_reason_for_call == DLL_PROCESS_DETACH) {
dispose:
		if(Yelo::CheApe::_InitError == Yelo::CheApe::k_error_none)
			Yelo::Dispose();

		Yelo::CheApe::Dispose();

		Yelo::c_memory_fixups::DisposePaths();
		Yelo::Settings::Dispose();
	}

    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif