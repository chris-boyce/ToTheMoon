// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "FirstPersonPlayerController.generated.h"


class UEnhancedInputComponent;
class APlayerCharacter;
class UInputMappingContext;
class AFirstPersonHUD;

UCLASS(Abstract)
class TOTHEMOON_API AFirstPersonPlayerController : public APlayerController
{

private:
	GENERATED_BODY()
public:
	//Actions For the Player
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputAction> ActionMove;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputAction> ActionLook;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputAction> ActionJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputAction> ActionSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputAction> ActionCrouch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|UI")
	TObjectPtr<UInputAction> ActionCycleUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputAction> ActionInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputAction> ActionFire;

	

	//Input Mapping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;


	UFUNCTION()
	void AllowInput(bool bAllowMove);

	UFUNCTION()
	void MouseVisibility(bool bIsVisable);

	UFUNCTION()
	APlayerCharacter* GetPlayerCharacter();

	
protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleJump();
	void HandleSprint();
	void HandleCrouch();
	void HandleCycleUIMode();
	void HandleInteract();
	void HandleFire();

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter = nullptr;

	UPROPERTY()
	AFirstPersonHUD* PlayerHUD = nullptr;
	
	UPROPERTY()
	bool bPlayerCanMove = true;
	
	
	
};
