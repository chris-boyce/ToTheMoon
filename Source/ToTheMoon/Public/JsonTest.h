// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Json.h"

#include "GameFramework/Actor.h"
#include "JsonTest.generated.h"

UCLASS()
class TOTHEMOON_API AJsonTest : public AActor
{
	GENERATED_BODY()
	
public:	
	AJsonTest();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void JSonReading(FString &JsonString);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TestString;
	  

};
