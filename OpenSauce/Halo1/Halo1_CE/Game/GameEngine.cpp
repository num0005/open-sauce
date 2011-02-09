/*
    Yelo: Open Sauce SDK
		Halo 1 (CE) Edition
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
#include "Game/GameEngine.hpp"

#include "Memory/MemoryInterface.hpp"
#include "Game/GameState.hpp"

namespace Yelo
{
	namespace GameEngine
	{
#define __EL_INCLUDE_ID			__EL_INCLUDE_GAME
#define __EL_INCLUDE_FILE_ID	__EL_GAME_GAME_ENGINE
#include "Memory/_EngineLayout.inl"

		s_ctf_globals* CtfGlobals()							PTR_IMP_GET2(ctf_globals);
		s_slayer_globals* SlayerGlobals()					PTR_IMP_GET2(slayer_globals);
		s_oddball_globals* OddballGlobals()					PTR_IMP_GET2(oddball_globals);
		s_king_globals* KingGlobals()						PTR_IMP_GET2(king_globals);
		s_race_globals* RaceGlobals()						PTR_IMP_GET2(race_globals);

		s_game_variant* GlobalVariant()						PTR_IMP_GET2(global_variant);

		const game_engine_definition* const* Definitions()	DPTR_IMP_GET2(game_engines);
		const game_engine_definition* Current()				DPTR_IMP_GET(game_engine);

#pragma region New Engines functions
		static game_engine_definition* new_definitions[Enums::_game_engine_custom + 1] = {
// 			NULL,
// 			NULL, NULL, NULL, NULL, NULL, NULL, // old game engines
// 			NULL, NULL, NULL, NULL, NULL, // space for new game engines
// 			NULL, // terminator
		};
		static int32 new_definitions_count = Enums::_game_engine;
#define GAME_ENGINE_REAL_COUNT (Enums::_game_engine - 2)

		const game_engine_definition* const* NewDefinitions() { return new_definitions; }

		int32 NewDefinitionsCount() { return new_definitions_count; }

		void RegisterNewGameEngine(game_engine_definition* engine)
		{
			if(new_definitions_count < Enums::_game_engine_custom)
				new_definitions[new_definitions_count++] = engine;
		}

		static void FixHudRenderUnitInterface()
		{
#if !PLATFORM_IS_DEDI

			static void* jmp_table[Enums::_game_engine_custom-1];

			// TODO: need to modify pre-jump table code before this works the way we want it to

			// copy the game's jump table into our jmp table
			for(int32 x = 0; x < Enums::_game_engine - GAME_ENGINE_REAL_COUNT; x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(HUD_RENDER_UNIT_INTERFACE_JMP_TABLE) + (sizeof(void*) * x));

			// just use the slayer variant of the code, it doesn't matter to us.
			for(int32 x = Enums::_game_engine-GAME_ENGINE_REAL_COUNT; x < NUMBEROF(jmp_table); x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(HUD_RENDER_UNIT_INTERFACE_JMP_TABLE) + (sizeof(void*) * (Enums::_game_engine_slayer - 1)));

			// set the game's jump table address to our's
			GET_PTR(hud_render_unit_interface_jmp_ptr) = jmp_table;
#endif
		}

		static void FixFunc4F7440() // function for the engine vehicle remapper
		{
			static void* jmp_table[Enums::_game_engine_custom-1];

			// TODO: reference jump table code for the changes to make this work the way we want it to

			// copy the game's jump table into our jmp table
			for(int32 x = 0; x < Enums::_game_engine - GAME_ENGINE_REAL_COUNT; x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(Func4F7440JmpTable) + (sizeof(void*) * x));

			// just use the slayer variant of the code, it doesn't matter to us.
			for(int32 x = Enums::_game_engine-GAME_ENGINE_REAL_COUNT; x < NUMBEROF(jmp_table); x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(Func4F7440JmpTable) + (sizeof(void*) * (Enums::_game_engine_slayer - 1)));

			// set the game's jump table address to our's
			GET_PTR(Func4F7440JmpPtr) = jmp_table;
		}

		static void FixFunc4F7580() // function for the engine vehicle remapper
		{
			static void* jmp_table[Enums::_game_engine_custom-1];

			// TODO: reference jump table code for the changes to make this work the way we want it to

			// copy the game's jump table into our jmp table
			for(int32 x = 0; x < Enums::_game_engine - GAME_ENGINE_REAL_COUNT; x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(Func4F7580JmpTable) + (sizeof(void*) * x));

			// just use the slayer variant of the code, it doesn't matter to us.
			for(int32 x = Enums::_game_engine-GAME_ENGINE_REAL_COUNT; x < NUMBEROF(jmp_table); x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(Func4F7580JmpTable) + (sizeof(void*) * (Enums::_game_engine_slayer - 1)));

			// set the game's jump table address to our's
			GET_PTR(Func4F7580JmpPtr) = jmp_table;
		}
#pragma endregion


		void Initialize()
		{
//#if PLATFORM_IS_DEDI
			Memory::CreateHookRelativeCall(&GameEngine::InitializeForNewMap, GET_FUNC_VPTR(GAME_ENGINE_INITIALIZE_FOR_NEW_MAP_HOOK), 0xC3 /*retn*/);

			Memory::CreateHookRelativeCall(&GameEngine::Update, GET_FUNC_VPTR(GAME_ENGINE_UPDATE_HOOK), 0xC3 /*retn*/);
//#endif

#pragma region New Engines implementation
			// copy the game engine pointers into our list
			for(int32 x = 0; x < new_definitions_count; x++)
				new_definitions[x] = GET_DPTR2(game_engines)[x];

			// replace the game's game_engines list with ours
			GET_PTR(game_engine_init_mod) = new_definitions;

			FixHudRenderUnitInterface();
			FixFunc4F7440();
			FixFunc4F7580();
#pragma endregion
		}

		void Dispose()
		{
		}

		void PLATFORM_API InitializeForNewMap()
		{
			if( GameEngine::Current() )
			{
				GameState::WriteEvent(GameState::GameGlobals()->options.map_name);
 				GameState::WriteEvent("", false);
			}
		}

		void PLATFORM_API Update()
		{
			const real k_update_normal = 1.6666668e-2f; // 0.016666668
			const real k_update_double_speed = 3.3333335e-2f; // 0.033333335

			real delta_time = !GameState::GameGlobals()->players_are_double_speed ? 
				k_update_normal :
				k_update_double_speed;

			GameState::Update(delta_time);

			// NOTE: Place any update code in the GameState's Update function, or the 
			// Update function of the corresponding component (ie, Effect, Players, etc) 
			// Don't mess with the GameEngine Update function unless it's related to the game_engine
		}
	};
};