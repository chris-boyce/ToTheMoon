// Semester 2 Christopher Boyce : TTM Project
#include "ChatDiologueBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/EditableTextBox.h"

void UChatDiologueBase::SetOutputDialogueText(FString InputText)
{
	FText DisplayText = FText::FromString(InputText);
	OutputDialogue->SetText(DisplayText);
	UpdateOptions();
}

void UChatDiologueBase::UpdateOptions()
{
	Options[0].OptionTextBlock->SetText(StringToText(Options[0].OptionString));
	Options[1].OptionTextBlock->SetText(StringToText(Options[1].OptionString));
	Options[2].OptionTextBlock->SetText(StringToText(Options[2].OptionString));
}

void UChatDiologueBase::ExitChat()
{
	OnExitChat.Broadcast();
}

FText UChatDiologueBase::StringToText(FString InputString)
{
	return FText::FromString(InputString);
}

void UChatDiologueBase::MakeArrays()
{
	WriteDataTableToArray();
	RandomizeButtons();
	
	Options.Add(FOptions{OptionOneButton, OptionOne, OptionString[0]});
	Options.Add(FOptions{OptionTwoButton, OptionTwo, OptionString[1]});
	Options.Add(FOptions{OptionThreeButton, OptionThree, OptionString[2]});
	ExitButton->OnClicked.AddDynamic(this, &UChatDiologueBase::ExitChat);
	
	UE_LOG(LogTemp, Warning, TEXT("BOUND BUTTONS"));
	Options[0].OptionButton->OnClicked.AddDynamic(this, &UChatDiologueBase::OptionOneClicked);
	Options[1].OptionButton->OnClicked.AddDynamic(this, &UChatDiologueBase::OptionTwoClicked);
	Options[2].OptionButton->OnClicked.AddDynamic(this, &UChatDiologueBase::OptionThreeClicked);
	DynamicTextInsertButton->OnClicked.AddDynamic(this, &UChatDiologueBase::DynamicTextInsert);
	
	//ButtonDisable();
}


void UChatDiologueBase::OptionOneClicked()
{
	FText LoadingText = FText::FromString("Loading");
	OutputDialogue->SetText(LoadingText);
	OnOptionTopicSelected.Broadcast(OptionTopics[0]);
	OnOptionInput.Broadcast(OptionInputString[0]);
}

void UChatDiologueBase::OptionTwoClicked()
{
	FText LoadingText = FText::FromString("Loading");
	OutputDialogue->SetText(LoadingText);
	OnOptionTopicSelected.Broadcast(OptionTopics[1]);
	OnOptionInput.Broadcast(OptionInputString[1]);
}

void UChatDiologueBase::OptionThreeClicked()
{
	FText LoadingText = FText::FromString("Loading");
	OutputDialogue->SetText(LoadingText);
	OnOptionTopicSelected.Broadcast(OptionTopics[2]);
	OnOptionInput.Broadcast(OptionInputString[2]);
}

void UChatDiologueBase::ButtonDisable()
{
	ButtonBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UChatDiologueBase::ButtonEnable()
{
	if (IsInGameThread())
	{
		ButtonBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UVerticalBox* LocalButtonBox = ButtonBox; 
		AsyncTask(ENamedThreads::GameThread, [LocalButtonBox]()
		{
			if (LocalButtonBox)
			{
				LocalButtonBox->SetVisibility(ESlateVisibility::Visible);
			}
		});
	}
	
}

void UChatDiologueBase::DynamicTextInsert()
{
	FString InputText =  TextEntry->GetText().ToString();
	if(!InputText.IsEmpty())
	{
		FString stringToAddAtStart = TEXT("<s>Respond in less than 10 Words. ");
		FString stringToAddAtEnd = TEXT("  </s>");
		FString FinText = stringToAddAtStart + InputText;
		FinText += stringToAddAtEnd;
		OnOptionInput.Broadcast(FinText);
	}
	
}

void UChatDiologueBase::WriteDataTableToArray()
{
	for (int32 i = 1; i <= 13; ++i)
	{
		FName RowName = FName(*FString::FromInt(i));
		FQuestions* Data = QuestionDataTable->FindRow<FQuestions>(RowName, FString());
		if (Data)
		{
			Questions.Add(*Data);
		}
	}
}

void UChatDiologueBase::RandomizeButtons()
{
	RandomNumbers.Empty();
	while (RandomNumbers.Num() < 3)
	{
		int32 RandomNumber = FMath::RandRange(0, 12);
		
		if (!RandomNumbers.Contains(RandomNumber))
		{
			RandomNumbers.Add(RandomNumber);
		}
	}
	for (int32 i = 0; i < RandomNumbers.Num(); ++i)
	{
		UE_LOG(LogTemp, Log, TEXT("Random number %d: %d"), i , RandomNumbers[i]);
		OptionString.Add(Questions[RandomNumbers[i]].DisplayQuestion);
		OptionInputString.Add(Questions[RandomNumbers[i]].InputQuestion);
		OptionTopics.Add((Questions[RandomNumbers[i]].Topic));
	}
}

void UChatDiologueBase::SetName(FString InputName)
{
	Name->SetText(StringToText(InputName)); 
}




