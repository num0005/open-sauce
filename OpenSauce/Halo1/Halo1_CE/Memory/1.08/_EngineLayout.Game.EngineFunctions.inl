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

ENGINE_PTR(void*, gather_exception_data,	0x6BDDC4, 0x62648C);
FUNC_PTR(GATHER_EXCEPTION,					0x582750, 0x52AE70);

FUNC_PTR(TEXTURE_CACHE_TEXTURE_REQUEST,		0x445070, FUNC_PTR_NULL);
FUNC_PTR(SOUND_CACHE_SOUND_REQUEST,			0x444930, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// Console
FUNC_PTR(CONSOLE_PROCESS_COMMAND,	0x4C9F10, 0x4B3960); // also in Console.cpp
FUNC_PTR(CONSOLE_TERMINAL_PRINTF,	0x4C9D10, 0x48ED40);
FUNC_PTR(CONSOLE_PRINTF,			0x4C9DB0, 0x4B3760);
FUNC_PTR(CONSOLE_WARNING,			0x4C9E70, 0x4B38C0);

//////////////////////////////////////////////////////////////////////////
// Cheats
FUNC_PTR(CHEAT_ALL_WEAPONS,						0x45B0A0, 0x457B00);
FUNC_PTR(CHEAT_SPAWN_WARTHOG,					0x45B130, 0x457B90);
FUNC_PTR(CHEAT_TELEPORT_TO_CAMERA,				0x45B1A0, 0x457C00);
FUNC_PTR(CHEAT_ACTIVE_CAMOFLAGE,				0x45B230, 0x457C90);
FUNC_PTR(CHEAT_ACTIVE_CAMOFLAGE_LOCAL_PLAYER,	0x45B290, 0x457CF0);
FUNC_PTR(CHEAT_PLAYER_INDEX,					0x45B310, 0x457D70);
FUNC_PTR(DIRECTOR_SAVE_CAMERA,					0x4463A0, FUNC_PTR_NULL);
FUNC_PTR(DIRECTOR_LOAD_CAMERA,					0x446460, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// Game
FUNC_PTR(SCENARIO_SWITCH_STRUCTURE_BSP,		0x5425E0, 0x4FD2F0);
FUNC_PTR(BINK_PLAYBACK_START,				0x43ED20, FUNC_PTR_NULL);
FUNC_PTR(GAME_ENGINE_RASTERIZE_MESSAGE,		0x462C80, FUNC_PTR_NULL);
FUNC_PTR(GAME_TEAM_IS_ENEMY,				0x45C8C0, 0x459270);
FUNC_PTR(GAME_ENGINE_PLAY_MULTIPLAYER_SOUND,0x46EC60, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// HS
FUNC_PTR(OBJECT_LIST_ADD,					0x48DFF0, 0x4858D0);

//////////////////////////////////////////////////////////////////////////
// Input
FUNC_PTR(INPUT_KEY_IS_DOWN, 0x493AC0, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// Interface
FUNC_PTR(KEYSTONE_CHAT_LOG_ADD_STRING,	0x4AEAA0, FUNC_PTR_NULL); // I forget if the dedicated has a chat log equivalent...
FUNC_PTR(HUD_PRINT_MESSAGE,				0x4B1760, 0x4A0210);
FUNC_PTR(HUD_GET_ITEM_MESSAGE,			0x4AD600, 0x49F310);

//////////////////////////////////////////////////////////////////////////
// Math
FUNC_PTR(PERIODIC_FUNCTION_EVALUATE,	0x4CFEC0, 0x4B8F30);
FUNC_PTR(TRANSITION_FUNCTION_EVALUATE,	0x4CFFD0, 0x4B9040);

//////////////////////////////////////////////////////////////////////////
// Memory
FUNC_PTR(DATUM_NEW_AT_INDEX,0x4D38E0, 0x4BC850);
FUNC_PTR(DATUM_NEW,			0x4D3990, 0x4BC900);
FUNC_PTR(DATUM_DELETE,		0x4D3A20, 0x4BC990);
FUNC_PTR(DATA_ITERATOR_NEXT,0x4D3AE0, 0x4BCA50);
FUNC_PTR(DATUM_NEXT_INDEX,	0x4D3B40, 0x4BCAB0);
FUNC_PTR(DATUM_GET,			0x4D3B90, 0x4BCB00);
FUNC_PTR(DATUM_INITIALIZE,	0x4D3BD0, 0x4BCB40);

//////////////////////////////////////////////////////////////////////////
// Networking
FUNC_PTR(MDP_ENCODE_OBJECT_DELETION_MESSAGE,			0x4F9700, 0x4E06F0);
FUNC_PTR(ENCODE_HUD_CHAT_NETWORK_DATA,					0x4ADF40, 0x49F710);
FUNC_PTR(MDP_TRANSLATED_INDEX_TRANSLATE,				0x4F4240, 0x4DD4A0);
DATA_PTR(MESSAGE_DELTA_FIELD_OBJECT_INDEX_PARAMETERS,	0x6226F0, 0x5980A8);
DATA_PTR(MESSAGE_DELTA_FIELD_PLAYER_INDEX_PARAMETERS,	0x622B18, 0x5984D0);

//////////////////////////////////////////////////////////////////////////
// Objects
FUNC_PTR(OBJECT_START_INTERPOLATION,	0x4FA7D0, 0x4E1720); // Until PY's netcode is finalized, this function don't mean shit (read: doesn't sync)
FUNC_PTR(OBJECT_RESET,					0x4F8DC0, 0x4DFDB0);
FUNC_PTR(OBJECT_RECONNECT_TO_MAP,		0x4F9890, 0x4E0880);
FUNC_PTR(OBJECT_DISCONNECT_FROM_MAP,	0x4F9A40, 0x4E0A30);
FUNC_PTR(OBJECT_GET_ORIGIN,				0x4FA560, 0x4E14B0);
FUNC_PTR(OBJECT_GET_ORIENTATION,		0x4FA5D0, 0x4E1520);
FUNC_PTR(OBJECT_GET_LOCATION,			0x4FA770, 0x4E16C0);
FUNC_PTR(OBJECT_SET_POSITION,			0x4F8E20, 0x4DFE10);
FUNC_PTR(OBJECT_SET_POSITION_NETWORK,	0x4F8F20, 0x4DFF10);
FUNC_PTR(OBJECT_RESTORE_BODY,			0x4F1630, 0x4DA890);
FUNC_PTR(OBJECT_DEPLETE_BODY,			0x4F1680, 0x4DA8E0);
FUNC_PTR(OBJECT_DEPLETE_SHIELD,			0x4F1770, 0x4DA9D0);
FUNC_PTR(OBJECT_DOUBLE_CHARGE_SHIELD,	0x4F1800, 0x4DA960);
FUNC_PTR(UNIT_GET_CAMERA_POSITION,		0x56CA50, FUNC_PTR_NULL);
FUNC_PTR(OBJECT_DEFINITION_PREDICT,		0x4FB730, 0x4E2680);
FUNC_PTR(UNIT_ORIENT_TO_FLAG,			0x48AC90, 0x482570);

//////////////////////////////////////////////////////////////////////////
// Players
FUNC_PTR(PLAYER_INDEX_FROM_UNIT_INDEX,		0x477BE0, 0x46F660);
FUNC_PTR(PLAYER_TELEPORT,					0x478A80, 0x470500);
FUNC_PTR(PLAYER_OVER_SHIELD_SCREEN_EFFECT,	0x47C4A0, FUNC_PTR_NULL);
FUNC_PTR(PLAYER_CAMO_SCREEN_EFFECT,			0x47C560, FUNC_PTR_NULL);
FUNC_PTR(PLAYER_HEALTH_PACK_SCREEN_EFFECT,	0x47C620, FUNC_PTR_NULL);
FUNC_PTR(FIND_CLOSEST_PLAYER_INDEX,			0x45EED0, FUNC_PTR_NULL);

//////////////////////////////////////////////////////////////////////////
// Scenario
FUNC_PTR(SCENARIO_TRIGGER_VOLUME_TEST_POINT,0x542750, 0x4FD460);

//////////////////////////////////////////////////////////////////////////
// TagGroups
FUNC_PTR(PHYSICAL_MEMORY_MAP_PREDICT_RESOURCES,	0x445510, FUNC_PTR_NULL);
FUNC_PTR(TAG_LOADED,							0x442990, 0x443520);
FUNC_PTR(UNICODE_STRING_LIST_GET_STRING,		0x55B360, 0x509DB0);