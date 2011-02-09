/*
    Yelo: Open Sauce SDK

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
#pragma once

namespace Yelo
{
	namespace TagGroups
	{
		/* !-- Gameplay --! */
		/* !-- Gameplay --! */


		/* !-- Scripting --! */
		struct script_construct_block
		{
			TAG_FIELD(tag_string, name[2]); // So we can have at most 62 characters for the name
			TAG_FIELD(int16, index);
		};
		struct script_function_block : public script_construct_block
		{
			TAG_ENUM(return_type, Enums::hs_type);
			TAG_TBLOCK(parameters, _enum); // 32
		};
		struct script_global_block : public script_construct_block
		{
			TAG_ENUM(type, Enums::hs_type);
		};
		struct scripting_block
		{
			TAG_TBLOCK(new_functions, script_function_block);
			TAG_TBLOCK(new_globals, script_global_block);
		};
		/* !-- Scripting --! */


		struct s_dual_wield_weapon_definition
		{
			TAG_FIELD(tag_reference, primary_weapon, 'weap');
			TAG_FIELD(tag_reference, secondary_weapon, 'weap');
			TAG_FIELD(tag_reference, combined_weapon, 'weap');

			TAG_PAD(int32, 8);
		}; BOOST_STATIC_ASSERT( sizeof(s_dual_wield_weapon_definition) == 0x50 );

		struct s_object_damage_region_permutation_extension
		{
			TAG_FIELD(tag_string, name);
			TAG_FIELD(real, damage_threshold);

			TAG_FIELD(tag_string, effect_marker_name);
			TAG_FIELD(tag_reference, transition_effect, 'effe');
			TAG_PAD(int32, 8);

			TAG_FIELD(tag_string, damage_effect_marker_name);
			TAG_FIELD(tag_reference, transition_damage_effect, 'jpt!');
			TAG_PAD(int32, 8);
		}; BOOST_STATIC_ASSERT( sizeof(s_object_damage_region_permutation_extension) == 0xC4 );
		struct s_object_damage_region_extension
		{
			TAG_FIELD(tag_string, name);
			TAG_TBLOCK(permutations, s_object_damage_region_permutation_extension); // 32
		}; BOOST_STATIC_ASSERT( sizeof(s_object_damage_region_extension) == 0x2C );
		struct s_object_damage_extension
		{
			TAG_FIELD(tag_reference, object, 'obje');
			TAG_TBLOCK(regions, s_object_damage_region_extension); // 32
		}; BOOST_STATIC_ASSERT( sizeof(s_object_damage_extension) == 0x1C );


		// yelo for globals
		struct project_yellow_globals
		{
#if !PLATFORM_IS_EDITOR
			const 
#endif
				int16 version;	enum { k_version = 1, k_group_tag = 'gelo' };
			struct _flags {
				TAG_FLAG16(hide_health_when_zoomed);
				TAG_FLAG16(hide_shield_when_zoomed);
				TAG_FLAG16(hide_motion_sensor_when_zoomed);
			}flags; BOOST_STATIC_ASSERT( sizeof(_flags) == sizeof(word_flags) );

			TAG_FIELD(tag_string, mod_name, "", "name of the engine 'mod' these globals and, inheriting scenario, are for");

			TAG_FIELD(tag_reference, explicit_references, "tagc");

			/* !-- Preprocessing --! */
			// PREPROCESSING DOESN'T EXIST AT RUNTIME. Only for the tools

			struct preprocess_maplist_block
			{
				TAG_FIELD(tag_string, name);
				TAG_FIELD(tag_reference, scenario, "scnr");
				TAG_PAD(int32, 6); // 24
			};

			struct preprocess_block
			{
				struct _flags {
					TAG_FLAG(unused, "");
				}flags;	BOOST_STATIC_ASSERT( sizeof(_flags) == sizeof(long_flags) );

				struct {
					TAG_TBLOCK(campaign, preprocess_maplist_block);		// 24
					TAG_TBLOCK(multiplayer, preprocess_maplist_block);	// 32
				}maplist;

				TAG_PAD(int32, 20); // 80

			}; TAG_TBLOCK(preprocess, preprocess_block); // 1
			/* !-- Preprocessing --! */


			/* !-- UI --! */
			struct {
				TAG_FIELD(tag_reference, custom_sp_map_list, "str#"); // SHOULD BE AUTOFILLED BY preprocess_maplist_block
				TAG_FIELD(tag_reference, custom_mp_map_list, "str#"); // SHOULD BE AUTOFILLED BY preprocess_maplist_block
				TAG_PAD(tag_reference, 2); // 32
			}ui;
			/* !-- UI --! */


			/* !-- Networking --! */
			struct network_game_player_biped
			{
				TAG_FIELD(tag_string, name, "", "name of this block definition");
				TAG_FIELD(tag_reference, definition, "unit", "unit definition for this player's biped");
				TAG_PAD(int32, 5); // 20
			};

			struct {
				TAG_TBLOCK(player_bipeds, network_game_player_biped); // 2

				TAG_PAD(int32, 5); // 20
			}networking;
			/* !-- Networking --! */


			/* !-- Gameplay --! */
			struct gameplay_game_type_player_settings
			{
				struct _flags {
					TAG_FLAG(inherit, "inherit from the \"global\" player settings");
				}flags;	BOOST_STATIC_ASSERT( sizeof(_flags) == sizeof(long_flags) );
				TAG_PAD(int32, 19); // 76
			};
			struct gameplay_game_type_player 
			{
				TAG_FIELD(tag_string, type_name, "", "name of the game type this block is for");
				TAG_TBLOCK(settings, gameplay_game_type_player_settings); // 17, first block is the "global" settings, rest are the player index settings
				TAG_PAD(int32, 6); // 24
			};

			struct {
				TAG_TBLOCK(game_type_players, gameplay_game_type_player); // 64

				TAG_PAD(tag_block, 2); // 24
			}gameplay;
			/* !-- Gameplay --! */

			/* !-- Scripting --! */
			TAG_TBLOCK(yelo_scripting, scripting_block); // 1
			/* !-- Scripting --! */


			TAG_TBLOCK(dual_wielding, s_dual_wield_weapon_definition); // 256
			TAG_TBLOCK(object_damage_extensions, s_object_damage_extension); // 512

			TAG_PAD(int32, 14); // 56
		};
	};
};