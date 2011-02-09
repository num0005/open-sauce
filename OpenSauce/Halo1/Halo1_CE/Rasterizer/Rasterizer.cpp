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
#include "Rasterizer/Rasterizer.hpp"
#if !PLATFORM_IS_DEDI

#include "Memory/MemoryInterface.hpp"
#include "Game/ScriptLibrary.hpp"
#include "Common/GameSystems.hpp"
#include "Rasterizer/GBuffer.hpp"
#include "Rasterizer/DX9/DX9.hpp"
#include "Rasterizer/PostProcessing/PostProcessing.hpp"

namespace Yelo
{
	namespace Rasterizer
	{
#define __EL_INCLUDE_ID			__EL_INCLUDE_RASTERIZER
#define __EL_INCLUDE_FILE_ID	__EL_RASTERIZER_RASTERIZER
#include "Memory/_EngineLayout.inl"

		//////////////////////////////////////////////////////////////////////////
		// s_render_target
		bool		s_render_target::IsEnabled() const { return (surface && texture); }
		HRESULT		s_render_target::CreateTarget(IDirect3DDevice9* device, uint32 rt_width, uint32 rt_height, D3DFORMAT rt_format)
		{
			width = rt_width;
			height = rt_height;
			format = rt_format;
			HRESULT hr = device->CreateTexture(						
					width,
					height,
					1,
					D3DUSAGE_RENDERTARGET,
					format,
					D3DPOOL_DEFAULT,
					&texture,
					NULL);

			if(SUCCEEDED(hr))
				hr = texture->GetSurfaceLevel(0, &surface);

			if(FAILED(hr))
				this->ReleaseTarget();
			return hr;
		}

		void		s_render_target::ReleaseTarget()
		{
			Yelo::safe_release(surface);
			Yelo::safe_release(texture);
		}

		void		s_render_target::ClearTarget(IDirect3DDevice9* device, D3DCOLOR color, DWORD flags)
		{
			if(!IsEnabled())	return;
			
			device->SetRenderTarget(0, surface);
			device->Clear( 0L, NULL, flags, color, 1.0f, 0L );
		}
		//////////////////////////////////////////////////////////////////////////

		s_render_globals* RenderGlobals()			PTR_IMP_GET2(render_globals);
		s_render_target* GlobalRenderTargets()		PTR_IMP_GET2(global_render_targets);
#pragma region DebugOptions
		s_rasterizer_debug_options* DebugOptions()	PTR_IMP_GET2(rasterizer_debug_data);

