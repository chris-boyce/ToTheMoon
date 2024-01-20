// Semester 2 Christopher Boyce : TTM Project


#include "PlayerInteractionComponent.h"

#include "Interactable.h"
#include "Kismet/GameplayStatics.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}


void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPlayerInteractionComponent::FireInteraction()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Player controller not found"));
		return;
	}
	
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
	
	FVector RayEnd = CameraLocation + CameraRotation.Vector() * 200.0f;
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	
	ECollisionChannel CollisionChannel = ECC_Pawn;
	CollisionParams.AddIgnoredActor(PlayerController->GetPawn());
	
	if (!GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, RayEnd, CollisionChannel, CollisionParams))
	{
		return;
	}

	AActor* HitActor = HitResult.GetActor();
	if (!HitActor)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Ray hit actor: %s"), *HitActor->GetName());

	if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable* InteractableActor = Cast<IInteractable>(HitActor);
		if (InteractableActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit actor is interactable!"));
			InteractableActor->Execute_Interact(HitActor);
		}
	}

	DrawDebugLine(GetWorld(), CameraLocation, RayEnd, FColor::Red, false, 2.0f, 0, 2.0f);
}

