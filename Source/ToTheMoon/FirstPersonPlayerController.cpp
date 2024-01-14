// Semester 2 Christopher Boyce : TTM Project


#include "FirstPersonPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FirstPersonHUD.h"
#include "PlayerCharacter.h"

void AFirstPersonPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	PlayerCharacter = Cast<APlayerCharacter>(aPawn);
	checkf(PlayerCharacter, TEXT("Player Character Not Set"));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("No Enhanced Input Component"));

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Subsystem Not Setup"));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	

	if(ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleMove);
	}
	if(ActionLook)
	{
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleLook);
	}
	if(ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleJump);
	}
	if(ActionCrouch)
	{
		EnhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleCrouch);
	}
	if(ActionSprint)
	{
		EnhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleSprint);
	}
	if(ActionCycleUI)
	{
		EnhancedInputComponent->BindAction(ActionCycleUI, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleCycleUIMode);
	}
}

void AFirstPersonPlayerController::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();
	Super::OnUnPossess();
}

void AFirstPersonPlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void AFirstPersonPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void AFirstPersonPlayerController::HandleJump()
{
	if(PlayerCharacter)
	{
		PlayerCharacter->UnCrouch();
		PlayerCharacter->Jump();
	}
}

void AFirstPersonPlayerController::HandleSprint()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->ToggleRunning();
	}
}

void AFirstPersonPlayerController::HandleCrouch()
{
	if(PlayerCharacter && PlayerCharacter->bIsCrouched)
	{
		PlayerCharacter->UnCrouch();
	}
	else
	{
		PlayerCharacter->Crouch();
	}
}

void AFirstPersonPlayerController::HandleCycleUIMode()
{
	if(PlayerHUD)
	{
		PlayerHUD->CycleToNextViewMode();
	}
}
