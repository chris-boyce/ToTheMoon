// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FirstPersonHUD.generated.h"

class UMinimalLayoutBase;
class UModerateLayoutBase;
class UOverloadLayoutBase;
class APlayerCharacter;

UENUM(BlueprintType)
enum class EHudViewMode: uint8
{
	CleanAndPristine,
	Minimal ,
	Moderate ,
	SensoryOverload 
};

inline EHudViewMode& operator++(EHudViewMode& ViewMode)
{	
	if (ViewMode == EHudViewMode::SensoryOverload)
		ViewMode = EHudViewMode::CleanAndPristine;
	else
		ViewMode = static_cast<EHudViewMode>(static_cast<int>(ViewMode) + 1);

	return ViewMode;
}

inline EHudViewMode& operator--(EHudViewMode& ViewMode)
{
	if (ViewMode == EHudViewMode::CleanAndPristine)
		ViewMode = EHudViewMode::SensoryOverload;
	else
		ViewMode = static_cast<EHudViewMode>(static_cast<int>(ViewMode) - 1);
	return ViewMode;
}

UCLASS()
class TOTHEMOON_API AFirstPersonHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MinimalLayoutClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ModerateLayoutClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverloadLayoutClass = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetCurrentViewMode(EHudViewMode NewViewMode);
	
	UFUNCTION(BlueprintCallable)
	void CycleToNextViewMode();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY(EditAnywhere)
	EHudViewMode CurrentViewMode = EHudViewMode::Moderate;
	
	void UpdateWidgets();
	
	void ClearAllHandlers();

	void ToggleIsVisableWidget();

	UPROPERTY()
	TObjectPtr<UWorld> World = nullptr;

	UPROPERTY()
	TObjectPtr<UMinimalLayoutBase>  MinimalLayoutWidget  = nullptr;
	
	UPROPERTY()
	TObjectPtr<UModerateLayoutBase> ModerateLayoutWidget = nullptr;
	
	UPROPERTY()
	TObjectPtr<UOverloadLayoutBase> OverloadLayoutWidget = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;
};
