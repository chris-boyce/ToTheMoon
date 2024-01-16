// Semester 2 Christopher Boyce : TTM Project


#include "FirstPersonHUD.h"

#include "HealthStaminaBarBase.h"
#include "MinimalLayoutBase.h"
#include "ModerateLayoutBase.h"
#include "OverloadLayoutBase.h"
#include "PlayerCharacter.h"
#include "PlayerQuestComponent.h"
#include "StatBarBase.h"


void AFirstPersonHUD::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	checkf(World, TEXT("World Not Found"));
	
	checkf(MinimalLayoutClass, TEXT("No Min Class"));
	checkf(ModerateLayoutClass, TEXT("No Mod"));
	checkf(OverloadLayoutClass, TEXT("No Overload"));

	MinimalLayoutWidget = CreateWidget<UMinimalLayoutBase>(World, MinimalLayoutClass);
	MinimalLayoutWidget->AddToViewport();
	MinimalLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	ModerateLayoutWidget = CreateWidget<UModerateLayoutBase>(World, ModerateLayoutClass);
	ModerateLayoutWidget->AddToViewport();
	ModerateLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	OverloadLayoutWidget = CreateWidget<UOverloadLayoutBase>(World, OverloadLayoutClass);
	OverloadLayoutWidget->AddToViewport();
	OverloadLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	if (APlayerController* PlayerController = GetOwningPlayerController())
	{
		PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn());
		UPlayerQuestComponent* PlayerQuestComponent = PlayerCharacter->FindComponentByClass<UPlayerQuestComponent>();
		if(PlayerQuestComponent)
		{
			//QUEST BINDS TO THE QUEST UI IS HERE !!!!
			PlayerQuestComponent->FUpdateDisplay.AddDynamic(ModerateLayoutWidget->QuestDisplayBase, &UQuestDisplayBase::UpdateQuestWidget);
			PlayerQuestComponent->FUpdateDisplay.AddDynamic(OverloadLayoutWidget->QuestDisplayBase, &UQuestDisplayBase::UpdateQuestWidget);
		}
		
	}
	
	checkf(PlayerCharacter, TEXT("Unable to get a reference to the player character"));

	UpdateWidgets();
}

void AFirstPersonHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearAllHandlers();
	Super::EndPlay(EndPlayReason);
}

void AFirstPersonHUD::SetCurrentViewMode(EHudViewMode NewViewMode)
{
	CurrentViewMode = NewViewMode;
	UpdateWidgets();
}

void AFirstPersonHUD::CycleToNextViewMode()
{
	++CurrentViewMode;
	UE_LOG(LogTemp, Warning, TEXT("CycleToNextViewMode %s"), *UEnum::GetValueAsString(CurrentViewMode));
	UpdateWidgets();
}

void AFirstPersonHUD::UpdateWidgets()
{
	// Unhook any delegate handlers.
	ClearAllHandlers();

	// Set all the widgets so we see none of them
	MinimalLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);
	ModerateLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);
	OverloadLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	switch (CurrentViewMode)
	{
	case EHudViewMode::CleanAndPristine:
		// Currently there isn't actually anything to do here!
		break;
	case EHudViewMode::Minimal:
		PlayerCharacter->OnHealthChange.AddDynamic(MinimalLayoutWidget->HealthStaminaBar->HealthBar, &UStatBarBase::OnIntStatUpdated);
		PlayerCharacter->OnStaminaChanged.AddDynamic(MinimalLayoutWidget->HealthStaminaBar->StaminaBar, &UStatBarBase::OnFloatStatUpdated);
		MinimalLayoutWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EHudViewMode::Moderate:
		PlayerCharacter->OnHealthChange.AddDynamic(ModerateLayoutWidget->HealthStaminaBar->HealthBar, &UStatBarBase::OnIntStatUpdated);
		PlayerCharacter->OnStaminaChanged.AddDynamic(ModerateLayoutWidget->HealthStaminaBar->StaminaBar, &UStatBarBase::OnFloatStatUpdated);
		ModerateLayoutWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EHudViewMode::SensoryOverload:
		PlayerCharacter->OnHealthChange.AddDynamic(OverloadLayoutWidget->HealthStaminaBar->HealthBar, &UStatBarBase::OnIntStatUpdated);
		PlayerCharacter->OnStaminaChanged.AddDynamic(OverloadLayoutWidget->HealthStaminaBar->StaminaBar, &UStatBarBase::OnFloatStatUpdated);
		OverloadLayoutWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	default: ;
	}

	// This ensures that even if something has not changed recently, the newly switched-to widget will get sent
	// the latest character stats, so it can update itself.
	ToggleIsVisableWidget();
	PlayerCharacter->BroadcastCurrentStats();
}

void AFirstPersonHUD::ClearAllHandlers()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->OnHealthChange.Clear();
		PlayerCharacter->OnStaminaChanged.Clear();
		PlayerCharacter->OnKeyWalletAction.Clear();
	}
	
}

void AFirstPersonHUD::ToggleIsVisableWidget()
{
	if(OverloadLayoutWidget)
	{
		OverloadLayoutWidget->VisibilityToggle();
	}
}
