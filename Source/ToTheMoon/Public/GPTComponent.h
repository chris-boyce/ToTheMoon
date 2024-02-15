// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "OpenAIDefinitions.h"
#include "Components/ActorComponent.h"
#include "GPTComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOTHEMOON_API UGPTComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGPTComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void CreateMission();
	UFUNCTION()
	void OnReturnedChat(FChatCompletion ChatCompletion, const FString& ErrorMessage, bool Success);

	UPROPERTY(EditAnywhere, Category="MissionControls")
	TArray<FChatLog> ChatLog;

	UPROPERTY(EditAnywhere, Category="MissionControls")
	FString ReturnString = "";
};
