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
using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace BlamLib.Test
{
	[TestClass]
	public partial class Halo2 : BaseTestClass
	{
		internal const string kTestResultsPath = TestLibrary.kTestResultsPath + @"Halo2\";
		const string kTestResultsPathXbox = kTestResultsPath + @"Xbox\";
		const string kTestResultsPathXboxAlpha = kTestResultsPath + @"Xbox\Alpha\";
		const string kTestResultsPathPc = kTestResultsPath + @"PC\";
		static string EngineGetTestResultsPath(BlamVersion engine)
		{
			switch (engine)
			{
				case BlamVersion.Halo2_Xbox:	return kTestResultsPathXbox;
				case BlamVersion.Halo2_Alpha:	return kTestResultsPathXboxAlpha;
				case BlamVersion.Halo2_PC:		return kTestResultsPathPc;

				default: return kTestResultsPath;
			}
		}

		[ClassInitialize]
		public static void Initialize(TestContext context)
		{
			Directory.CreateDirectory(kTestResultsPath);
			Directory.CreateDirectory(kTestResultsPathXbox);
			Directory.CreateDirectory(kTestResultsPathXboxAlpha);
			Directory.CreateDirectory(kTestResultsPathPc);
		}
		[ClassCleanup]
		public static void Dispose()
		{
		}

		const string kMapsDirectoryXbox = @"C:\Mount\A\Bungie\Games\Halo2\Xbox\Retail\Maps\";
		const string kMapsDirectoryPc = @"C:\Mount\A\Bungie\Games\Halo2\PC\Maps\";
		const string kMapsDirectoryXboxAlpha = @"C:\Mount\A\Bungie\Games\Halo2\Xbox\Alpha\Maps\";
		static readonly string[] kMapNames = {
			"mainmenu.map",
			"shared.map",
			"single_player_shared.map",
			"00a_introduction.map",
			"01a_tutorial.map",
			"01b_spacestation.map",
			"03a_oldmombasa.map",
			"03b_newmombasa.map",
			"04a_gasgiant.map",
			"04b_floodlab.map",
			"05a_deltaapproach.map",
			"05b_deltatowers.map",
			"06a_sentinelwalls.map",
			"06b_floodzone.map",
			"07a_highcharity.map",
			"07b_forerunnership.map",
			"08a_deltacliffs.map",
			"08b_deltacontrol.map",
			"ascension.map",
			"backwash.map",
			"burial_mounds.map",
			"coagulation.map",
			"colossus.map",
			"containment.map",
			"cyclotron.map",
			"deltatap.map",
			"dune.map",
			"elongation.map",
			"foundation.map",
			"gemini.map",
			"headlong.map",
			"lockout.map",
			"midship.map",
			"triplicate.map",
			"turf.map",
			"warlock.map",
			"waterworks.map",
			"zanzibar.map",
		};
		static readonly string[] kMapNamesXbox = {
			"derelict.map",
			"highplains.map",
		};
		static readonly string[] kMapNamesPc = {
			"beavercreek.map", // I thought Xbox had this too?
			"example.map",
			"example_sans_sharing.map",
			"forerunner_sample.map",
			"human_sample.map",
			"needle.map",
			"street_sweeper.map",
		};
		static readonly string[] kMapNamesXboxAlpha = {
			"mainmenu.map",
			"shared.map",
			"cyclotron.map",
			"midship.map",
			"waterworks.map",
			"zanzibar.map",
			//C:\Mount\B\Bungie\Halo2\Xbox\Alpha\test\4d53008200000000\lockout.map

			// Epsilon
			//C:\Mount\B\Bungie\Halo2\Xbox\Alpha\test\4d53008200000778\box_multiplayer.map
		};

		#region CacheOutputInformation
		static void CacheOutputInformationMethod(object param)
		{
			var args = param as CacheFileOutputInfoArgs;

			using (var handler = new CacheHandler<Blam.Halo2.CacheFile>(args.Game, args.MapPath))
			{
				handler.Read();
				var cache = handler.CacheInterface;

				string test_results_path = EngineGetTestResultsPath(args.Game);

				Blam.CacheFile.OutputStringIds(cache,
					BuildResultPath(test_results_path, args.Game, cache.Header.Name, "string_ids", "txt"), true);
				Blam.CacheFile.OutputTags(cache,
					BuildResultPath(test_results_path, args.Game, cache.Header.Name, null, "txt"));
			}
		}
		[TestMethod]
		public void Halo2TestCacheOutputXbox()
		{
			(Program.GetManager(BlamVersion.Halo2_Xbox) as Managers.IStringIdController)
				.StringIdCacheOpen(BlamVersion.Halo2_Xbox);

			CacheFileOutputInfoArgs.TestThreadedMethod(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.Halo2_Xbox, kMapsDirectoryXbox, kMapNames);
			CacheFileOutputInfoArgs.TestThreadedMethod(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.Halo2_Xbox, kMapsDirectoryXbox, kMapNamesXbox);

			(Program.GetManager(BlamVersion.Halo2_Xbox) as Managers.IStringIdController)
				.StringIdCacheClose(BlamVersion.Halo2_Xbox);
		}
		[TestMethod]
		public void Halo2TestCacheOutputPc()
		{
			(Program.GetManager(BlamVersion.Halo2_PC) as Managers.IStringIdController)
				.StringIdCacheOpen(BlamVersion.Halo2_PC);

			CacheFileOutputInfoArgs.TestThreadedMethod(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.Halo2_PC, kMapsDirectoryPc, kMapNames);
			CacheFileOutputInfoArgs.TestThreadedMethod(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.Halo2_PC, kMapsDirectoryPc, kMapNamesPc);

			(Program.GetManager(BlamVersion.Halo2_PC) as Managers.IStringIdController)
				.StringIdCacheClose(BlamVersion.Halo2_PC);
		}
		[TestMethod]
		public void Halo2TestCacheOutputXboxAlpha()
		{
			(Program.GetManager(BlamVersion.Halo2_Alpha) as Managers.IStringIdController)
				.StringIdCacheOpen(BlamVersion.Halo2_Alpha);

			CacheFileOutputInfoArgs.TestThreadedMethod(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.Halo2_Alpha, kMapsDirectoryXboxAlpha, kMapNamesXboxAlpha);

			(Program.GetManager(BlamVersion.Halo2_Alpha) as Managers.IStringIdController)
				.StringIdCacheClose(BlamVersion.Halo2_Alpha);
		}
		#endregion
	};
}