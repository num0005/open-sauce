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
#include "Game/Campaign.hpp"
#if !PLATFORM_IS_DEDI

#include "Memory/MemoryInterface.hpp"

// Note: Only use 'Campaign.inl' (in the "Impl" virtual folder) for declaring campaign levels,
// all other definitions should be automated via 'DEFINE_CAMPAIGN_LEVEL'

namespace Yelo
{
	namespace Enums
	{
		enum campaign_level
		{
#define DEFINE_CAMPAIGN_LEVEL(name, path) _campaign_level_##name,

#include "Game/Campaign.inl" // Create an enumeration of our campaign levels
			_campaign_level,

#undef DEFINE_CAMPAIGN_LEVEL


			// Original amount of campaign levels the engine expected
			k_campaign_level_base_count = 10,

			// How many campaign levels we've added to the original count
			k_campaign_level_new_count = _campaign_level - k_campaign_level_base_count,

			// How many campaign levels we've defined
// 			k_campaign_level_total_count = k_campaign_level_new_count >= 0 ?
// 				k_campaign_level_base_count + k_campaign_level_new_count
// 				:
// 				_campaign_level,
		};

		// Make sure the user heeded our warning and didn't remove existing campaign 
		// levels
		BOOST_STATIC_ASSERT(_campaign_level >= k_campaign_level_base_count);
	};

	namespace Campaign
	{
#define __EL_INCLUDE_ID			__EL_INCLUDE_GAME
#define __EL_INCLUDE_FILE_ID	__EL_GAME_CAMPAIGN
#include "Memory/_EngineLayout.inl"

#pragma region Scenario Paths

	#define DEFINE_CAMPAIGN_LEVEL(name, path) path,
		static cstring ScenarioPaths[] = { // this is needed for displaying the title\bitmap in the campaign selection in the UI
			
	#include "Game/Campaign.inl" // create a path list of our campaign levels

		};
	#undef DEFINE_CAMPAIGN_LEVEL


		static void ScenarioPathsInitialize()
		{
			for(int32 x = 0; x < NUMBEROF(ScenarioPathsReferences); x++)
				*ScenarioPathsReferences[x] = ScenarioPaths;

			for(int32 x = 0; x < NUMBEROF(ScenarioPathsReferences2); x++)
				*ScenarioPathsReferences2[x] = ScenarioPaths;
		}
#pragma endregion


#pragma region Scenario Help

	#define DEFINE_CAMPAIGN_LEVEL(name, path) {#name, "ui\\shell\\solo_game\\player_help\\player_help_screen_" #name},
		static struct s_scenario_help_mapping {
			cstring name;
			cstring widget_definition;
		}ScenarioHelpMappings[] = { // this is needed for displaying the title\bitmap in the campaign selection in the UI

	#include "Game/Campaign.inl" // create a path list of our campaign levels

		};
	#undef DEFINE_CAMPAIGN_LEVEL

	static cstring ScenarioHelpMappingGetWidgetName(char* scenario_name)
	{
		for(int32 x = 0; x < NUMBEROF(ScenarioHelpMappings); x++)
			if( strstr(scenario_name, ScenarioHelpMappings[x].name) )
				return ScenarioHelpMappings[x].widget_definition;

		return NULL;
	}

	API_FUNC_NAKED static void PLATFORM_API DisplayScenarioHelpHack()
	{
		static uint32 SUCCESS_CALL_ADDR = GET_FUNC_PTR(DISPLAY_SCENARIO_HELP_SUCCESS);

		static uint32 FAIL_CALL_ADDR = GET_FUNC_PTR(DISPLAY_SCENARIO_HELP_FAIL);

		__asm {
			// edx = char scenario_name[256]
			// Note: The code we jump back to in display_scenario_help doesn't expect any 
			// registers to have a specific value (save for 'eax', which we return) 
			// so we don't have to worry about the compiler overwriting ecx or esi 
			// without preserving them on the stack in 'ScenarioHelpMappingGetWidgetName's code

			push	edx
			call	ScenarioHelpMappingGetWidgetName
			test	eax, eax
			jz		mapping_not_found
			jmp		SUCCESS_CALL_ADDR

mapping_not_found:
			jmp		FAIL_CALL_ADDR
		}
	}

	static void DisplayScenarioHelpInitialize()
	{
		Memory::WriteRelativeJmp(Campaign::DisplayScenarioHelpHack, GET_FUNC_VPTR(DISPLAY_SCENARIO_HELP_HOOK), true);
	}

#pragma endregion


#pragma region Campaign Level Data

		struct {
			cstring ScenarioPath;
			PAD8; // bools
			PAD8;
			PAD8;
			PAD8;
		}CampaignLevelData[Enums::_campaign_level];

		static void CampaignLevelDataInitialize()
		{
			for(int32 x = 0; x < NUMBEROF(CampaignLevelDataReferences); x++)
				*CampaignLevelDataReferences[x] = CampaignLevelData;

			for(int32 x = 0; x < NUMBEROF(CampaignLevelDataSizeReferences); x++)
				*CampaignLevelDataSizeReferences[x] = sizeof(CampaignLevelData) / 4;
		}
#pragma endregion


#pragma region Campaign Level Count

		static void CampaignLevelCountInitialize()
		{
			for(int32 x = 0; x < NUMBEROF(CampaignLevelCountReferences_8bit); x++)
				*CampaignLevelCountReferences_8bit[x] = Enums::_campaign_level-1;
			for(int32 x = 0; x < NUMBEROF(CampaignLevelCountReferences_16bit); x++)
				*CampaignLevelCountReferences_16bit[x] = Enums::_campaign_level-1;
			for(int32 x = 0; x < NUMBEROF(CampaignLevelCountReferences_32bit); x++)
				*CampaignLevelCountReferences_32bit[x] = Enums::_campaign_level-1;

			for(int32 x = 0; x < NUMBEROF(CampaignLevelCountReferences2_8bit); x++)
				*CampaignLevelCountReferences2_8bit[x] = Enums::_campaign_level;
			for(int32 x = 0; x < NUMBEROF(CampaignLevelCountReferences2_16bit); x++)
				*CampaignLevelCountReferences2_16bit[x] = Enums::_campaign_level;
		}
#pragma endregion


		void Initialize()
		{
			if(Enums::_campaign_level > Enums::k_campaign_level_base_count) // only change the game if we're greater than the normal level count
			{
				ScenarioPathsInitialize();
				DisplayScenarioHelpInitialize();
				CampaignLevelDataInitialize();
				CampaignLevelCountInitialize();
			}
		}

		void Dispose()
		{
// 			if(Enums::_campaign_level > Enums::k_campaign_level_base_count) // only change the game if we're greater than the normal level count
// 			{
// 			}
		}
	};
};

#endif