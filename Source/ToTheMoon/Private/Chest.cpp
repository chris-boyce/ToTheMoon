// Semester 2 Christopher Boyce : TTM Project


#include "Chest.h"

AChest::AChest()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AChest::BeginPlay()
{
	
	
}

void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChest::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
	USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	Super::BeginPlay();
	if (OpenAnimation != nullptr && SkeletalMeshComponent)
	{
		SkeletalMeshComponent->PlayAnimation(OpenAnimation, false);
	}
}

