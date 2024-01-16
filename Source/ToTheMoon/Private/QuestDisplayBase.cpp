// Semester 2 Christopher Boyce : TTM Project


#include "QuestDisplayBase.h"
#include "Components/TextBlock.h"


void UQuestDisplayBase::UpdateQuestWidget(FString mQuestName, FString mQuestDescription, int mCurrentScore, int mFinalScore)
{
	QuestName->SetText(FText::FromString(mQuestName));
	QuestDescription->SetText(FText::FromString(mQuestDescription));
	
	FText CurrentScoreText = FText::AsNumber(mCurrentScore);
	FText FinalScoreText = FText::AsNumber(mFinalScore);
	FText ConcatenatedText = FText::Format(FText::FromString("{0}/{1}"), CurrentScoreText, FinalScoreText);
	StatsDescription->SetText(ConcatenatedText);
	
}

void UQuestDisplayBase::UpdateQuest()
{
	UE_LOG(LogTemp, Warning, TEXT("BIND HAS WORKED"));
}
