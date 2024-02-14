// Semester 2 Christopher Boyce : TTM Project


#include "NPCReader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"

NPCReader::NPCReader()
{
}

FNPCData NPCReader::ReadJSONFile(const FString& FileName)
{
	FNPCData CharacterData;

	// Construct the file path using the FString variable as the filename
	FString FilePath = FPaths::ProjectContentDir() + "NPCs/" + FileName + ".json";

	// Check if the file exists
	if (FPaths::FileExists(FilePath))
	{
		// Read the JSON file
		FString JSONString;
		FFileHelper::LoadFileToString(JSONString, *FilePath);

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JSONString);

		// Deserialize the JSON data
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			// Read name
			CharacterData.Name = JsonObject->GetStringField("name");

			// Read introString
			CharacterData.IntroString = JsonObject->GetStringField("intro_string");

			CharacterData.Lore = JsonObject->GetStringField("lore");

			// Read level
			CharacterData.Level = JsonObject->GetIntegerField("level");
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON data."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("File not found: %s"), *FilePath);
	}

	return CharacterData;
}


NPCReader::~NPCReader()
{
}
