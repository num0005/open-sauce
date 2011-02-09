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
using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace BlamLib.CheApe
{
	internal sealed class XmlInterface
	{
		#region Editor markup strings
		/// <summary>
		/// Identifiers after this character are the tooltip data. Any other Markup strings terminate the tooltip string
		/// </summary>
		const string MarkupTooltip = "#";
		/// <summary>
		/// Identifiers after this character are the units data. Any other Markup strings terminate the tooltip string
		/// </summary>
		const string MarkupUnits = ":";

		/// <summary>
		/// Identifier means this field is locked
		/// </summary>
		const char MarkupLocked = '*';
		/// <summary>
		/// Identifier means this field is hidden
		/// </summary>
		const char MarkupHidden = ')'; // or its '~'
		/// <summary>
		/// Identifier means this field is a block name and the field's definition has the block definition we're naming at runtime in the editor
		/// </summary>
		const char MarkupBlockname = '^';
		/// <summary>
		/// Identifier means this field is deprecated, but is still in place for removal later or w/e
		/// </summary>
		const char MarkupDepricated = '@';
		#endregion

		public sealed class FieldType
		{
			#region Opcode
			private int opcode;
			/// <summary>
			/// Enumeration index of this field type
			/// </summary>
			public int Opcode	{ get { return opcode; } }
			#endregion

			#region SizeOf
			private int sizeOf;
			/// <summary>
			/// Byte size of this field type
			/// </summary>
			public int SizeOf	{ get { return sizeOf; } }
			#endregion

			#region Name
			private string name;
			/// <summary>
			/// String representation of this field type
			/// </summary>
			public string Name	{ get { return name; } }
			#endregion

			#region RequiresDefinition
			private bool requiresDefinition;
			/// <summary>
			/// Does this kind of field type require an explicit definition in the field definition data?
			/// </summary>
			public bool RequiresDefinition	{ get { return requiresDefinition; } }
			#endregion

			#region ByteSwapCodes
			private List<int> byteSwapCodes = new List<int>();
			/// <summary>
			/// The codes used for byte swapping this field type
			/// </summary>
			public List<int> ByteSwapCodes	{ get { return byteSwapCodes; } }
			#endregion

			public FieldType(IO.XmlStream s)
			{
				s.ReadAttribute("opcode", 16, ref opcode);
				s.ReadAttribute("size", 16, ref sizeOf);
				s.ReadAttribute("name", ref name);
				s.ReadAttributeOpt("needsDefinition", ref requiresDefinition);

				#region Read byte swap codes
				foreach (XmlNode n in s.Cursor.ChildNodes)
					if (n.Name == "byteSwap")
					{
						s.SaveCursor(n);
						int code = 0;
						foreach (XmlNode n2 in s.Cursor.ChildNodes)
						{
							if (n2.Name != "code") continue;

							s.SaveCursor(n2);
							s.ReadAttribute("value", 10, ref code);
							byteSwapCodes.Add(code);
							s.RestoreCursor();
						}
						s.RestoreCursor();
					}
				#endregion
			}
		};


		#region Engine
		BlamVersion engine = BlamVersion.Unknown;
		/// <summary>
		/// Engine this CheApe definition belongs to
		/// </summary>
		public BlamVersion Engine { get { return engine; } }
		#endregion

		#region FieldTypes
		private List<FieldType> fieldTypes = new List<FieldType>();
		/// <summary>
		/// Field types defined in the xml definition
		/// </summary>
		public List<FieldType> FieldTypes	{ get { return fieldTypes; } }
		#endregion

		public XmlInterface(BlamVersion engine) { this.engine = engine; }

		/// <summary>
		/// Get a tag field type's definition index based on it's name string
		/// </summary>
		/// <param name="type_name"></param>
		/// <returns></returns>
		/// <remarks>If <paramref name="type_name"/> equals "None", returns -1</remarks>
		public int GetTypeIndex(string type_name)
		{
			if(type_name != "None")
				foreach (FieldType ft in fieldTypes) if (ft.Name == type_name) return ft.Opcode;

			return -1;
		}

		internal static string BuildEditorNameString(IO.XmlStream s)
		{
			StringBuilder value = new StringBuilder();
			string temp = string.Empty;

			if (s.ReadAttributeOpt("name", ref temp)) value.Append(temp);

			if (s.ReadAttributeOpt("locked", ref temp) && Util.ParseBooleanLazy(temp))
				value.Append(MarkupLocked);

			if (s.ReadAttributeOpt("hidden", ref temp) && Util.ParseBooleanLazy(temp))
				value.Append(MarkupHidden);

			if (s.ReadAttributeOpt("blockname", ref temp) && Util.ParseBooleanLazy(temp))
				value.Append(MarkupBlockname);

			if (s.ReadAttributeOpt("deprecated", ref temp) && Util.ParseBooleanLazy(temp))
				value.Append(MarkupDepricated);

			if (s.ReadAttributeOpt("units", ref temp))
				value.AppendFormat("{0}{1}", MarkupUnits, temp);

			if (s.ReadAttributeOpt("tooltip", ref temp))
				value.AppendFormat("{0}{1}", MarkupTooltip, temp);

			return value.ToString();
		}

		public void Read(string path, string name)
		{
			using (IO.XmlStream s = new BlamLib.IO.XmlStream(path, name, this))
			{
				s.ReadAttribute("game", ref engine);

				foreach (XmlNode n in s.Cursor.ChildNodes)
					if (n.Name == "fieldTypes")
					{
						s.SaveCursor(n);
						foreach (XmlNode n2 in s.Cursor.ChildNodes)
						{
							if (n2.Name != "type") continue;

							s.SaveCursor(n2);
							fieldTypes.Add(new FieldType(s));
							s.RestoreCursor();
						}
						s.RestoreCursor();
					}
					else if(n.Name == "editorMarkup")
					{
						s.SaveCursor(n);
						foreach (XmlNode n2 in s.Cursor.ChildNodes)
						{
							if (n2.Name != "entry") continue;

							//s.SaveCursor(n2);
							// TODO
							//s.RestoreCursor();
						}
						s.RestoreCursor();
					}
			}
		}
	};
}