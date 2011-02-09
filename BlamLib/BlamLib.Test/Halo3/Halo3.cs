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
﻿using System;
using System.Collections.Generic;
using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace BlamLib.Test
{
	[TestClass]
	public partial class Halo3 : BaseTestClass
	{
		internal const string kTestResultsPath = TestLibrary.kTestResultsPath + @"Halo3\";

		[ClassInitialize]
		public static void Initialize(TestContext context)
		{
			(Program.GetManager(BlamVersion.Halo3_Xbox) as Managers.IStringIdController)
				.StringIdCacheOpen(BlamVersion.Halo3_Xbox);
			(Program.GetManager(BlamVersion.Halo3_Epsilon) as Managers.IStringIdController)
				.StringIdCacheOpen(BlamVersion.Halo3_Epsilon);

			Directory.CreateDirectory(kTestResultsPath);
		}
		[ClassCleanup]
		public static void Dispose()
		{
			(Program.GetManager(BlamVersion.Halo3_Epsilon) as Managers.IStringIdController)
				.StringIdCacheClose(BlamVersion.Halo3_Epsilon);
			(Program.GetManager(BlamVersion.Halo3_Xbox) as Managers.IStringIdController)
				.StringIdCacheClose(BlamVersion.Halo3_Xbox);
		}

		const string kDirectoryXbox = @"C:\Mount\A\Bungie\Games\Halo3\Xbox\";
		static readonly string[] kMapNames_Retail = {
			@"Retail\maps\005_intro.map",
			@"Retail\maps\010_jungle.map",
			@"Retail\maps\020_base.map",
			@"Retail\maps\030_outskirts.map",
			@"Retail\maps\040_voi.map",
			@"Retail\maps\050_floodvoi.map",
			@"Retail\maps\070_waste.map",
			@"Retail\maps\100_citadel.map",
			@"Retail\maps\110_hc.map",
			@"Retail\maps\120_halo.map",
			@"Retail\maps\130_epilogue.map",

			@"Retail\maps\chill.map",
			@"Retail\maps\construct.map",
			@"Retail\maps\cyberdyne.map",
			@"Retail\maps\deadlock.map",
			@"Retail\maps\guardian.map",
			@"Retail\maps\isolation.map",
			@"Retail\maps\mainmenu.map",
			@"Retail\maps\riverworld.map",
			@"Retail\maps\salvation.map",
			@"Retail\maps\shrine.map",
			@"Retail\maps\snowbound.map",
			@"Retail\maps\zanzibar.map",

			// dlc_heroic
			@"Retail\dlc_heroic\armory.map",
//			@"Retail\dlc_heroic\armory2.map",
			@"Retail\dlc_heroic\bunkerworld.map",
			@"Retail\dlc_heroic\warehouse.map",

			// dlc_legendary
			@"Retail\dlc_legendary\ghosttown.map",
			@"Retail\dlc_legendary\lockout.map",
			@"Retail\dlc_legendary\sidewinder.map",

			// dlc_mythic
			@"Retail\dlc_mythic\descent.map",
			@"Retail\dlc_mythic\sandbox.map",
			@"Retail\dlc_mythic\spacecamp.map",

			// dlc_mythic2
			@"retail\dlc_mythic2\docks.map",
			@"retail\dlc_mythic2\fortress.map",
			@"retail\dlc_mythic2\midship.map",

			// dlc_chillout
			@"Retail\dlc_chillout\chillout.map",
		};
		static readonly string[] kMapNames_Epsilon = {
			// 11729.07.08.10.0021
			@"Epsilon_11729\maps\030_outskirts.map",
			@"Epsilon_11729\maps\chill.map",
			@"Epsilon_11729\maps\deadlock.map",
			@"Epsilon_11729\maps\mainmenu.map",
			@"Epsilon_11729\maps\riverworld.map",
			@"Epsilon_11729\maps\salvation.map",
			@"Epsilon_11729\maps\shrine.map",
			@"Epsilon_11729\maps\snowbound.map",
			@"Epsilon_11729\maps\zanzibar.map",

			// 11856.07.08.20.2332
			@"Epsilon_11856\maps\030_outskirts.map",
			@"Epsilon_11856\maps\deadlock.map",
			@"Epsilon_11856\maps\mainmenu.map",
			@"Epsilon_11856\maps\riverworld.map",
			@"Epsilon_11856\maps\shrine.map",
			@"Epsilon_11856\maps\snowbound.map",
			@"Epsilon_11856\maps\zanzibar.map",
		};
		const string kMapPathChillout = kDirectoryXbox + @"Retail\dlc_chillout\chillout.map";
		const string kMapPathSandbox = kDirectoryXbox + @"Retail\dlc_mythic\sandbox.map";


		#region CacheOutputInformation
		internal static void CacheOutputInformationMethod(object param)
		{
			var args = param as CacheFileOutputInfoArgs;

			using (var handler = new CacheHandler<Blam.Halo3.CacheFileBase>(args.Game, args.MapPath))
			{
				handler.Read();
				var cache = handler.CacheInterface;

				Blam.CacheFile.OutputStringIds(cache,
					BuildResultPath(args.TestResultsPath, args.Game, cache.Header.Name, "string_ids", "txt"), true);
				Blam.CacheFile.OutputTags(cache,
					BuildResultPath(args.TestResultsPath, args.Game, cache.Header.Name, null, "txt"));
			}
		}
		[TestMethod]
		public void Halo3TestCacheOutputXbox()
		{
			CacheFileOutputInfoArgs.TestThreadedMethod(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.Halo3_Xbox, kDirectoryXbox, kMapNames_Retail);
		}
		[TestMethod]
		public void Halo3TestCacheOutputXboxEpsilon()
		{
			CacheFileOutputInfoArgs.TestThreadedMethod(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.Halo3_Epsilon, kDirectoryXbox, kMapNames_Epsilon);
		}
		#endregion
	};
}