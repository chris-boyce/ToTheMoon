// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "OverloadLayoutBase.generated.h"

class UQuestDisplayBase;
class UImage;
class UHealthStaminaBarBase;
class UFPSCounterBase;
class UMinimap;

UCLASS(Abstract)
class TOTHEMOON_API UOverloadLayoutBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UHealthStaminaBarBase> HealthStaminaBar = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UFPSCounterBase> FPSCounterWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UQuestDisplayBase> QuestDisplayBase = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UMinimap> MiniMapDisplay = nullptr;
	
	void VisibilityToggle();
	
	void UpdateWidget();
private:
	FTimerHandle TimerHandle;
	

	

	
	
};
