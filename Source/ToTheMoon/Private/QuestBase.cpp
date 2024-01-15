// Semester 2 Christopher Boyce : TTM Project


#include "QuestBase.h"

void UQuestBase::StartQuest()
{
	if (QuestStatus == EQuestStatus::NotStarted)
	{
		QuestStatus = EQuestStatus::InProgress;
		UE_LOG(LogTemp, Warning, TEXT("Quest In Progress"));
	}
}

void UQuestBase::CompleteStep()
{
	UE_LOG(LogTemp, Warning, TEXT("Step Completed"));
	StepCompleted.Broadcast();
}
