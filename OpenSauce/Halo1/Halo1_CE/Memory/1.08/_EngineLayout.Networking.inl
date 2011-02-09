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

//////////////////////////////////////////////////////////////////////////
// MDP.hpp
#if __EL_INCLUDE_FILE_ID == __EL_NETWORKING_MDP
	FUNC_PTR(MDP_FIELD_ENCODE_ARRAY, 0x4ECCD0, 0x4D5F60);
	FUNC_PTR(MDP_FIELD_DECODE_ARRAY, 0x4ECD10, 0x4D5FA0);

	#ifndef YELO_NO_NETWORK
		ENGINE_PTR(field_properties_definition, message_delta_field_integer_small,							0x6229B8, 0x598370);
		ENGINE_PTR(field_properties_definition, message_delta_field_integer_medium,							0x622A28, 0x5983E0);
		ENGINE_PTR(field_properties_definition, message_delta_field_integer_large,							0x622600, 0x597FB8);
		ENGINE_PTR(field_properties_definition, message_delta_field_real,									0x622770, 0x598128);
		ENGINE_PTR(field_properties_definition, message_delta_field_boolean,								0x622950, 0x598308);
		ENGINE_PTR(field_properties_definition, message_delta_field_ascii_character,						0x635E20, 0x5AB7F8);
		ENGINE_PTR(field_properties_definition, message_delta_field_time,									0x635F68, 0x5AB940);
		ENGINE_PTR(field_properties_definition, message_delta_field_grenade_counts,							0x635C58, 0x5AB630);
		ENGINE_PTR(field_properties_definition, message_delta_field_locality_reference_position,			0x6314B0, 0x5A6E50);
		ENGINE_PTR(field_properties_definition, message_delta_field_digital_throttle,						0x633660, 0x5A8FF8);
		ENGINE_PTR(field_properties_definition, message_delta_field_fixed_width_weapon_index,				0x633738, 0x5A90D0);
		ENGINE_PTR(field_properties_definition, message_delta_field_fixed_width_grenade_index,				0x6337A0, 0x5A913C);
		ENGINE_PTR(field_properties_definition, message_delta_field_item_placement_position,				0x635FD0, 0x5AB9A8);

		ENGINE_PTR(field_properties_definition, message_delta_field_local_player_update_sequence_number,	0x634EC8, 0x5AA8A0);
		ENGINE_PTR(field_properties_definition, message_delta_field_remote_player_update_sequence_number,	0x634FA8, 0x5AA980);
		ENGINE_PTR(field_properties_definition, message_delta_field_remote_player_action_update_baseline_id,0x634F38, 0x5AA910);
		ENGINE_PTR(field_properties_definition, message_delta_field_update_tick_count,						0x633568, 0x5A8F00);
		ENGINE_PTR(field_properties_definition, message_delta_field_update_id,								0x6334F8, 0x5A8E90);
		ENGINE_PTR(field_properties_definition, message_delta_field_fixed_width_3bits,						0x635CC8, 0x5AB6A0);
		ENGINE_PTR(field_properties_definition, message_delta_field_fixed_width_6bits,						0x631740, 0x5A70E0);
		ENGINE_PTR(field_properties_definition, message_delta_field_fixed_width_1bit,						0x6336D0, 0x5A9068);
		ENGINE_PTR(field_properties_definition, message_delta_field_fixed_width_normal_4bit,				0x635D40, 0x5AB718);
		ENGINE_PTR(field_properties_definition, message_delta_field_fixed_width_normal_8bit,				0x630A68, 0x5A6408);
		ENGINE_PTR(field_properties_definition, message_delta_field_fixed_width_normal_16bit,				0x635DB8, 0x5AB790);
		ENGINE_PTR(field_properties_definition, message_delta_field_object_index,							0x622698, 0x598050);
		ENGINE_PTR(field_properties_definition, message_delta_field_player_index,							0x622AC0, 0x598478);
		ENGINE_PTR(field_properties_definition, message_delta_field_definition_index,						0x62E4D0, 0x5A3E70);
		ENGINE_PTR(field_properties_definition, message_delta_field_point2d,								0x635E90, 0x5AB868);
		ENGINE_PTR(field_properties_definition, message_delta_field_point3d,								0x630AD8, 0x5A6478);
		ENGINE_PTR(field_properties_definition, message_delta_field_vector2d,								0x635F00, 0x5AB8D8);
		ENGINE_PTR(field_properties_definition, message_delta_field_vector3d,								0x622708, 0x5980C0);
		ENGINE_PTR(field_properties_definition, message_delta_field_control_flags,							0x6335F8, 0x5A8F90);
		ENGINE_PTR(field_properties_definition, message_delta_field_angular_velocity,						0x6311E8, 0x5A6B88);
		ENGINE_PTR(field_properties_definition, message_delta_field_translational_velocity,					0x630E60, 0x5A6800);
		ENGINE_PTR(field_properties_definition, message_delta_field_map_name,								0x6339E8, 0x5A9380);
		ENGINE_PTR(field_properties_definition, message_delta_field_network_map,							0x633A78, 0x5A9410);
		ENGINE_PTR(field_properties_definition, message_delta_field_network_player_name,					0x633AE8, 0x5A9480);
		ENGINE_PTR(field_properties_definition, message_delta_field_network_player,							0x633BC8, 0x5A9560);
		ENGINE_PTR(field_properties_definition, message_delta_field_network_game_name,						0x633C38, 0x5A95D0);
		ENGINE_PTR(field_properties_definition, message_delta_field_network_game_players,					0x633CB0, 0x5A9648);
		ENGINE_PTR(field_properties_definition, message_delta_field_game_variant,							0x622F78, 0x598930);
		ENGINE_PTR(field_properties_definition, message_delta_field_game_variant_human_readable_description,0x622E28, 0x5987E0);
		ENGINE_PTR(field_properties_definition, message_delta_field_universal_variant,						0x622D40, 0x5986F8);
		ENGINE_PTR(field_properties_definition, message_delta_field_universal_variant_flags,				0x622B50, 0x598508);
		ENGINE_PTR(field_properties_definition, message_delta_field_game_engine_variant,					0x622DB8, 0x598770);
		ENGINE_PTR(field_properties_definition, message_delta_field_game_variant_flags,						0x622EB8, 0x598870);
		ENGINE_PTR(field_properties_definition, message_delta_field_parameters_protocol_array,				0x636808, 0x5AC1E0);
		ENGINE_PTR(field_properties_definition, message_delta_field_hud_chat_message,						0x62E388, 0x5A3D28);
		ENGINE_PTR(field_properties_definition, message_delta_field_hud_chat_message_ptr,					0x62E3F8, 0x5A3D98);
		ENGINE_PTR(field_properties_definition, message_delta_field_object_change_colors,					0x636530, 0x5ABF08);
		ENGINE_PTR(field_properties_definition, message_delta_field_ctf_score_array,						0x6233A0, 0x598D60);
		ENGINE_PTR(field_properties_definition, message_delta_field_race_score_array,						0x623AC8, 0x599488);
		ENGINE_PTR(field_properties_definition, message_delta_field_king_score_array,						0x623548, 0x598F08);
		ENGINE_PTR(field_properties_definition, message_delta_field_oddball_score_array,					0x623970, 0x599330);
		ENGINE_PTR(field_properties_definition, message_delta_field_oddball_owner_array,					0x6239E8, 0x5993A8);
		ENGINE_PTR(field_properties_definition, message_delta_field_slayer_score_array,						0x623BC8, 0x599588);
		ENGINE_PTR(field_properties_definition, message_delta_field_damage_data_flags,						0x622810, 0x5981C8);
		ENGINE_PTR(field_properties_definition, message_delta_field_motd_text,								0x634E10, 0x5AA7E8);
		ENGINE_PTR(field_properties_definition, message_delta_field_rcon_response,							0x634D58, 0x5AA6F0);
		ENGINE_PTR(field_properties_definition, message_delta_field_rcon_password,							0x634C20, 0x5AA5B8);
		ENGINE_PTR(field_properties_definition, message_delta_field_rcon_command,							0x634C90, 0x5AA628);
		//ENGINE_PTR(field_properties_definition, message_delta_field_, 0, PTR_UNKNOWN);


		ENGINE_PTR(field_reference_set, message_delta_empty_field_set,								0x6225E0, 0x597F98);

		//ENGINE_PTR(field_reference_set, message_delta_guaranteed_object_header_field_set,				0x0, 0x0);
		ENGINE_PTR(field_reference_set, message_delta_game_object_header_field_set,					0x631250, 0x5A6BF0);
		ENGINE_PTR(field_reference_set, message_delta_game_object_timestamped_header_field_set,		0x636060, 0x5ABA38);
		ENGINE_PTR(field_reference_set, message_delta_biped_update_header_field_set,				0x636440, 0x5ABE18);
		ENGINE_PTR(field_reference_set, message_delta_ctf_update_header_field_set,					0x623408, 0x598DC8);
		ENGINE_PTR(field_reference_set, message_delta_client_game_update_header_field_set,			0x6338EC, 0x5A9284);
		ENGINE_PTR(field_reference_set, message_delta_player_score_update_header_field_set,			0x6230DC, 0x598A9C);
		ENGINE_PTR(field_reference_set, message_delta_remote_player_action_update_header_field_set,	0x635130, 0x5AAB08);
		ENGINE_PTR(field_reference_set, message_delta_remote_player_position_update_header_field_set,0x6352C8, 0x5AACA0);
		ENGINE_PTR(field_reference_set, message_delta_remote_player_total_update_header_field_set,	0x6353F0, 0x5AADC8);
		//ENGINE_PTR(field_reference_set, message_delta__header_field_set, 0, PTR_UNKNOWN);
	#endif


