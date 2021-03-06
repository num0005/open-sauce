/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <blamlib/Halo1/tag_files/tag_groups.hpp>

namespace Yelo
{
	namespace TagGroups
	{
		struct s_sound_permutation
		{
			TAG_FIELD(tag_string, name);
			TAG_FIELD(real, skip_fraction);
			TAG_FIELD(real, gain);
			TAG_FIELD(_enum, compression);
			TAG_FIELD(int16, next_permutation_index);

			datum_index cache_block_index;		// 0x2C
			void* cache_base_address;			// 0x30
			datum_index cache_tag_index;		// 0x34
			//int32 unused0;						// 0x38, used on the pc. size of the decompressed xbox adpcm samples buffer (cache_base_address)
			//int32 unused1;						// 0x3C, used on the pc. owner sound tag index
			int32 decompressed_buffer_size;
			datum_index owner_tag_index;

			// samples' tag_data flags
			enum { _samples_in_data_file_bit = 0 }; // data is in the sounds data file, not the cache file
			TAG_FIELD(tag_data, samples);

			TAG_FIELD(tag_data, mouth_data);
			TAG_FIELD(tag_data, subtitle_data);
		}; BOOST_STATIC_ASSERT( sizeof(s_sound_permutation) == 0x7C );

		struct s_sound_pitch_range
		{
			TAG_FIELD(tag_string, name);
			TAG_FIELD(real, natural_pitch);
			TAG_FIELD(real_bounds, bend_bounds);
			TAG_FIELD(int16, actual_permutation_count);
			PAD16;
			TAG_PAD(tag_block, 1);
			TAG_TBLOCK_(permutations, s_sound_permutation);
		}; BOOST_STATIC_ASSERT( sizeof(s_sound_pitch_range) == 0x48 );

		struct s_sound_definition_playback_parameters
		{
			TAG_FIELD(real_bounds, audible_distance);
			TAG_FIELD(real, skip_fraction);
			TAG_FIELD(real_bounds, random_pitch_bounds);
			TAG_FIELD(angle_bounds, cone_angles); // inner, outer
			TAG_FIELD(real, outer_cone_gain);
			TAG_FIELD(real, gain_modifier);
			TAG_FIELD(real, max_bend_per_second);
		};
		struct s_sound_definition_scale_modifiers
		{
			TAG_FIELD(real, skip_fraction_modifier);
			TAG_FIELD(real, gain_modifier);
			TAG_FIELD(real, pitch_modifier);
		};
		struct s_sound_promotion_parameters
		{
			TAG_FIELD(tag_reference, sound, "snd!");
			TAG_FIELD(int16, count);
			PAD16;
		};
		struct sound_definition
		{
			enum { k_group_tag = 'snd!' };

			TAG_FIELD(long_flags, flags);
			TAG_FIELD(_enum, sound_class);
			TAG_FIELD(_enum, sample_rate);

			TAG_FIELD(s_sound_definition_playback_parameters, playback_parameters);
			// unused, when-scale-is-ZERO, unused, when-scale-is-ONE, unused
			TAG_FIELD(s_sound_definition_scale_modifiers, scale_modifiers)[5];

			TAG_FIELD(_enum, encoding);
			TAG_FIELD(_enum, compression);

			TAG_FIELD(s_sound_promotion_parameters, promotion_parameters);

			TAG_PAD(tag_data, 1);
			TAG_TBLOCK(pitch_ranges, s_sound_pitch_range);
		}; BOOST_STATIC_ASSERT( sizeof(sound_definition) == 0xA4 );
	};
};