		struct rasterizer_debug_table
		{
			uint32 field;
			uint32 index;
		};
		static rasterizer_debug_table _rasterizer_debug_table[] = {
			{offsetof(s_rasterizer_debug_options, stats),									0xC},
			{offsetof(s_rasterizer_debug_options, mode),									0xD},
			{offsetof(s_rasterizer_debug_options, smart),									0xF},
			{offsetof(s_rasterizer_debug_options, debug_model_vertices),					0x10},
			{offsetof(s_rasterizer_debug_options, debug_model_lod),							0x11},
			{offsetof(s_rasterizer_debug_options, debug_transparents),						0x12},
			{offsetof(s_rasterizer_debug_options, debug_meter_shader),						0x13},
			{offsetof(s_rasterizer_debug_options, models),									0x14},
			{offsetof(s_rasterizer_debug_options, model_transparents),						0x15},
			{offsetof(s_rasterizer_debug_options, draw_first_person_weapon_first),			0x16},
			{offsetof(s_rasterizer_debug_options, stencil_mask),							0x17},
			{offsetof(s_rasterizer_debug_options, environment),								0x18},
			{offsetof(s_rasterizer_debug_options, environment_lightmaps),					0x19},
			{offsetof(s_rasterizer_debug_options, environment_shadows),						0x1A},
			{offsetof(s_rasterizer_debug_options, environment_diffuse_lights),				0x1B},
			{offsetof(s_rasterizer_debug_options, environment_decals),						0x1D},
			{offsetof(s_rasterizer_debug_options, environment_specular_lights),				0x1E},
			{offsetof(s_rasterizer_debug_options, environment_specular_lightmaps),			0x1F},
			{offsetof(s_rasterizer_debug_options, environment_reflection_lightmap_mask),	0x20},
			{offsetof(s_rasterizer_debug_options, environment_reflection_mirrors),			0x21},
			{offsetof(s_rasterizer_debug_options, environment_reflections),					0x22},
			{offsetof(s_rasterizer_debug_options, environment_transparents),				0x23},
			{offsetof(s_rasterizer_debug_options, environment_fog),							0x24},
			{offsetof(s_rasterizer_debug_options, environment_fog_screen),					0x25},
			{offsetof(s_rasterizer_debug_options, water),									0x26},
			{offsetof(s_rasterizer_debug_options, lens_flares),								0x27},
			{offsetof(s_rasterizer_debug_options, dynamic_unlit_geometry),					0x28},
			{offsetof(s_rasterizer_debug_options, dynamic_lit_geometry),					0x29},
			{offsetof(s_rasterizer_debug_options, dynamic_screen_geometry),					0x2A},
			{offsetof(s_rasterizer_debug_options, hud_motion_sensor),						0x2B},
			{offsetof(s_rasterizer_debug_options, detail_objects),							0x2C},
			{offsetof(s_rasterizer_debug_options, debug_geometry),							0x2D},
			{offsetof(s_rasterizer_debug_options, debug_geometry_multipass),				0x2E},
			{offsetof(s_rasterizer_debug_options, bump_mapping),							0x31},
			{offsetof(s_rasterizer_debug_options, lightmap_ambient),						0x32},
			//{offsetof(s_rasterizer_debug_options, ), 0x33},
			{offsetof(s_rasterizer_debug_options, lightmaps_incident),						0x34},
			{offsetof(s_rasterizer_debug_options, lightmaps_filtering),						0x35},
			{offsetof(s_rasterizer_debug_options, model_lightning_ambient),					0x36},
			{offsetof(s_rasterizer_debug_options, environment_alpha_testing),				0x37},
			{offsetof(s_rasterizer_debug_options, environment_specular_mask),				0x38},
			{offsetof(s_rasterizer_debug_options, shadows_convolution),						0x39},
			{offsetof(s_rasterizer_debug_options, shadows_debug),							0x3A},
			{offsetof(s_rasterizer_debug_options, water_mipmapping),						0x3B},
			{offsetof(s_rasterizer_debug_options, active_camouflage),						0x3C},
			{offsetof(s_rasterizer_debug_options, active_camouflage_multipass),				0x3D},
			{offsetof(s_rasterizer_debug_options, plasma_energy),							0x3E},
			{offsetof(s_rasterizer_debug_options, lens_flares_occlusion),					0x3F},
			{offsetof(s_rasterizer_debug_options, lens_flares_occlusion_debug),				0x40},
			{offsetof(s_rasterizer_debug_options, ray_of_buddha),							0x41},
			{offsetof(s_rasterizer_debug_options, screen_flashes),							0x42},
			{offsetof(s_rasterizer_debug_options, screen_effects),							0x43},
			{offsetof(s_rasterizer_debug_options, DXTC_noise),								0x44},
			{offsetof(s_rasterizer_debug_options, soft_filter),								0x45},
			{offsetof(s_rasterizer_debug_options, secondary_render_target_debug),			0x46},
			{offsetof(s_rasterizer_debug_options, profile_log),								0x47},
			{offsetof(s_rasterizer_debug_options, detail_objects_offset_multiplier),		0x48},
			{offsetof(s_rasterizer_debug_options, zbias), 									0x49},
			{offsetof(s_rasterizer_debug_options, zoffset),									0x4A},
			{offsetof(s_rasterizer_debug_options, force_all_player_views_to_default_player),0x4B},
			{offsetof(s_rasterizer_debug_options, safe_frame_bounds),						0x4C},
			{offsetof(s_rasterizer_debug_options, zsprites),								0x4E},
			{offsetof(s_rasterizer_debug_options, filthy_decal_fog_hack),					0x4F},
			{offsetof(s_rasterizer_debug_options, splitscreen_VB_optimization),				0x50},
			{offsetof(s_rasterizer_debug_options, profile_print_locks),						0x51},
			{offsetof(s_rasterizer_debug_options, profile_objectlook_time),					0x52},
			//{offsetof(rasterizer_debug_options, ), 0x53},
			{offsetof(s_rasterizer_debug_options, pad3_scale),								0x54},
			{offsetof(s_rasterizer_debug_options, f0),										0x55},
			{offsetof(s_rasterizer_debug_options, f1),										0x56},
			{offsetof(s_rasterizer_debug_options, f2),										0x57},
			{offsetof(s_rasterizer_debug_options, f3),										0x58},
			{offsetof(s_rasterizer_debug_options, f4),										0x59},
			{offsetof(s_rasterizer_debug_options, f5),										0x5A},
			//{offsetof(s_rasterizer_debug_options, ), 0x},
		};
		static const int32 RASTERIZER_DEBUG_TABLE_COUNT = NUMBEROF(_rasterizer_debug_table);
#pragma endregion