//////////////////////////////////////////////////////////////////////////
// MessageDefinitions.cpp
#elif __EL_INCLUDE_FILE_ID == __EL_NETWORKING_MESSAGE_DEFINITIONS

	// Currently there is nothing to add here


//////////////////////////////////////////////////////////////////////////
// MessageDeltas.cpp
#elif __EL_INCLUDE_FILE_ID == __EL_NETWORKING_MESSAGE_DELTAS
	ENGINE_PTR(s_misc_encoding_globals, misc_encoding_globals,						0x635994, 0x5AB36C);
	ENGINE_PTR(Enums::message_delta_encoding_class, g_message_delta_encoding_class,	0x636A18, 0x5AC3F0);

	ENGINE_PTR(byte, mdp_packet_buffer_received_data,			0x7FCD40, 0x6C8C80);
	ENGINE_PTR(byte, mdp_packet_buffer_sent_data,				0x80CD40, 0x6D8C80);

	ENGINE_DPTR(message_delta_definition, message_delta_packets,0x5FBA60, 0x557400);

	#ifndef YELO_NO_NETWORK
		#pragma region MessageDeltaPointerReferences
		static void** MessageDeltaPointerReferences[] = {
			CAST_PTR(void**, PLATFORM_VALUE(0x4EFF73,0x4D91D3)), CAST_PTR(void**, PLATFORM_VALUE(0x4EFFF4,0x4D9254)), CAST_PTR(void**, PLATFORM_VALUE(0x4F018D,0x4D93ED)),
			CAST_PTR(void**, PLATFORM_VALUE(0x4F03B3,0x4D9613)), CAST_PTR(void**, PLATFORM_VALUE(0x4F0440,0x4D96A0)), CAST_PTR(void**, PLATFORM_VALUE(0x4F05D0,0x4D9830)),
			CAST_PTR(void**, PLATFORM_VALUE(0x4F076C,0x4D99CC)), CAST_PTR(void**, PLATFORM_VALUE(0x4F07D9,0x4D9A39)), CAST_PTR(void**, PLATFORM_VALUE(0x4F086E,0x4D9ACE)),
			CAST_PTR(void**, PLATFORM_VALUE(0x4F0898,0x4D9AF8)), CAST_PTR(void**, PLATFORM_VALUE(0x4F0A4F,0x4D9CAF)), CAST_PTR(void**, PLATFORM_VALUE(0x4F0C29,0x4D9E89)),
			CAST_PTR(void**, PLATFORM_VALUE(0x4F0CE1,0x4D9F41)), CAST_PTR(void**, PLATFORM_VALUE(0x4F0DA9,0x4DA009)), CAST_PTR(void**, PLATFORM_VALUE(0x4F0E39,0x4DA099)),
			CAST_PTR(void**, PLATFORM_VALUE(0x4F0E87,0x4DA0E7)), CAST_PTR(void**, PLATFORM_VALUE(0x4F0EF5,0x4DA155)), CAST_PTR(void**, PLATFORM_VALUE(0x4F0F13,0x4DA173)),
		};
		#pragma endregion

		#pragma region MessageDeltaPointerEndChecks
		static void** MessageDeltaPointerEndChecks[] = {
			CAST_PTR(void**, PLATFORM_VALUE(0x4EFF83,0x4D91E3)), CAST_PTR(void**, PLATFORM_VALUE(0x4F0017,0x4D9277)), CAST_PTR(void**, PLATFORM_VALUE(0x4F03D7,0x4D9637)),
		};

		static byte* MessageDeltaTypeCountChecks8bit[] = {
			CAST_PTR(byte*, PLATFORM_VALUE(0x4F0B9D,0x4D9DFD)),
		};
		#pragma endregion

		FUNC_PTR(NETWORK_GAME_CLIENT_HANDLE_MESSAGE_DELTA_MESSAGE_BODY_CALL,0x4DEECA, 0x4C63CA);
			DATA_PTR(DONT_SEND_OBJECT_NEW_MSG,								0x6B7288, 0x61FAA0);
			FUNC_PTR(NETWORK_GAME_CLIENT_HANDLE_MESSAGE_DELTA_MESSAGE_BODY,	0x4DD8B0, 0x4C4DB0);


		ENGINE_PTR(Networking::s_network_game_server, global_network_game_server_data, 0x7FC260, 0x6C78E0);
		ENGINE_PTR(Networking::s_network_game_client, global_network_game_client_data, 0x80DD40, 0x6D9C80);

		FUNC_PTR(NETWORK_GAME_SERVER_WRITE,							0x4E0410, 0x4C78F0);
		FUNC_PTR(MDP_ENCODE_STATELESS,								0x4F05A0, 0x4D9800); // really mdpi_encode
		FUNC_PTR(MDP_DECODE_STATELESS_ITERATED,						0x4F01F0, 0x4D9450);
		FUNC_PTR(NETWORK_CONNECTION_FLUSH_QUEUE,					0x4E1130, 0x4C85B0);
		FUNC_PTR(BITSTREAM_WRITE_BUFFER,							0x4D2E00, 0x4BBD70);
		FUNC_PTR(NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES,	0x4E5200, 0x4CC760); // network_game_server_send_message_to_all_machines2
		FUNC_PTR(NETWORK_GAME_SERVER_SEND_MESSAGE_TO_MACHINE,		0x4E50B0, 0x4CC6D0);
		FUNC_PTR(MDP_DISCARD_ITERATION_BODY,						0x4F02D0, 0x4D9530);
	#endif


