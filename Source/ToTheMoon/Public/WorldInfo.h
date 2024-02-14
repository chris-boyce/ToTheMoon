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
	FString Name = "Name";
	UPROPERTY(EditAnywhere, Category="World")
	FString System = "System";
	UPROPERTY(EditAnywhere, Category="World")
	FString Classification = "Classic";
	
	UPROPERTY(EditAnywhere, Category="Time")
	FString Date = "01/01/2001";
	UPROPERTY(EditAnywhere, Category="Time")
	FString Time = "12:00";
	

};
