// Semester 2 Christopher Boyce : TTM Project


#include "QuestBase.h"

void UQuestBase::StartQuest()
{
	if (QuestStatus == EQuestStatus::NotStarted)
	{
		QuestStatus = EQuestStatus::InProgress;
	}
}

void UQuestBase::CompleteStep(int32 StepIndex)
{
	if (QuestStatus == EQuestStatus::InProgress && StepIndex >= 0 && StepIndex < QuestSteps.Num())
	{

	}
}
