// Semester 2 Christopher Boyce : TTM Project


#include "GPTComponent.h"
#include "EngineUtils.h"
#include "LocationSpawnPoint.h"
#include "OpenAIAPI/Public/OpenAICallChat.h"
#include "OpenAIUtils.h"
#include "QuestBase.h"


UGPTComponent::UGPTComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UGPTComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GPT BEGIN"));
	UOpenAIUtils::setOpenAIApiKey("sk-proj-LgCsZUaUHnQNJP97Snh8T3BlbkFJmQ2ERfGLF9PclxOwrsPc");
	ChatLog[0].content = FinalPromptText();
	ChatLog[0].role = EOAChatRole::SYSTEM;
	ChatSettings.model = EOAChatEngineType::GPT_3_5_TURBO;
	ChatSettings.messages = ChatLog;
	ChatSettings.temperature = 1.0f;
	ChatSettings.maxTokens  = 100;
}


void UGPTComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UGPTComponent::CreateMission()
{
	FChatLog NewChat;
	NewChat.content = "Generate New Mission";
	NewChat.role = EOAChatRole::SYSTEM;
	ChatSettings.messages.Add(NewChat);
	UE_LOG(LogTemp, Warning, TEXT("GPT CALLED"));
	if(!isEnable)
	{
		return;
	}
	
	UOpenAICallChat* OpenAICallChatInstance = UOpenAICallChat::OpenAICallChat(ChatSettings);
	if (OpenAICallChatInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GPT BINDED"));
		OpenAICallChatInstance->Finished.AddDynamic(this, &UGPTComponent::OnReturnedChat);
		OpenAICallChatInstance->Activate();
	}
}

void UGPTComponent::OnReturnedChat(const FChatCompletion ChatCompletion, const FString& ErrorMessage, bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("GPT HAS RETURNED"));
	if(!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("GPT FAILED"));
		return;
	}
	ReturnString = ChatCompletion.message.content;
	StringToJson(ReturnString);
}

FString UGPTComponent::FinalPromptText()
{
	return StartPrompt + GoToPromptText() + CollectPromptText() + KillPromptText() + EndPrompt;
}

FString UGPTComponent::GoToPromptText()
{
	TSubclassOf<ALocationSpawnPoint> LocationPoints = ALocationSpawnPoint::StaticClass();
	TArray<FString> LocationNames;
	for (TActorIterator<ALocationSpawnPoint> ActorItr(GetWorld(), LocationPoints); ActorItr; ++ActorItr)
	{
		ALocationSpawnPoint* LocationPoint = *ActorItr;
		if (LocationPoint)
		{
			LocationNames.Add(LocationPoint->LocationName);
		}
	}

	FString AllLocationNames;
	for (const FString& Name : LocationNames)
	{
		AllLocationNames += Name + TEXT(", ");
	}
	
	return "For 'GoTo' missions, generate a JSON object with 'Location' (options: " + AllLocationNames + ") 'MissionName' and 'MissionDescription'";
}

FString UGPTComponent::CollectPromptText()
{
	return "For 'Collect' missions, generate a JSON object with 'ItemType' (options: 'Rock', 'Key', 'Money') Pick Randomly, 'MissionName', 'MissionDescription', and 'Amount' (ranging from 1 to 10).";
}

FString UGPTComponent::KillPromptText()
{
	return "For 'Kill' missions, generate a JSON object with 'EnemyToKill' (options: 'Alien', 'Pirate') Pick Randomly, 'MissionName', 'MissionDescription', and 'Amount' (ranging from 3 to 10).";
}

void UGPTComponent::StringToJson(FString GPTReturnString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(GPTReturnString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		FString EnumString;
		if (JsonObject->TryGetStringField("MissionType", EnumString))
		{
			if (EnumString.Equals(TEXT("GoTo"), ESearchCase::IgnoreCase))
			{
				QuestType = EQuestType::GoTo;
			}
			else if (EnumString.Equals(TEXT("Collect"), ESearchCase::IgnoreCase))
			{
				QuestType = EQuestType::Collect;
			}
			else if (EnumString.Equals(TEXT("Kill"), ESearchCase::IgnoreCase))
			{
				QuestType = EQuestType::Kill;
			}
		}
		switch (QuestType)
		{
		case EQuestType::GoTo:
			if(JsonObject->TryGetStringField("MissionName", QuestData.MissionName) &&
				JsonObject->TryGetStringField("MissionDescription", QuestData.MissionDescription) &&
				JsonObject->TryGetStringField("Location", QuestData.Location))
			{
				UE_LOG(LogTemp, Warning, TEXT("GOTO JSON COMPLETED"));
				OnQuestDataValid.Broadcast(QuestType, QuestData);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("GOTO JSON FAILED"));
			}
			break;
		case EQuestType::Collect:
			if(JsonObject->TryGetStringField("MissionName", QuestData.MissionName) &&
				JsonObject->TryGetStringField("MissionDescription", QuestData.MissionDescription) &&
				JsonObject->TryGetStringField("ItemType", QuestData.ItemType)&&
				JsonObject->TryGetNumberField("Amount", QuestData.Amount))
			{
				UE_LOG(LogTemp, Warning, TEXT("COLLECT JSON COMPLETED"));
				OnQuestDataValid.Broadcast(QuestType, QuestData);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("COLLECT JSON FAILED"));
			}
			break;
		case EQuestType::Kill:
			if(JsonObject->TryGetStringField("MissionName", QuestData.MissionName) &&
				JsonObject->TryGetStringField("MissionDescription", QuestData.MissionDescription) &&
				JsonObject->TryGetStringField("EnemyToKill", QuestData.EnemyToKill)&&
				JsonObject->TryGetNumberField("Amount", QuestData.Amount))
			{
				UE_LOG(LogTemp, Warning, TEXT("KILL JSON COMPLETED"));
				OnQuestDataValid.Broadcast(QuestType, QuestData);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("KILL JSON FAILED"));
			}
			
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("NO JSON FAILED"));
			;
		}
	}
}

