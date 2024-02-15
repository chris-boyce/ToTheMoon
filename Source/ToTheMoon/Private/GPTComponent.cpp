// Semester 2 Christopher Boyce : TTM Project


#include "GPTComponent.h"
#include "OpenAIAPI/Public/OpenAICallChat.h"
#include "OpenAIUtils.h"


UGPTComponent::UGPTComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGPTComponent::BeginPlay()
{
	Super::BeginPlay();
	CreateMission();
	UE_LOG(LogTemp, Warning, TEXT("GPT BEGIN"));
	
}


void UGPTComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UGPTComponent::CreateMission()
{
	UOpenAIUtils::setOpenAIApiKey("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");
	FChatSettings ChatSettings;
	ChatSettings.model = EOAChatEngineType::GPT_3_5_TURBO;
	ChatSettings.messages = ChatLog;
	ChatSettings.temperature = 1.0f;
	ChatSettings.maxTokens  = 100;
	UE_LOG(LogTemp, Warning, TEXT("GPT CALLED"));
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
}

