using UnrealBuildTool;
using System.Collections.Generic;

public class Project2Target : TargetRules
{
	public Project2Target( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Project2" } );
	}
}