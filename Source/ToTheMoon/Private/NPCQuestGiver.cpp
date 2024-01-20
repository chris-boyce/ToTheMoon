// Semester 2 Christopher Boyce : TTM Project


#include "NPCQuestGiver.h"

// Sets default values
ANPCQuestGiver::ANPCQuestGiver()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCQuestGiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCQuestGiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCQuestGiver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCQuestGiver::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello I Got the Message"));
	IInteractable::Interact_Implementation();
}

