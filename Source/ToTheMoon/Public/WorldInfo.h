// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldInfo.generated.h"

UCLASS()
class TOTHEMOON_API AWorldInfo : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldInfo();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="World")
	FString Name;
	UPROPERTY(EditAnywhere, Category="World")
	FString System;
	UPROPERTY(EditAnywhere, Category="World")
	FString Classification;
	
	UPROPERTY(EditAnywhere, Category="Time")
	FString Date;
	UPROPERTY(EditAnywhere, Category="Time")
	FString Time;
	

};
