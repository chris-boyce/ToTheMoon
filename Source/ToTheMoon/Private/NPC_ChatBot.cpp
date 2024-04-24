// Semester 2 Christopher Boyce : TTM Project


#include "NPC_ChatBot.h"

#include "ChatDiologueBase.h"
#include "LlamaComponent.h"
#include "NPCReader.h"
#include "ToTheMoon/FirstPersonPlayerController.h"

ANPC_ChatBot::ANPC_ChatBot()
{
	PrimaryActorTick.bCanEverTick = true;
	TopicInfoRelay = CreateDefaultSubobject<UTopicInfoRelay>(TEXT("TopicInfo"));
}

void ANPC_ChatBot::BeginPlay()
{
	Super::BeginPlay();
	NPCReader Reader;                      
	FNPCData CharacterData = Reader.ReadJSONFile(FileName); 
	
	Name = CharacterData.Name;
	IntroStringz = CharacterData.IntroString;
	Level = CharacterData.Level;
	Lore = CharacterData.Lore;

}

void ANPC_ChatBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC_ChatBot::OptionSelected(FString InputString)
{
	ChatDiologueWidget->ButtonDisable();
	//Sets up the ask question to filter out the inputted Question
	FilterQuestion = InputString;
	if(CurrentInformation != "")
	{
		LlamaComponent->InsertPrompt(CurrentInformation);
	}
	
	LlamaComponent->InsertPrompt(InputString);
	//Box needs to be cleared from the last question
	BotText.Empty();
}

void ANPC_ChatBot::GeneratedToken(FString Token)
{
	UE_LOG(LogTemp, Warning, TEXT("THE TOKEN HAS BEEN GENERATED: %s"), *Token);
	//Adds the Words To The String to Display
	BotText.Append(Token);
	
	//Filters the Worlds
	if (BotText.Contains(IntroStringz) || BotText.Contains(FilterQuestion))
	{
		BotText.Empty();
	}
	
	//Needs to Run on the game thread - Sets the Text Block to the String
	if (IsInGameThread())
	{
		ChatDiologueWidget->SetOutputDialogueText(BotText);
	}
	else
	{
		FText DisplayText = FText::FromString(BotText);
		AsyncTask(ENamedThreads::GameThread, [this, DisplayText]()
		{
			ChatDiologueWidget->SetOutputDialogueText(DisplayText.ToString());
		});
	}
}

void ANPC_ChatBot::Interact_Implementation()
{
	//Creates a Llama Comp if there isnt one and addes the binds to EOS and WordGen + Adds Intro String + Enables it
	if(!LlamaComponent)
	{
		LlamaComponent = NewObject<ULlamaComponent>(this, TEXT("LlamaComp"));
		LlamaComponent->RegisterComponent();
	}
	if (LlamaComponent)
	{
		LlamaComponent->OnEndOfStream.AddDynamic(this, &ANPC_ChatBot::SentenceHasEnded);
		LlamaComponent->OnNewTokenGenerated.AddDynamic(this, &ANPC_ChatBot::GeneratedToken);
		LlamaComponent->ModelParams.Prompt= Lore + IntroStringz;
		LlamaComponent->Activate(false);
		UE_LOG(LogTemp, Warning, TEXT("HELLLO"));
	}
	
	//Gets First Person Comp and disables Movement 
	FirstPersonController = Cast<AFirstPersonPlayerController>(GetWorld()->GetFirstPlayerController());
	if (FirstPersonController)
	{
		FirstPersonController->AllowInput(false);
		FirstPersonController->MouseVisibility(true);
	}
	
	//Makes Chat Window + Adds it to screen + Binds internal event and sets up Arrays + adds callbacks to the NPC
	ChatDiologueWidget = CreateWidget<UChatDiologueBase>(GetWorld(), ChatDiologueClass);
	if (ChatDiologueWidget)
	{
		ChatDiologueWidget->AddToViewport();
		ChatDiologueWidget->MakeArrays();
		ChatDiologueWidget->OnOptionInput.AddDynamic(this, &ANPC_ChatBot::OptionSelected);
		ChatDiologueWidget->OnExitChat.AddDynamic(this, &ANPC_ChatBot::ExitChat);
		ChatDiologueWidget->OnOptionTopicSelected.AddDynamic(this, &ANPC_ChatBot::TopicSelected);
		ChatDiologueWidget->SetName(Name);
	}
	
}

void ANPC_ChatBot::SentenceHasEnded(bool b, float f)
{
	ChatDiologueWidget->ButtonEnable();
}

void ANPC_ChatBot::ExitChat()
{
	//This needs to destroy the LLama Comp so it can Start a new one when interacted //TODO Check if it can carry on - Dont think it does when Deactivated to Activation Limitation of the Plugin <- TLDR Memory Gets all messed up
	LlamaComponent->Deactivate();
	LlamaComponent->DestroyComponent();
	LlamaComponent = nullptr;
	
	//Removes Chat Windows and enables Player Movement	
	ChatDiologueWidget->RemoveFromParent();
	FirstPersonController->AllowInput(true);
	FirstPersonController->MouseVisibility(false);
}

void ANPC_ChatBot::TopicSelected(FQuestionTopic Topic)
{
	CurrentInformation = TopicInfoRelay->GatherTopicInfo(Topic);
}





