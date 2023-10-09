using UnrealBuildTool;
using System.Collections.Generic;

public class Project2EditorTarget : TargetRules
{
	public Project2EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Project2" } );
	}
}