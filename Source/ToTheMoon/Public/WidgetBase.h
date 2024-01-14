// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

UCLASS()
class TOTHEMOON_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
	
};
