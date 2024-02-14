// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "QuestionData.h"
#include "WidgetBase.h"
#include "ChatDiologueBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitChat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOptionInputRecived, FString, InputString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOptionTopicSelected, FQuestionTopic, InputTopic);

class UVerticalBox;
class UEditableTextBox;
class UButton;
class UTextBlock;
//Struct the hold the Button Textblock and the string that will be passed to the bot when pressed
USTRUCT()
struct FOptions
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<UButton> OptionButton = nullptr;

	UPROPERTY()
	TObjectPtr<UTextBlock> OptionTextBlock = nullptr;

	UPROPERTY()
	FString OptionString;

	FOptions(TObjectPtr<UButton> InOptionButton, TObjectPtr<UTextBlock> InOptionTextBlock, const FString& InOptionString): OptionButton(InOptionButton), OptionTextBlock(InOptionTextBlock), OptionString(InOptionString){}
	FOptions() : OptionButton(nullptr), OptionTextBlock(nullptr), OptionString(TEXT("")){}
};

USTRUCT()
struct FOptionText
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString ShownText;

	UPROPERTY()
	FString InsertedText;
};


UCLASS()
class TOTHEMOON_API UChatDiologueBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UTextBlock> OutputDialogue = nullptr;

	//A array of the all the options button, textblocks and strings <- Access this way
	UPROPERTY()
	TArray<FOptions> Options;

	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	UButton* ExitButton = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	UButton* DynamicTextInsertButton = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UVerticalBox> ButtonBox = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UEditableTextBox> TextEntry = nullptr;

	
	//This are the bind widgets before being added to the array ----Don't Access this -------
	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UButton> OptionOneButton = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UButton> OptionTwoButton = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UButton> OptionThreeButton = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UTextBlock> OptionOne = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UTextBlock> OptionTwo = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UTextBlock> OptionThree = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="AIInteraction", meta=(BindWidget))
	TObjectPtr<UTextBlock> Name = nullptr;

	UPROPERTY()
	TArray<FString> OptionString;

	UPROPERTY()
	TArray<FString> OptionInputString;

	UPROPERTY()
	TArray<FQuestionTopic> OptionTopics;
	
	//Delegates that will get called on the NPC when an action is done
	FOnExitChat OnExitChat;
	FOptionInputRecived OnOptionInput;
	FOptionTopicSelected OnOptionTopicSelected;

	//Functions to change the output dialogue box so nothing can access it
	UFUNCTION()
	void SetOutputDialogueText(FString InputText);

	//TODO - Get it so it changes the options atm just uses presets
	UFUNCTION()
	void UpdateOptions();
	
	UFUNCTION()
	void ExitChat();

	//Used to Convert Text <- Easier that the lines of Code
	UFUNCTION()
	FText StringToText(FString InputString);

	//Creates Arrays and Binds Delegates
	UFUNCTION()
	void MakeArrays();

	//Functions For Each Button being Clicked
	UFUNCTION()
	void OptionOneClicked();

	UFUNCTION()
	void OptionTwoClicked();

	UFUNCTION()
	void OptionThreeClicked();

	UFUNCTION()
	void ButtonDisable();

	UFUNCTION()
	void ButtonEnable();

	UFUNCTION()
	void DynamicTextInsert();

	UPROPERTY(EditAnywhere)
	UDataTable* QuestionDataTable;
	
	UPROPERTY(EditAnywhere)
	TArray<FQuestions> Questions;

	UFUNCTION()
	void WriteDataTableToArray();

	UFUNCTION()
	void RandomizeButtons();

	TArray<int32> RandomNumbers;

	UFUNCTION()
	void SetName(FString InputName);

	
};
