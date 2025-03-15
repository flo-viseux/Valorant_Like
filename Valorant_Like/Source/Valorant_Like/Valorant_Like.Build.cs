// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Valorant_Like : ModuleRules
{
	public Valorant_Like(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
