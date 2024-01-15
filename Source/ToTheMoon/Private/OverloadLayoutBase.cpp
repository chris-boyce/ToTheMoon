// Semester 2 Christopher Boyce : TTM Project


#include "OverloadLayoutBase.h"

#include "FPSCounterBase.h"

void UOverloadLayoutBase::VisibilityToggle()
{
	if (IsVisible())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOverloadLayoutBase::UpdateWidget, 1.f, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}


void UOverloadLayoutBase::UpdateWidget()
{
	UGameViewportClient* ViewportClient = GEngine->GameViewport;

	if (ViewportClient)
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		float FPS = 1.0f / DeltaTime;
		FString FPSText = FString::Printf(TEXT("FPS: %.2f"), FPS);
		FPSCounterWidget->UpdateWidget(FPSText);
	}
}
