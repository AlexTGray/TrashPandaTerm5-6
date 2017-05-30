// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "PlayerHUD.h"
#include "ChipHUDWidget.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	ChipHUDWidget = CreateWidget<UChipHUDWidget>(GetOwningPlayerController(), ChipHUDWidgetClass);
	ChipHUDWidget->AddToPlayerScreen();
}

