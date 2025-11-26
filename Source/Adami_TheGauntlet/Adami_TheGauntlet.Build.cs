// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Adami_TheGauntlet : ModuleRules
{
	public Adami_TheGauntlet(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Adami_TheGauntlet",
			"Adami_TheGauntlet/Variant_Platforming",
			"Adami_TheGauntlet/Variant_Platforming/Animation",
			"Adami_TheGauntlet/Variant_Combat",
			"Adami_TheGauntlet/Variant_Combat/AI",
			"Adami_TheGauntlet/Variant_Combat/Animation",
			"Adami_TheGauntlet/Variant_Combat/Gameplay",
			"Adami_TheGauntlet/Variant_Combat/Interfaces",
			"Adami_TheGauntlet/Variant_Combat/UI",
			"Adami_TheGauntlet/Variant_SideScrolling",
			"Adami_TheGauntlet/Variant_SideScrolling/AI",
			"Adami_TheGauntlet/Variant_SideScrolling/Gameplay",
			"Adami_TheGauntlet/Variant_SideScrolling/Interfaces",
			"Adami_TheGauntlet/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
