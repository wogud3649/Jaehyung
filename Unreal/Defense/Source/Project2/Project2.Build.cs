using UnrealBuildTool;

public class Project2 : ModuleRules
{
	public Project2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "SlateCore" });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}