//////////////////////////////////////////////////////////////////////////
// Networking.cpp
#elif __EL_INCLUDE_FILE_ID == __EL_NETWORKING_NETWORKING
	ENGINE_PTR(s_update_client_globals, update_client_globals,		0x692DD0, 0x5FB650);
	ENGINE_PTR(s_update_server_globals, update_server_globals,		0x68CCC0, 0x5F5540);
	ENGINE_PTR(network_update_globals, network_update_globals,		0x624A68, 0x59A408);
	ENGINE_PTR(Enums::game_connection, global_game_connection,		0x6B46E8, 0x61CF60);
	ENGINE_DPTR(s_network_game_server, global_network_game_server,	0x6B729C, 0x61FAB4);
	ENGINE_DPTR(s_network_game_client, global_network_game_client,	0x6B72A0, 0x61FAB8);

	FUNC_PTR(NETWORK_GAME_ADD_PLAYER,									0x4E1AC0, 0x4C8F40);
	FUNC_PTR(NETWORK_GAME_SERVER_ADD_PLAYER_TO_GAME__HOOK_ADD_PLAYER,	0x4E2EAA, 0x4CA41A);
	FUNC_PTR(NETWORK_GAME_REMOVE_PLAYER,								0x4E1C20, 0x4C90A0);
	// just a few bytes after this gets called is another call to ngrp, but its for the s_network_client's game member
	FUNC_PTR(CLIENT_MACHINE_CLEANUP__HOOK_REMOVE_PLAYER,				0x4E47E3, 0x4CBDE3);


