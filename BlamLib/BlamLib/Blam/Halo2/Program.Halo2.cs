/*
    BlamLib: .NET SDK for the Blam Engine

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
﻿
namespace BlamLib
{
	partial class Program
	{
#if !NO_HALO2
		/// <summary>
		/// Halo 2 global wide settings
		/// </summary>
		public static class Halo2
		{
			#region Manager
			static Blam.Halo2.GameDefinition manager = new Blam.Halo2.GameDefinition();
			/// <summary>
			/// Halo 2's specific manager instance
			/// </summary>
			public static Blam.Halo2.GameDefinition Manager { get { return manager; } }
			#endregion

			/// <summary>
			/// Initialize the resources used by the Halo 2 systems
			/// </summary>
			public static void Initialize()
			{
				manager.Read(Managers.GameManager.GetRelativePath(BlamLib.Managers.GameManager.Namespace.Halo2), "Halo2.xml");
			}

			/// <summary>
			/// Close the resources used by the Halo 2 systems
			/// </summary>
			public static void Close()
			{
				CloseXbox();
				CloseAlpha();
				ClosePc();
				manager.Close();
			}

			#region Xbox
			/// <summary>
			/// Path to the file 'mainmenu.map'
			/// </summary>
			static string XboxMainmenuPath = string.Empty;
			/// <summary>
			/// Object for the file  'mainmenu.map'
			/// </summary>
			public static Blam.Halo2.CacheFile XboxMainmenu = null;

			/// <summary>
			/// Path to the file 'shared.map'
			/// </summary>
			static string XboxSharedPath = string.Empty;
			/// <summary>
			/// Object for the file 'shared.map'
			/// </summary>
			public static Blam.Halo2.CacheFile XboxShared = null;

			/// <summary>
			/// Path to the file 'single_player_shared.map'
			/// </summary>
			static string XboxCampaignPath = string.Empty;
			/// <summary>
			/// Object for the file 'single_player_shared.map'
			/// </summary>
			public static Blam.Halo2.CacheFile XboxCampaign = null;

			/// <summary>
			/// Loads the Halo 2 files needed to fully run this library
			/// </summary>
			/// <remarks>
			/// Path[0] = Mainmenu
			/// Path[1] = Shared
			/// Path[2] = Single Player Shared
			/// </remarks>
			/// <param name="paths"></param>
			public static void LoadXbox(params string[] paths)
			{
				Blam.DatumIndex di;

				if (paths.Length >= 1 && System.IO.File.Exists(paths[0]))
				{
					di = manager.OpenCacheFile(BlamVersion.Halo2_Xbox, XboxMainmenuPath = paths[0]);
					XboxMainmenu = manager.GetCacheFile(di) as BlamLib.Blam.Halo2.CacheFile;
					XboxMainmenu.Read();
				}

				if (paths.Length >= 2 && System.IO.File.Exists(paths[1]))
				{
					di = manager.OpenCacheFile(BlamVersion.Halo2_Xbox, XboxSharedPath = paths[1]);
					XboxShared = manager.GetCacheFile(di) as BlamLib.Blam.Halo2.CacheFile;
					XboxShared.Read();
				}

				if (paths.Length >= 3 && System.IO.File.Exists(paths[2]))
				{
					di = manager.OpenCacheFile(BlamVersion.Halo2_Xbox, XboxCampaignPath = paths[2]);
					XboxCampaign = manager.GetCacheFile(di) as BlamLib.Blam.Halo2.CacheFile;
					XboxCampaign.Read();
				}
			}

			/// <summary>
			/// Closes the shared xbox caches
			/// </summary>
			public static void CloseXbox()
			{
				if (XboxMainmenu != null)	manager.CloseCacheFile(XboxMainmenu.CacheId);
				if (XboxShared != null)		manager.CloseCacheFile(XboxShared.CacheId);
				if (XboxCampaign != null)	manager.CloseCacheFile(XboxCampaign.CacheId);
			}
			#endregion

			#region Alpha
			/// <summary>
			/// Path to the file 'mainmenu.map'
			/// </summary>
			static string AlphaMainmenuPath = string.Empty;
			/// <summary>
			/// Object for the file  'mainmenu.map'
			/// </summary>
			public static Blam.Halo2.CacheFile AlphaMainmenu = null;

			/// <summary>
			/// Path to the file 'shared.map'
			/// </summary>
			static string AlphaSharedPath = string.Empty;
			/// <summary>
			/// Object for the file 'shared.map'
			/// </summary>
			public static Blam.Halo2.CacheFile AlphaShared = null;

			/// <summary>
			/// Loads the Halo 2 files needed to fully run this library
			/// </summary>
			/// <remarks>
			/// Path[0] = Mainmenu
			/// Path[1] = Shared
			/// </remarks>
			/// <param name="paths"></param>
			public static void LoadAlpha(params string[] paths)
			{
				Blam.DatumIndex di;

				if (paths.Length >= 1 && System.IO.File.Exists(paths[0]))
				{
					di = manager.OpenCacheFile(BlamVersion.Halo2_Alpha, AlphaMainmenuPath = paths[0]);
					AlphaMainmenu = manager.GetCacheFile(di) as BlamLib.Blam.Halo2.CacheFile;
					AlphaMainmenu.Read();
				}

				if (paths.Length >= 2 && System.IO.File.Exists(paths[1]))
				{
					di = manager.OpenCacheFile(BlamVersion.Halo2_Alpha, AlphaSharedPath = paths[1]);
					AlphaShared = manager.GetCacheFile(di) as BlamLib.Blam.Halo2.CacheFile;
					AlphaShared.Read();
				}
			}

			/// <summary>
			/// Closes the shared Alpha xbox caches
			/// </summary>
			public static void CloseAlpha()
			{
				if (AlphaMainmenu != null)	manager.CloseCacheFile(AlphaMainmenu.CacheId);
				if (AlphaShared != null)	manager.CloseCacheFile(AlphaShared.CacheId);
			}
			#endregion

			#region PC
			/// <summary>
			/// Path to the file 'mainmenu.map'
			/// </summary>
			static string PcMainmenuPath = string.Empty;
			/// <summary>
			/// Object for the file  'mainmenu.map'
			/// </summary>
			public static Blam.Halo2.CacheFile PcMainmenu = null;

			/// <summary>
			/// Path to the file 'shared.map'
			/// </summary>
			static string PcSharedPath = string.Empty;
			/// <summary>
			/// Object for the file 'shared.map'
			/// </summary>
			public static Blam.Halo2.CacheFile PcShared = null;

			/// <summary>
			/// Path to the file 'single_player_shared.map'
			/// </summary>
			static string PcCampaignPath = string.Empty;
			/// <summary>
			/// Object for the file 'single_player_shared.map'
			/// </summary>
			public static Blam.Halo2.CacheFile PcCampaign = null;

			/// <summary>
			/// Loads the Halo 2 files needed to fully run this library
			/// </summary>
			/// <remarks>
			/// Path[0] = Mainmenu
			/// Path[1] = Shared
			/// Path[2] = Single Player Shared
			/// </remarks>
			/// <param name="paths"></param>
			public static void LoadPc(params string[] paths)
			{
				Blam.DatumIndex di;

				if (paths.Length >= 1 && System.IO.File.Exists(paths[0]))
				{
					di = manager.OpenCacheFile(BlamVersion.Halo2_PC, PcMainmenuPath = paths[0]);
					PcMainmenu = manager.GetCacheFile(di) as BlamLib.Blam.Halo2.CacheFile;
					PcMainmenu.Read();
				}

				if (paths.Length >= 2 && System.IO.File.Exists(paths[1]))
				{
					di = manager.OpenCacheFile(BlamVersion.Halo2_PC, PcSharedPath = paths[1]);
					PcShared = manager.GetCacheFile(di) as BlamLib.Blam.Halo2.CacheFile;
					PcShared.Read();
				}

				if (paths.Length >= 3 && System.IO.File.Exists(paths[2]))
				{
					di = manager.OpenCacheFile(BlamVersion.Halo2_PC, PcCampaignPath = paths[2]);
					PcCampaign = manager.GetCacheFile(di) as BlamLib.Blam.Halo2.CacheFile;
					PcCampaign.Read();
				}
			}

			/// <summary>
			/// Closes the shared pc caches
			/// </summary>
			public static void ClosePc()
			{
				if (PcMainmenu != null)	manager.CloseCacheFile(PcMainmenu.CacheId);
				if (PcShared != null)	manager.CloseCacheFile(PcShared.CacheId);
				if (PcCampaign != null)	manager.CloseCacheFile(PcCampaign.CacheId);
			}
			#endregion

			/// <summary>
			/// Returns a CacheFile object based on a ResourcePtr
			/// </summary>
			/// <param name="cf">Halo2 cache housing the <paramref name="ptr"/> value</param>
			/// <param name="ptr">ResourcePtr to use</param>
			/// <returns>The CacheFile <paramref name="ptr"/> references</returns>
			/// <remarks>Returns null if <paramref name="ptr"/> doesn't point to anything</remarks>
			public static Blam.Halo2.CacheFile FromLocation(Blam.Halo2.CacheFile cf, Blam.ResourcePtr ptr)
			{
				if (ptr.Offset == -1) return null;

				var ver = cf.EngineVersion;

				if (ptr.Map == BlamLib.Blam.ResourcePtr.Location.Internal)
					return cf;

				if (ver == BlamVersion.Halo2_Xbox)
				{
					switch (ptr.Map)
					{
						case BlamLib.Blam.ResourcePtr.Location.MainMenu:return XboxMainmenu;
						case BlamLib.Blam.ResourcePtr.Location.Shared:	return XboxShared;
						case BlamLib.Blam.ResourcePtr.Location.Campaign:return XboxCampaign;
					}
				}
				else if (ver == BlamVersion.Halo2_Alpha)
				{
					switch (ptr.Map)
					{
						case BlamLib.Blam.ResourcePtr.Location.MainMenu:return AlphaMainmenu;
						case BlamLib.Blam.ResourcePtr.Location.Shared:	return AlphaShared;
						case BlamLib.Blam.ResourcePtr.Location.Campaign:throw new Debug.Exceptions.UnreachableException();
					}
				}
				else if (ver == BlamVersion.Halo2_PC)
				{
					switch (ptr.Map)
					{
						case BlamLib.Blam.ResourcePtr.Location.MainMenu:return PcMainmenu;
						case BlamLib.Blam.ResourcePtr.Location.Shared:	return PcShared;
						case BlamLib.Blam.ResourcePtr.Location.Campaign:return PcCampaign;
					}
				}

				return null;
			}

			/// <summary>
			/// Returns a CacheFile object based on a ResourcePtr
			/// </summary>
			/// <remarks>
			/// If the resource is internal then <paramref name="is_internal"/> gets set to true
			/// and <paramref name="cf"/> is returned. If null and <paramref name="is_internal"/> is not set,
			/// the CacheFile is either not loaded or the location was invalid.
			/// 
			/// Returns null if <paramref name="ptr"/> doesn't point to anything
			/// </remarks>
			/// <param name="cf">Halo2 cache housing the <paramref name="ptr"/> value</param>
			/// <param name="ptr">ResourcePtr to use</param>
			/// <param name="is_internal">bool reference to set if <paramref name="ptr"/> is internal</param>
			/// <returns>The CacheFile <paramref name="ptr"/> references</returns>
			public static Blam.Halo2.CacheFile FromLocation(Blam.Halo2.CacheFile cf, Blam.ResourcePtr ptr, out bool is_internal)
			{
				var ver = cf.EngineVersion;
				is_internal = false;

				if (ptr.Offset == -1) return null;

				if(ptr.Map == BlamLib.Blam.ResourcePtr.Location.Internal)
				{
					is_internal = true;
					return cf;
				}

				return FromLocation(cf, ptr);
			}
		};
#endif
	};
}