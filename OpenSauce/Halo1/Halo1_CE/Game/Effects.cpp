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
#include "Game/Effects.hpp"

#include "Memory/MemoryInterface.hpp"

namespace Yelo
{
	namespace Effects
	{
#define __EL_INCLUDE_ID			__EL_INCLUDE_GAME
#define __EL_INCLUDE_FILE_ID	__EL_GAME_EFFECTS
#include "Memory/_EngineLayout.inl"

		t_contrail_data* Contrails()									DPTR_IMP_GET(contrails);
		t_contrail_point_data* ContrailPoints()							DPTR_IMP_GET(contrail_points);
		t_particle_data* Particles()									DPTR_IMP_GET(particles);
		t_effect_data* Effects()										DPTR_IMP_GET(effects);
		t_effect_location_data* EffectLocations()						DPTR_IMP_GET(effect_locations);
		t_particle_systems_data* ParticleSystems()						DPTR_IMP_GET(particle_systems);
		t_particle_system_particles_data* ParticleSystemParticles()		DPTR_IMP_GET(particle_system_particles);

		s_structure_detail_objects_data* StructureDetailObjects()		DPTR_IMP_GET(structure_detail_objects);
		s_structure_decals_data* StructureDecals()						DPTR_IMP_GET(structure_decals);
		s_breakable_surface_globals_data* BreakableSurfaceGlobals()		DPTR_IMP_GET(breakable_surface_globals);
		t_decals_data* Decals()											DPTR_IMP_GET(decals);
		s_decal_globals_data* DecalGlobals()							DPTR_IMP_GET(decal_globals);
		s_decal_vertex_cache_data* DecalVertexCache()					DPTR_IMP_GET(decal_vertex_cache);


		void Initialize()
		{
			Memory::CreateHookRelativeCall(&Effects::Update, GET_FUNC_VPTR(EFFECTS_UPDATE_HOOK), 0xC3);
		}

		void Dispose()
		{
		}

		void PLATFORM_API Update()
		{
		}
	};
};