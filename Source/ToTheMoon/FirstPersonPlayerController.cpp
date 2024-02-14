// Semester 2 Christopher Boyce : TTM Project


#include "FirstPersonPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FirstPersonHUD.h"
#include "Gun.h"
#include "PlayerCharacter.h"

void AFirstPersonPlayerController::AllowInput(bool bAllowMove)
{
	bPlayerCanMove = bAllowMove;
}

void AFirstPersonPlayerController::MouseVisibility(bool bIsVisable)
{
	if (bIsVisable)
	{
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

APlayerCharacter* AFirstPersonPlayerController::GetPlayerCharacter()
{
	return PlayerCharacter;
}

void AFirstPersonPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	PlayerCharacter = Cast<APlayerCharacter>(aPawn);
	checkf(PlayerCharacter, TEXT("Player Character Not Set"));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("No Enhanced Input Component"));

	PlayerHUD = Cast<AFirstPersonHUD>(GetHUD());
	checkf(PlayerHUD, TEXT("Unable to get reference to the HUD"));
	

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
	if(ActionInteract)
	{
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleInteract);
	}
	if(ActionFire)
	{
		EnhancedInputComponent->BindAction(ActionFire, ETriggerEvent::Triggered, this, &AFirstPersonPlayerController::HandleFire);
	}
	
}

void AFirstPersonPlayerController::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();
	Super::OnUnPossess();
}

void AFirstPersonPlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	if(!bPlayerCanMove)
	{
		return;
	}
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void AFirstPersonPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	if(!bPlayerCanMove)
	{
		return;
	}
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void AFirstPersonPlayerController::HandleJump()
{
	if(!bPlayerCanMove)
	{
		return;
	}
	if(!bPlayerCanMove)
	{
		return;
	}
	if(PlayerCharacter)
	{
		PlayerCharacter->UnCrouch();
		PlayerCharacter->Jump();
	}
}

void AFirstPersonPlayerController::HandleSprint()
{
	if(!bPlayerCanMove)
	{
		return;
	}
	if (PlayerCharacter)
	{
		PlayerCharacter->ToggleRunning();
	}
}

void AFirstPersonPlayerController::HandleCrouch()
{
	if(!bPlayerCanMove)
	{
		return;
	}
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
	if(!bPlayerCanMove)
	{
		return;
	}
	if(PlayerHUD)
	{
		PlayerHUD->CycleToNextViewMode();
	}
}

void AFirstPersonPlayerController::HandleInteract()
{
	if(!bPlayerCanMove)
	{
		return;
	}
	if(PlayerCharacter)
	{
		PlayerCharacter->InteractionComponent->FireInteraction();
	}
}

void AFirstPersonPlayerController::HandleFire()
{
	if(!bPlayerCanMove)
	{
		return;
	}
	if(PlayerCharacter->Pistol)
	{
		PlayerCharacter->Pistol->Fire();
	}
	
}
