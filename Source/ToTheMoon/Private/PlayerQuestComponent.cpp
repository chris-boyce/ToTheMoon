// Semester 2 Christopher Boyce : TTM Project


#include "PlayerQuestComponent.h"
#include "QuestBase.h"

UPlayerQuestComponent::UPlayerQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	for (int32 Index = 0; Index < TESTQUEUE.Num(); ++Index)
	{
		QuestQueue.Enqueue(TESTQUEUE[Index]);
		UE_LOG(LogTemp, Warning, TEXT("Added To Que"));
	}

	
	if(QuestQueue.Peek())
	{
		UQuestBase* FirstQuestInstance = NewObject<UQuestBase>(this, QuestQueue.Peek()->Get());
		FirstQuestInstance->StartQuest();
		FirstQuestInstance->StepCompleted.AddDynamic(this, &UPlayerQuestComponent::HandleStepCompleted);
		UE_LOG(LogTemp, Warning, TEXT("Quest Started"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Quest Queued"));
	}
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
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Quest"));
	}
}

void UPlayerQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

