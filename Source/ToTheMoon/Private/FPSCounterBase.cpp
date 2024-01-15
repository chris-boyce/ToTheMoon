// Semester 2 Christopher Boyce : TTM Project


#include "FPSCounterBase.h"

#include "Components/TextBlock.h"


void UFPSCounterBase::UpdateWidget(FString FPSString)
{
	UE_LOG(LogTemp, Warning, TEXT("FPS Has Run"));
	if(FPSCounter)
	{
		FText MyText = FText::FromString(FPSString);
		FPSCounter->SetText(MyText);
	}
}
