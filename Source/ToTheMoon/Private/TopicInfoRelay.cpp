// Semester 2 Christopher Boyce : TTM Project


#include "TopicInfoRelay.h"

#include "Alien.h"
#include "PlayerQuestComponent.h"
#include "QuestBase.h"
#include "SavedData.h"
#include "Teleporter.h"
#include "WorldInfo.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ToTheMoon/FirstPersonPlayerController.h"
#include "ToTheMoon/PlayerCharacter.h"


UTopicInfoRelay::UTopicInfoRelay()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTopicInfoRelay::BeginPlay()
{
	Super::BeginPlay();
}

void UTopicInfoRelay::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FString UTopicInfoRelay::GatherTopicInfo(FQuestionTopic QuestionTopic)
{
	FString ReturnString = "";
	
	
	switch (QuestionTopic)
	{
	case FQuestionTopic::Null:
		ReturnString = "";
		break;
	case FQuestionTopic::Mission:
		ReturnString = SearchMission();
		break;
	case FQuestionTopic::PlanetInfo:
		 ReturnString =  SearchPlanet();
		break;
	case FQuestionTopic::TimeInfo:
		ReturnString =  SearchTime();
		break;
	case FQuestionTopic::ThreatInfo:
		ReturnString = SearchThreats();
		break;
	case FQuestionTopic::OtherPlanetInfo:
		ReturnString = SearchOtherPlanets();
		break;
	default:
		ReturnString = "";
		;
	}
	return ReturnString;
}

FString UTopicInfoRelay::SearchMission()
{
	UPlayerQuestComponent* QuestComponent = nullptr; 
	UQuestBase** temp = nullptr; 
	UQuestBase* PointerToBase = nullptr;
	QuestComponent = GetWorld()->GetFirstPlayerController<AFirstPersonPlayerController>()->GetPlayerCharacter()->GetQuestComponent();
	temp = QuestComponent->QuestQueue.Peek();
	if(!temp)
	{
		return "<s> The Player Has No Mission </s>";
	}
	PointerToBase = *temp;
	return  "<s> Player Current Mission is" + PointerToBase->QuestName + "</s>";
}

FString UTopicInfoRelay::SearchPlanet()
{
	AWorldInfo* WorldInfo = Cast<AWorldInfo>(UGameplayStatics::GetActorOfClass(GetWorld(), AWorldInfo::StaticClass()));
	return "<s>We are on a " + ASavedData::GetInstance(GetWorld())->Classification  +"Called " + ASavedData::GetInstance(GetWorld())->Name + "In the " + ASavedData::GetInstance(GetWorld())->System + "</s>";
}

FString UTopicInfoRelay::SearchTime()
{
	AWorldInfo* WorldInfo = Cast<AWorldInfo>(UGameplayStatics::GetActorOfClass(GetWorld(), AWorldInfo::StaticClass()));
	return "<s>The date is " + ASavedData::GetInstance(GetWorld())->Date + "and the time is " + ASavedData::GetInstance(GetWorld())->Time + "</s>";
}

FString UTopicInfoRelay::SearchThreats()
{
	FVector CenterPosition = GetOwner()->GetActorLocation();
	float Radius = 10000.0f;
	TArray<AActor*> FoundActors;
	int AmountOfAliens = 0;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAlien::StaticClass(), FoundActors);
	TArray<AActor*> ActorsWithinRadius;
	for (AActor* Actor : FoundActors)
	{
		if (Actor && FVector::Dist(Actor->GetActorLocation(), CenterPosition) <= Radius)
		{
			ActorsWithinRadius.Add(Actor);
			AmountOfAliens++;
		}
	}
	if(ActorsWithinRadius.Num() == 0)
	{
		return "<s>There are no Aliens nearby</s>";
	}
	else
	{
		return "<s> There are " + FString::Printf(TEXT("%d"), ActorsWithinRadius.Num()) + " Aliens </s>";
	}
}

FString UTopicInfoRelay::SearchOtherPlanets()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATeleporter::StaticClass(), FoundActors);
	ATeleporter* Teleporter = Cast<ATeleporter>(FoundActors[0]);
	return "<s> There is a new planet called " + Teleporter->TeleportLocation + "</s>";
}

