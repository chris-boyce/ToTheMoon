// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "OverloadLayoutBase.generated.h"

class UImage;
class UHealthStaminaBarBase;
/**
 * 
 */
UCLASS(Abstract)
class TOTHEMOON_API UOverloadLayoutBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UHealthStaminaBarBase> HealthStaminaBar = nullptr;

	//UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	//TObjectPtr<UImage> Crosshair = nullptr;
	
};
