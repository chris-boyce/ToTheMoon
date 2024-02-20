// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "QuestItemBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitPlayer, UClass*, ObjectClass);

UCLASS()
class TOTHEMOON_API AQuestItemBase : public AActor,  public IInteractable
{
	GENERATED_BODY()
	
public:	
	AQuestItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
	FHitPlayer PlayerHit;
	
	UFUNCTION()
	virtual void Interact_Implementation() override;

	UFUNCTION()
	void SetObject(FString ObjectName);
	
	UFUNCTION()
	void LoadMeshFromFile(const FString& AssetPath);
	
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
	
};
