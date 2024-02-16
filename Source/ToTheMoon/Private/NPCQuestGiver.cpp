// Semester 2 Christopher Boyce : TTM Project


#include "NPCQuestGiver.h"
#include "GoToQuest.h"
#include "GPTComponent.h"
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
	GPTComp = FindComponentByClass<UGPTComponent>();
	GPTComp->OnQuestDataValid.AddDynamic(this, &ANPCQuestGiver::HandleNewQuestData);
	
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
	GPTComp->CreateMission();
	IInteractable::Interact_Implementation();
}

void ANPCQuestGiver::QuestGive()
{
	/*
	UQuestBase* QuestInstance = NewObject<UQuestBase>(this, QuestTypes[0]); //TODO CHANGE THIS BETWEEN QUEST TYPES
	switch (QuestInstance->QuestType)
	{
	case EQuestType::Collect:
			
		CollectionQuestData.QuestItem = QuestItem[0]; //TODO FIND A WAY TO ADD THE CLASSES
		CollectionQuestData.ItemCollectionAmount = 1;
		QuestInstance->InitQuestVariables(CollectionQuestData);
			
		break;
			
	case EQuestType::GoTo:
			
		QuestInstance->QuestName = "Waypoint Finder";
		QuestInstance->QuestDescription = "Go To the Waypoint and Stand Under It";
		GoToQuestData.LocationName = "Here";
		QuestInstance->InitQuestVariables(GoToQuestData);
			
		break;
		
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown quest type"));
		break;
	}
	*/
	
}

void ANPCQuestGiver::HandleNewQuestData(EQuestType QuestType, FQuestData QuestData)
{
	UE_LOG(LogTemp, Warning, TEXT("HAS RUN THE HANDLE"));
	UQuestBase* QuestInstance = NewObject<UQuestBase>();
	FLocationQuest LocationQuest;
	switch (QuestType)
	{
	case EQuestType::GoTo:
		
		QuestInstance->QuestName = QuestData.MissionName;
		QuestInstance->QuestDescription = QuestData.MissionDescription;
		QuestInstance->QuestType = QuestType;
		
		LocationQuest.LocationName = QuestData.Location;
		QuestInstance->InitQuestVariables(LocationQuest);
		
		break;
	case EQuestType::Collect:
		UE_LOG(LogTemp, Warning, TEXT("COLLECT NOT COMPLETED"));
		break;
	case EQuestType::Kill:
		UE_LOG(LogTemp, Warning, TEXT("KILL NOT COMPLETED"));
		break;
	}
	PlayerQuestComponent->AddQuest(QuestInstance);
}

