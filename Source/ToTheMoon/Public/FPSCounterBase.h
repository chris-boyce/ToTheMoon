// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "FPSCounterBase.generated.h"

class UTextBlock;
UCLASS()
class TOTHEMOON_API UFPSCounterBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UTextBlock> FPSCounter = nullptr;

	UFUNCTION()
	void UpdateWidget(FString FPSString);
};