//////////////////////////////////////////////////////////////////////////
// Server.cpp
#elif __EL_INCLUDE_FILE_ID == __EL_NETWORKING_SERVER
	namespace Networking
	{
		ENGINE_PTR(wchar_t, sv_password,								0x6B72BC, 0x61FAD4);
		ENGINE_PTR(char, sv_rcon_password,								0x6B73D8, 0x61FBF4);
		ENGINE_PTR(int32, sv_timelimit,									0x634C18, 0x5AA5B0);
		ENGINE_PTR(int32, halo_argv_port,								0x633808, 0x5A91A0);
		ENGINE_PTR(int32, halo_argv_client_port,						0x63380C, 0x5A91A4);
	};

	//////////////////////////////////////////////////////////////////////////
	// Server
	namespace Server
	{
		ENGINE_PTR(s_network_sv_file_globals, network_sv_file_globals,			0x653404, 0x5C5204);
		ENGINE_PTR(s_network_sv_mapcycle_globals, network_sv_mapcycle_globals,	0x6230CC, 0x598A8C);
		ENGINE_PTR(s_network_sv_globals, network_sv_globals,					0x6B72B4, 0x61FACC);

	#if PLATFORM_IS_DEDI
		ENGINE_PTR(int32, server_instance,			PTR_NULL, 0x6257E8);

		ENGINE_PTR(bool, event_type_logging,		PTR_NULL, 0x5C5334);
		ENGINE_PTR(bool, event_type_echoing,		PTR_NULL, 0x5C5344);
	#endif
	};


