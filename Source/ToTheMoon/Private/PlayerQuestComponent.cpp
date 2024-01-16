// Semester 2 Christopher Boyce : TTM Project


#include "PlayerQuestComponent.h"
#include "QuestBase.h"
#include "QuestDisplayBase.h"

UPlayerQuestComponent::UPlayerQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	///THIS IS FOR TESTING
	for (int32 Index = 0; Index < TESTQUEUE.Num(); ++Index)
	{
		QuestQueue.Enqueue(TESTQUEUE[Index]);
		UE_LOG(LogTemp, Warning, TEXT("Added To Que"));
	}
	/// - - - - - - - - - - - -
	if(QuestQueue.Peek())
	{
		UQuestBase* FirstQuestInstance = NewObject<UQuestBase>(this, QuestQueue.Peek()->Get());
		FirstQuestInstance->StartQuest();
		FirstQuestInstance->StepCompleted.AddDynamic(this, &UPlayerQuestComponent::HandleStepCompleted);
		UE_LOG(LogTemp, Warning, TEXT("Quest Started"));
		FUpdateDisplay.Broadcast(FirstQuestInstance->QuestName, FirstQuestInstance->QuestDescription , 0 ,0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Quest Queued"));
		FString NoMissionName = "No Mission";
		FString NoMissionDescription = "Find A Mission";
		FUpdateDisplay.Broadcast(NoMissionName, NoMissionDescription, 0 , 0 );
	}
	
	FUpdateQuest.Broadcast();
	
	
}

void UPlayerQuestComponent::HandleStepCompleted()
{
	QuestQueue.Pop();
	if(QuestQueue.Peek())
	{
		UQuestBase* FirstQuestInstance = NewObject<UQuestBase>(this, QuestQueue.Peek()->Get());
		FirstQuestInstance->StartQuest();
		FirstQuestInstance->StepCompleted.AddDynamic(this, &UPlayerQuestComponent::HandleStepCompleted);
		UE_LOG(LogTemp, Warning, TEXT("Next Quest"));
		FUpdateDisplay.Broadcast(FirstQuestInstance->QuestName, FirstQuestInstance->QuestDescription , 0 ,0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Quest"));
		
		UE_LOG(LogTemp, Warning, TEXT("No Quest Queued"));
		FString NoMissionName = "No Mission";
		FString NoMissionDescription = "Find A Mission";
		FUpdateDisplay.Broadcast(NoMissionName, NoMissionDescription, 0 , 0 );
	}
	
}

void UPlayerQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

