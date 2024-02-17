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



void ANPCQuestGiver::HandleNewQuestData(EQuestType QuestType, FQuestData QuestData)
{
	UE_LOG(LogTemp, Warning, TEXT("HAS RUN THE HANDLE"));
	if(PlayerQuestComponent->QuestQueue.IsEmpty())
	{
		switch (QuestType)
		{
		case EQuestType::GoTo:
			QuestInstance = NewObject<UGoToQuest>();
			QuestInstance->QuestName = QuestData.MissionName;
			QuestInstance->QuestDescription = QuestData.MissionDescription;
			QuestInstance->QuestType = QuestType;
			LocationQuest.LocationName = QuestData.Location;
			QuestInstance->SetWorldReference(GetWorld());
			QuestInstance->InitQuestVariables(LocationQuest);
			PlayerQuestComponent->AddQuest(QuestInstance);
			break;
		case EQuestType::Collect:
			QuestInstance = NewObject<UTestQuest>();
			QuestInstance->QuestName = QuestData.MissionName;
			QuestInstance->QuestDescription = QuestData.MissionDescription;
			QuestInstance->QuestType = QuestType;
			CollectionQuest.ItemName = QuestData.ItemType;
			CollectionQuest.ItemCollectionAmount = QuestData.Amount;
			QuestInstance->SetWorldReference(GetWorld());
			QuestInstance->InitQuestVariables(CollectionQuest);
			PlayerQuestComponent->AddQuest(QuestInstance);
			break;
		case EQuestType::Kill:
			UE_LOG(LogTemp, Warning, TEXT("KILL NOT COMPLETED"));
			break;
		}
	}
	
	
}

