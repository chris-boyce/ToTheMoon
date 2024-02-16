// Semester 2 Christopher Boyce : TTM Project


#include "LocationBase.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"




ALocationBase::ALocationBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	UBoxComponent* BoxCollider;

	// Initialize the BoxCollider and attach it to the PaperSpriteComponent
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f)); 
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
	BoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap); 
	BoxCollider->SetGenerateOverlapEvents(true); 
	RootComponent = BoxCollider;

	
	
}

// Called when the game starts or when spawned
void ALocationBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Alive"));
	Super::BeginPlay();
	
	
}

void ALocationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocationBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayerOverlap.Broadcast();
	//Destroy();
}



