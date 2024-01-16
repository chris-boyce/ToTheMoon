// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "QuestDisplayBase.generated.h"


class UTextBlock;

UCLASS()
class TOTHEMOON_API UQuestDisplayBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Quest Display", meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestName = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Quest Display", meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestDescription = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Quest Display", meta = (BindWidget))
	TObjectPtr<UTextBlock> StatsDescription = nullptr;
	
	UFUNCTION(BlueprintCallable, Category= "Quest Display")
	void UpdateQuestWidget(FString mQuestName, FString mQuestDescription, int mCurrentScore, int FinalScore);

	UFUNCTION()
	void UpdateQuest();





	
};
