// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "PlayerInteractionComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class AGun;
class UPlayerQuestComponent;
UENUM(BlueprintType)
enum class EPlayerKeyAction : uint8
{
	AddKey, RemoveKey, TestKey
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIntStatUpdate, int32, OldValue, int32, NewValue, int32, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerIsDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFloatStatUpdate, float, OldValue, float, NewValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FKeyWalletAction, FString, KeyString, EPlayerKeyAction, KeyAction, bool, IsSuccess);

UCLASS()
class TOTHEMOON_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	virtual void Crouch(bool bCilentSimulation = false) override;

	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false) override;

	UFUNCTION()
	void AttachGun();

	UFUNCTION(BlueprintCallable,Category="Player|Stats")
	void BroadcastCurrentStats();
	
	//Health Functions
	UFUNCTION(BlueprintPure, Category="Player|Health")
	int GetHealth();

	UFUNCTION(BlueprintPure, Category="Player|Health")
	int GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category="Player|Health")
	void UpdateHealth(int DeltaHealth);

	UFUNCTION(BlueprintCallable, Category="Player|Health")
	void RestoreFullHealth();
	
	UFUNCTION(BlueprintCallable, Category="Player|Health")
	void SetMaxHealth(int NewMaxHealth);

	//Stamina Functions
	UFUNCTION(BlueprintPure, Category="Player|Stamina")
	float GetStamina();

	UFUNCTION(BlueprintPure, Category="Player|Stamina")
	float GetStaminaRegenFactor();

	UFUNCTION(BlueprintCallable, Category="Player|Stamina")
	void SetStaminaRegenFactor(float NewStaminaRegenFactor);
	
	//Keys Functions
	UFUNCTION(BlueprintCallable, Category="Player|Keys")
	void AddKey(FString KeyToAdd);

	UFUNCTION(BlueprintCallable, Category="Player|Keys")
	void RemoveKey(FString KeyToRemove);

	UFUNCTION(BlueprintPure, Category="Player|Keys")
	bool IsPlayerCarryingKey(FString DesiredKey);

	//Delegates
	UPROPERTY(BlueprintAssignable, Category="Player|Health")
	FIntStatUpdate OnHealthChange;

	UPROPERTY(BlueprintAssignable, Category="Player|Health")
	FPlayerIsDead OnPlayerDied;

	UPROPERTY(BlueprintAssignable, Category="Player|Stamina")
	FFloatStatUpdate OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category="Player|Keys")
	FKeyWalletAction OnKeyWalletAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement", meta = (AllowPrivateAccess = "true"))
	float NormalMaxWalkSpeed = 400.0f;

	// The sprinting speed of the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Movement", meta = (AllowPrivateAccess = "true"))
	float RunningMaxWalkSpeed = 800.0f;

	UFUNCTION(BlueprintCallable, Category="Player|Movement")
	void ToggleRunning();

	// Called to set the flag indicating the player jumped since the last update.
	UFUNCTION(BlueprintCallable, Category="Player|Movement")
	void SetHasJumped();

	// Called to se the flag indicating the player sprinted since the last update.
	UFUNCTION(BlueprintCallable, Category="Player|Movement")
	void SetHasRan();

	UFUNCTION(BlueprintCallable, Category="Player|Movement")
	void SetRunning(bool IsRunning);

	UFUNCTION(BlueprintCallable, Category="Player|Flashlight")
	void ToggleFlashlight();


	
	//Components --------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Components")
	UPlayerQuestComponent* QuestComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Components")
	TSubclassOf<AGun> PistolClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Components")
	AGun* Pistol = nullptr;
	
	UFUNCTION()
	UPlayerQuestComponent* GetQuestComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player|Components")
	UPlayerInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player|Flashlight")
	UPointLightComponent* Flashlight;

	

private:
	//Health
	static constexpr int BaseHealth = 100;
	int MaxHealth = BaseHealth;
	int CurrentHealth = BaseHealth;

	//Stamina
	static constexpr float  MaxStamina = 200;
	static constexpr float JumpStaminaCost = 10;
	static constexpr float RunStaminaCost = 5;
	static constexpr float RestStaminaRegen = 5;
	float CurrentStamina = MaxStamina;
	float StaminaRegenFactor = 1;

	bool bIsRunning = false;
	bool bHasRan = false;
	bool bHasJumped = false;

	//Player Key
	TArray<FString> KeyWallet;

};
