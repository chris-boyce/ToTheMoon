// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "HealthStaminaBarBase.generated.h"

class UStatBarBase;
UCLASS(Abstract)
class TOTHEMOON_API UHealthStaminaBarBase : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UStatBarBase> HealthBar = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UStatBarBase> StaminaBar = nullptr;
};
