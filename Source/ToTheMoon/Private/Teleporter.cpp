// Semester 2 Christopher Boyce : TTM Project


#include "Teleporter.h"

#include "Kismet/GameplayStatics.h"
#include "ToTheMoon/PlayerCharacter.h"

ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("PORTAL COLL"));
	if (OtherActor && OtherActor != this)
	{
		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
		{
			UGameplayStatics::OpenLevel(GetWorld(), *TeleportLocation);
		}
	}
	
}


