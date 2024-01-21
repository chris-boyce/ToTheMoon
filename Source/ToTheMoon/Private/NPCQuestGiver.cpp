// Semester 2 Christopher Boyce : TTM Project


#include "NPCQuestGiver.h"
#include "GoToQuest.h"
#include "QuestBase.h"
#include "TestQuest.h"
#include "Kismet/GameplayStatics.h"
#include "ToTheMoon/PlayerCharacter.h"


ANPCQuestGiver::ANPCQuestGiver()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPCQuestGiver::BeginPlay()
{
	Super::BeginPlay();
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
	PlayerQuestComponent = PlayerCharacter->GetQuestComponent();
	
}

void ANPCQuestGiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPCQuestGiver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCQuestGiver::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello I Got the Message"));
	QuestGive();
	IInteractable::Interact_Implementation();
}

void ANPCQuestGiver::QuestGive()
{
	FCollectionQuest CollectionQuestData;
	FLocationQuest GoToQuestData;
	
	if(PlayerQuestComponent->QuestQueue.IsEmpty())
	{
		UQuestBase* QuestInstance = NewObject<UQuestBase>(this, QuestTypes[0]); //TODO CHANGE THIS BETWEEN QUEST TYPES
		switch (QuestInstance->QuestType)
		{
		case EQuestType::QT_CollectItems:
			
			CollectionQuestData.QuestItem = QuestItem[0]; //TODO FIND A WAY TO ADD THE CLASSES
			CollectionQuestData.ItemCollectionAmount = 1;
			QuestInstance->InitQuestVariables(CollectionQuestData);
			
			break;
			
		case EQuestType::QT_GoTo:
			
			QuestInstance->QuestName = "Waypoint Finder";
			QuestInstance->QuestDescription = "Go To the Waypoint and Stand Under It";
			GoToQuestData.LocationName = "Here";
			QuestInstance->InitQuestVariables(GoToQuestData);
			
			break;
		
			default:
				UE_LOG(LogTemp, Warning, TEXT("Unknown quest type"));
			break;
		}
		
		PlayerQuestComponent->AddQuest(QuestInstance);
		
	}
	
}

