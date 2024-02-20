// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStepCompleted);

struct FKillQuestData;
struct FLocationQuest;
struct FCollectionQuest;
USTRUCT(BlueprintType)
struct FQuestData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category="TEMP")
	FString MissionName;
	UPROPERTY(VisibleAnywhere, Category="TEMP")
	FString MissionDescription;
	UPROPERTY(VisibleAnywhere, Category="TEMP")
	FString ItemType;
	UPROPERTY(VisibleAnywhere, Category="TEMP")
	int Amount;
	UPROPERTY(VisibleAnywhere, Category="TEMP")
	FString EnemyToKill;
	UPROPERTY(VisibleAnywhere, Category="TEMP")
	FString Location;
	
};
UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	NotStarted,
	InProgress,
	Completed,
	Failed
};
UENUM(BlueprintType)
enum class EQuestType : uint8
{
	GoTo,
	Collect,
	Kill
};

UCLASS()
class TOTHEMOON_API UQuestBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EQuestType QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestDescription;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EQuestStatus QuestStatus;

	UFUNCTION(BlueprintCallable)
	virtual void StartQuest();
	
	UFUNCTION(BlueprintCallable)
	virtual void CompleteStep();

	UPROPERTY()
	UWorld* WorldReference;

	UPROPERTY()
	FStepCompleted StepCompleted;
	
	virtual void InitQuestVariables(const FCollectionQuest& Parameters) {}

	virtual void InitQuestVariables(const FLocationQuest& Parameters) {}

	virtual void InitQuestVariables(const FKillQuestData& Parameters) {}

	virtual void SetWorldReference(UWorld* InWorld) {WorldReference = InWorld;};
	
	
};
