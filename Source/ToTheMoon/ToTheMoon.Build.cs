// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ToTheMoon : ModuleRules
{
	public ToTheMoon(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "Paper2D" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "UMG", "Slate", "SlateCore", "Json", "JsonUtilities", "Niagara", "OpenAIAPI", "Paper2D"});
		
		PublicAdditionalLibraries.Add("C:/Users/skyog/Documents/GitHub/LlamaReupload/Libraries/llama.lib");
		RuntimeDependencies.Add("C:/Users/skyog/Documents/GitHub/LlamaReupload/Binaries/Win64/llama.dll");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
