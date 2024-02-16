// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "OpenAIDefinitions.h"
#include "QuestBase.h"
#include "Components/ActorComponent.h"
#include "GPTComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestDataValid, EQuestType, QuestType, FQuestData, QuestData);

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

	UFUNCTION()
	void CreateMission();
	
	UFUNCTION()
	void OnReturnedChat(FChatCompletion ChatCompletion, const FString& ErrorMessage, bool Success);

	UPROPERTY(EditAnywhere, Category="MissionControls")
	TArray<FChatLog> ChatLog;

	UPROPERTY(EditAnywhere, Category="MissionControls")
	FString ReturnString = "";

	UPROPERTY(EditAnywhere, Category="MissionControls")
	bool isEnable = false;

	UFUNCTION()
	FString FinalPromptText();

	UFUNCTION()
	FString GoToPromptText();

	UFUNCTION()
	FString CollectPromptText();

	UFUNCTION()
	FString KillPromptText();

	UFUNCTION()
	void StringToJson(FString GPTReturnString);


	FString StartPrompt = "You are a assistant that generates JSONS. You always return just the JSON with no additional context. You are an assistant responsible for generating JSONs for different types of missions. Each mission has a 'MissionType' attribute with three options: 'Collect', 'GoTo', and 'Kill'. Pick Randomly";
	FString EndPrompt = "Ensure the generated JSONs accurately represent each mission type based on the provided options.";


	UPROPERTY(VisibleAnywhere)
	EQuestType QuestType;

	UPROPERTY(VisibleAnywhere)
	FQuestData QuestData;

	FOnQuestDataValid OnQuestDataValid;
	
};