//////////////////////////////////////////////////////////////////////////
// GameSpyApi.cpp
#elif __EL_INCLUDE_FILE_ID == __EL_NETWORKING_GAMESPY_API
	namespace Networking
	{
		ENGINE_DPTR(s_gamespy_socket, gs_Socket,									0x68C3B8, 0x5F4C38);
		ENGINE_DPTR(s_gamespy_socket, gs_LoopbackSocket,							0x68C3BC, 0x5F4C3C);
		ENGINE_PTR(s_gamespy_config, gamespy_config,								0x63AD04, 0x5AED34);
		ENGINE_PTR(s_gamespy_globals, gamespy_globals,								0x6BD9A0, 0x626068);
		ENGINE_PTR(s_gamespy_server_browser_globals, gamespy_server_browser_globals,0x6B4418, 0x61CC94);

		ENGINE_PTR(s_gamespy_product, gamespy_products_list,						0x6BE400, 0x6268C0); // [4]

		DATA_PTR(compiler_null_string,			0x5F365C, 0x54F33C); // TODO: not the best place for this...
		FUNC_PTR(GAMESPY_GET_CLIENT_KEY_HASH,	0x579CF0, 0x5283F0);


		ENGINE_PTR(long_enum, game_version_id1,								0x4DC2A6, 0x4C3836);
		ENGINE_PTR(long_enum, game_version_id2,								0x4DC483, 0x4C3A13);
		ENGINE_PTR(long_enum, game_version_id3,								0x4E3FC3, 0x4CB553);
	};


#else
	#error Undefined engine layout include for: __EL_INCLUDE_NETWORKING
#endif