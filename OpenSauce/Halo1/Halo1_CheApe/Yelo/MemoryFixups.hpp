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
#pragma once

namespace Yelo
{
	class c_memory_fixups
	{
		static struct s_override_paths {
			// this HAS to be lower case
			char root[MAX_PATH];

			struct {
				char path[MAX_PATH];
				char path_with_slash[MAX_PATH];
			}data;

			struct {
				char path[MAX_PATH];
				char path_with_slash[MAX_PATH];

				char temp_uncompressed_cache_file[MAX_PATH];
			}maps;

			// these HAVE to be lower case
			struct {
				char path[MAX_PATH];
				char path_with_slash[MAX_PATH];

				// "tags\"
				char folder_name_with_slash_single[64];
				// ".\tags"
				char folder_name_with_slash_single_relative[64];

				// "\tags\"
				char folder_name_with_slash[64];
				// ".\tags\"
				char folder_name_with_slash_relative[64];
#if PLATFORM_ID == PLATFORM_SAPIEN
				// "tags\levels"
				char folder_name_with_levels[64];
#endif
			}tags;
		}_override_paths;

		static DWORD WINAPI GetCurrentDirectoryHack(
			__in DWORD nBufferLength,
			__out_ecount_part_opt(nBufferLength, return + 1) LPSTR lpBuffer);

#if PLATFORM_ID == PLATFORM_TOOL
		static char* PLATFORM_API tag_file_index_build_strchr_hack(char* str, char val);
		static void tag_file_index_build_strchr_hack_initialize();
#endif

		static void FixupsInitializeDataPaths(cstring data_override);
		static void FixupsInitializeMapsPaths(cstring maps_override);

		static void FixupsInitializeTagPaths(cstring tags_override, cstring tags_name_override);
		static void FixupsInitializeFilePaths();

	public:
		enum fixup_type : _enum
		{
			_fixup_type_none,
			_fixup_type_replace_memory,
			_fixup_type_replace_pointer,
			_fixup_type_replace_tag_field,
			_fixup_type,
		};

		struct s_fixup
		{
			fixup_type type;
			int16 type_data;
			void* address[3]; // PLATFORM_ID - 1
			void* definition[3]; // PLATFORM_ID - 1
			PAD32;
		}; BOOST_STATIC_ASSERT( sizeof(s_fixup) == 0x20 );

		static void ProcessFixup(s_fixup* fixup);
		static void ProcessFixups();

		// The paths have to be initialized before any engine-modifying CheApe systems are 
		// ran so no code (mainly debug logging) is ran before file paths are updated.
		static void InitializePaths();
		static void DisposePaths();

		static void Initialize();
		static void Dispose();

		static void DebugPaths();
	};
};