// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"

#include "WidgetBase.h"
#include "MinimalLayoutBase.generated.h"

class UHealthStaminaBarBase;
class UImage;

UCLASS(Abstract)
class TOTHEMOON_API UMinimalLayoutBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UHealthStaminaBarBase> HealthStaminaBar = nullptr;

	//UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	//TObjectPtr<UImage> Crosshair = nullptr;

	
	
};