		s_rasterizer_frame_inputs* FrameInputs()	PTR_IMP_GET2(rasterizer_frame_inputs);

		// release direct3D resources before the device is destroyed
		void RasterizerDisposeHook()
		{			
			Yelo::Main::s_dx_component* components;
			const Yelo::int32 component_count = Yelo::Main::GetDXComponents(components);

			for(Yelo::int32 x = 0; x <= component_count; x++)
				components[x].Release();

			// Return the code flow back to the game
			static uint32 RETN_ADDRESS = GET_FUNC_PTR(RASTERIZER_DISPOSE);
			__asm	call RETN_ADDRESS
		}

#pragma warning( push )
#pragma warning( disable : 4311 ) // pointer truncation
#pragma warning( disable : 4312 ) // conversion from 'unsigned long' to 'void *' of greater size
		void Rasterizer::Initialize()
		{
			// TODO: If using DX_WRAPPER, refer to the DxWrapper.cpp file 
			// instead of hooking the game render loop
#if !defined(DX_WRAPPER)
			Memory::WriteRelativeCall(&Rasterizer::Update, GET_FUNC_VPTR(RENDER_WINDOW_END_HOOK));
#endif			
			// hook the calls to rasterizer_dispose
			Memory::WriteRelativeCall(&RasterizerDisposeHook, GET_FUNC_VPTR(RASTERIZER_DISPOSE_CALL_FROM_RASTERIZER));
			Memory::WriteRelativeCall(&RasterizerDisposeHook, GET_FUNC_VPTR(RASTERIZER_DISPOSE_CALL_FROM_SHELL));

			rasterizer_debug_table* rdt = NULL;
			Scripting::hs_global_definition* global_def = NULL;
			uint32 address = CAST_PTR(uint32, Rasterizer::DebugOptions());
			for(int32 x = 0; x < RASTERIZER_DEBUG_TABLE_COUNT; x++)
			{
				rdt = &_rasterizer_debug_table[x];

				// this is the only time we should be modifying the hs definitions
				// outside of the ScriptLibrary code, so do some cast magic
				global_def = CAST_QUAL(Scripting::hs_global_definition*, 
					&(Scripting::HSExternalGlobals()[rdt->index]) );	// get the hs global definition we're about to fix up

				global_def->address = CAST_PTR(void*, address + rdt->field);// fix the global definition's address to point to the correct memory
			}
		}
#pragma warning( pop )

		void Dispose()
		{
		}

		void Update()
		{
#if !defined(DX_WRAPPER)
			// only thing that changes is the vertex type (texture or color)
			// so I just made a global render states function
			// and put the setFVF (vertex change function) in each class
			//Rasterizer::SetRenderStates();

			__asm {
				call DX9::Direct3DDevice
				mov edx, [eax]
			}
#endif
		}

		void LoadSettings(TiXmlElement* dx9_element)
		{
			DX9::c_gbuffer_system::LoadSettings(dx9_element);
			Postprocessing::LoadSettings(dx9_element);
		}

		void SaveSettings(TiXmlElement* dx9_element)
		{
			DX9::c_gbuffer_system::SaveSettings(dx9_element);
			Postprocessing::SaveSettings(dx9_element);
		}

		void SetRenderStates()
		{
			DX9::Direct3DDevice()->SetVertexShader(NULL);
			DX9::Direct3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
			DX9::Direct3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			DX9::Direct3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			DX9::Direct3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			DX9::Direct3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		}
	};
};

#endif