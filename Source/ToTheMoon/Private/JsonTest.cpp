// Semester 2 Christopher Boyce : TTM Project


#include "JsonTest.h"
#include "Dom/JsonObject.h"
AJsonTest::AJsonTest()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AJsonTest::BeginPlay()
{
	Super::BeginPlay();
	JSonReading(TestString);
	
}

void AJsonTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJsonTest::JSonReading(FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		// Extract values from the JSON object
		FString MissionName;
		FString MissionDescription;
		FString ItemToCollect;
		int32 AmountToCollect;

		if (JsonObject->TryGetStringField("MissionName", MissionName) &&
			JsonObject->TryGetStringField("MissionDescription", MissionDescription) &&
			JsonObject->TryGetStringField("ItemToCollect", ItemToCollect) &&
			JsonObject->TryGetNumberField("AmountToCollect", AmountToCollect))
		{
			// Now you have the values in the variables, you can use them as needed
			UE_LOG(LogTemp, Warning, TEXT("MissionName: %s"), *MissionName);
			UE_LOG(LogTemp, Warning, TEXT("MissionDescription: %s"), *MissionDescription);
			UE_LOG(LogTemp, Warning, TEXT("ItemToCollect: %s"), *ItemToCollect);
			UE_LOG(LogTemp, Warning, TEXT("AmountToCollect: %d"), AmountToCollect);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to extract values from JSON object."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON string."));
	}

}

