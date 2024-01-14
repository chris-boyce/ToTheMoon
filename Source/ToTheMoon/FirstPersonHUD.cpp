// Semester 2 Christopher Boyce : TTM Project


#include "FirstPersonHUD.h"

void AFirstPersonHUD::CycleToNextViewMode()
{
	++CurrentViewMode;
	UE_LOG(LogTemp, Warning, TEXT("CycleToNextViewMode %s"), *UEnum::GetValueAsString(CurrentViewMode));
	//UpdateWidget();
}
