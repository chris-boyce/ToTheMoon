// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "OverloadLayoutBase.generated.h"

class UImage;
class UHealthStaminaBarBase;
class UFPSCounterBase;

UCLASS(Abstract)
class TOTHEMOON_API UOverloadLayoutBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UHealthStaminaBarBase> HealthStaminaBar = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UFPSCounterBase> FPSCounterWidget = nullptr;
	
	void VisibilityToggle();
	
	void UpdateWidget();
private:
	FTimerHandle TimerHandle;
	

	

	
	
};
