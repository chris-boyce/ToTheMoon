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

	//Input Mapping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="First Person Player|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;



	
protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleJump();
	void HandleSprint();
	void HandleCrouch();

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter = nullptr;
	
	
};
