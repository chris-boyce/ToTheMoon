// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestBase.generated.h"

struct FLocationQuest;
struct FCollectionQuest;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStepCompleted);


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
	QT_CollectItems,
	QT_GoTo,
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
	FStepCompleted StepCompleted;
	
	virtual void InitQuestVariables(const FCollectionQuest& Parameters) {}

	virtual void InitQuestVariables(const FLocationQuest& Parameters) {}
	
	
};
