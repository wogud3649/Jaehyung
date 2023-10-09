using UnrealBuildTool;

public class DefenseRPG : ModuleRules
{
	public DefenseRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"GameplayTasks",
			"SlateCore",
			"HeadMountedDisplay",
			"NavigationSystem",
			"AIModule"
		});

		PublicIncludePaths.Add(ModuleDirectory);
	}
}