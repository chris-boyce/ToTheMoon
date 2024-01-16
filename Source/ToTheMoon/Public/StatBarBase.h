// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "Brushes/SlateColorBrush.h"
#include "StatBarBase.generated.h"

class UVerticalBox;
class UBorder;
class UImage;
class UTextBlock;

UCLASS(Abstract)
class TOTHEMOON_API UStatBarBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue);
	
	UFUNCTION()
	void OnFloatStatUpdated(float OldValue, float NewValue, float MaxValue);

#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
protected:

	virtual void NativeOnInitialized() override;
	
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> MainBorder = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UVerticalBox> PercentBars = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UImage> Icon = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> Percentbar_Filled = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> PercentBar_Empty = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UTextBlock> ValueText = nullptr;

private:
	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FSlateBrush IconBrush;

	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FLinearColor BarBackgroundColor = FLinearColor(0.3f, 0.f, 0.f, 0.3f);

	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FLinearColor BarForegroundColor = FLinearColor(1.f, 0.f, 0.f, 0.75f);
	
	UPROPERTY(EditAnywhere, Category="Stat Bar")
	bool IsFullSize = true;
	
	UPROPERTY(EditAnywhere, Category="Stat Bar|Testing", meta=(ClampMin=0, UIMin=0, ClampMax=1, UIMax=1, Units="Percent"))
	float CurrentPercentage = 0.f;
	
	UPROPERTY(EditAnywhere, Category="Stat Bar|Testing", meta=(ClampMin=0, UIMin=0))
	float CurrentValue = 100.f;
	
	FText CurrentValueText;
	
	void ProcessCurrentValueText();
	
	void UpdateWidget();

	
};
