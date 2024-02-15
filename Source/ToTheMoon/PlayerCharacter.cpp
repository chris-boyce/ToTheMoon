//Semester 2 Christopher Boyce : TTM Project

#include "PlayerCharacter.h"
#include "Gun.h"
#include "PlayerQuestComponent.h"
#include "QuestBase.h"
#include "Components/PointLightComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(0.5f);
	SetActorTickEnabled(true);

	QuestComponent = CreateDefaultSubobject<UPlayerQuestComponent>(TEXT("QuestComponent"));
	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("InteractionComponent"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(GetMovementComponent())
	{
		GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}
	CameraComponent = FindComponentByClass<UCameraComponent>();
	AttachGun();
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float ActualStaminaRegenFactor = StaminaRegenFactor;
	if(bHasJumped)
	{
		ActualStaminaRegenFactor = -JumpStaminaCost;
	}
	else if(bHasRan)
	{
		ActualStaminaRegenFactor = -RunStaminaCost;
	}
	else if(bIsCrouched)
	{
		ActualStaminaRegenFactor = RestStaminaRegen;
	}
	const float PreviousStamina = CurrentStamina;
	CurrentStamina = FMath::Clamp(CurrentStamina + ActualStaminaRegenFactor, 0.f, MaxStamina);
	if(CurrentStamina != PreviousStamina)
	{
		OnStaminaChanged.Broadcast(PreviousStamina, CurrentStamina, MaxStamina);
	}
	bHasRan = false;
	bHasJumped = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::Jump()
{
	if (CurrentStamina - JumpStaminaCost >= 0.f)
	{
		UnCrouch();
		Super::Jump();
		bHasJumped = true;
	}
}

void APlayerCharacter::Crouch(bool bCilentSimulation)
{
	SetRunning(false);
	Super::Crouch(bCilentSimulation);
}

void APlayerCharacter::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	if (bIsRunning && CurrentStamina <= 0)
	{
		SetRunning(false);
	}

	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
	
	if (bIsRunning) bHasRan = true;
}

void APlayerCharacter::BroadcastCurrentStats()
{
	OnHealthChange.Broadcast(CurrentHealth, CurrentHealth, MaxHealth);
	OnStaminaChanged.Broadcast(CurrentStamina, CurrentStamina, MaxStamina);
}

void APlayerCharacter::SetRunning(bool IsRunning)
{
	bIsRunning = IsRunning;
	GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? RunningMaxWalkSpeed : NormalMaxWalkSpeed;
}

void APlayerCharacter::ToggleFlashlight()
{
	if(Flashlight->Intensity > 10)
	{
		Flashlight->SetIntensity(0);
	}
	else
	{
		Flashlight->SetIntensity(1000);
	}
	
}

UPlayerQuestComponent* APlayerCharacter::GetQuestComponent()
{
	return QuestComponent;
}

int APlayerCharacter::GetHealth()
{
	return CurrentHealth;
}

int APlayerCharacter::GetMaxHealth()
{
	return MaxHealth;
}

void APlayerCharacter::UpdateHealth(int DeltaHealth)
{
	//Check For Players Death
	if(CurrentHealth <= 0.f) return;
	
	//Update the Health
	int OldValue = CurrentHealth;
	CurrentHealth += DeltaHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth, -1, MaxHealth);

	//Broadcast Check
	if(CurrentHealth != OldValue)
	{
		OnHealthChange.Broadcast(OldValue, CurrentHealth, MaxHealth);
	}

	//Did the Player Die?
	if(CurrentHealth <= 0)
	{
		OnPlayerDied.Broadcast();
	}
}

void APlayerCharacter::RestoreFullHealth()
{
	CurrentHealth = MaxHealth;
}

void APlayerCharacter::SetMaxHealth(int NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

float APlayerCharacter::GetStamina()
{
	return CurrentStamina;
}

float APlayerCharacter::GetStaminaRegenFactor()
{
	return StaminaRegenFactor;
}

void APlayerCharacter::SetStaminaRegenFactor(float NewStaminaRegenFactor)
{
	StaminaRegenFactor = NewStaminaRegenFactor;
}

void APlayerCharacter::ToggleRunning()
{
	SetRunning(!bIsRunning);
}

void APlayerCharacter::SetHasJumped()
{
	bHasJumped = true;
}

void APlayerCharacter::SetHasRan()
{
	bHasRan = true;
}

void APlayerCharacter::AddKey(FString KeyToAdd)
{
	if(!KeyWallet.Contains(KeyToAdd))
	{
		KeyWallet.Add(KeyToAdd);
	}
}

void APlayerCharacter::RemoveKey(FString KeyToRemove)
{
	if(KeyWallet.Contains(KeyToRemove))
	{
		KeyWallet.Remove(KeyToRemove);
	}
}

bool APlayerCharacter::IsPlayerCarryingKey(FString DesiredKey)
{
	return KeyWallet.Contains(DesiredKey);
}
void APlayerCharacter::AttachGun()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	
	Pistol = GetWorld()->SpawnActor<AGun>(PistolClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	if(Pistol)
	{
		Pistol->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
	
}

