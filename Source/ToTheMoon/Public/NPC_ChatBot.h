// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "QuestionData.h"
#include "TopicInfoRelay.h"
#include "GameFramework/Pawn.h"
#include "NPC_ChatBot.generated.h"

class UChatDiologueBase;
class AFirstPersonPlayerController;
class ULlamaComponent;
UCLASS()
class TOTHEMOON_API ANPC_ChatBot : public APawn, public IInteractable
{
	GENERATED_BODY()

public:
	ANPC_ChatBot();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	//Called From the UI of Chat - When a button is pressed
	UFUNCTION()
	void OptionSelected(FString InputString);
	
	//Called From the Llama Component - When a word is Created
	UFUNCTION()
	void GeneratedToken(FString Token);
	
	//Called from when the player interacts with the NPC
	UFUNCTION()
	virtual void Interact_Implementation() override;

	//Called when the Sentence has finished generating - //TODO : Button Appear and disapear
	UFUNCTION()
	void SentenceHasEnded(bool b, float f);

	//Called From the UI of Chat - When the Exit Button is pressed
	UFUNCTION()
	void ExitChat();

	//LlamaComponent is created when interacted due to memory Errors. Deleted and recreated when reinteracting
	UPROPERTY(EditAnywhere)
	TObjectPtr<ULlamaComponent> LlamaComponent;
	
	//String to hold the Text output of the bot
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString BotText;

	//BP Class to Create and once made has to be store to interact with Widgets
	UPROPERTY(EditAnywhere)
	TSubclassOf<UChatDiologueBase> ChatDiologueClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChatDiologueBase> ChatDiologueWidget;

	//This is prompt to set up Bob but can be changed in the Constructor for other NPCs
	UPROPERTY(EditAnywhere)
	FString IntroString = "Intro String";
	
	//This needs to be set or it will cause the first string to be deleted
	UPROPERTY()
	FString FilterQuestion = "TestFilter";

	//Needed to disable the Input of Mouse and Movement
	UPROPERTY()
	AFirstPersonPlayerController* FirstPersonController;

	UPROPERTY(EditAnywhere)
	FString FileName = "Lucy";

	UPROPERTY(VisibleAnywhere)
	FString Name;
	UPROPERTY(VisibleAnywhere)
	FString IntroStringz;
	UPROPERTY(VisibleAnywhere)
	int32 Level;
	UPROPERTY(VisibleAnywhere)
	FString Lore;

	UFUNCTION()
	void TopicSelected(FQuestionTopic Topic);

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTopicInfoRelay* TopicInfoRelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	FString CurrentInformation;

	

	
	

};
