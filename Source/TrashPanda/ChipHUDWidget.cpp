// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "ChipHUDWidget.h"
#include "Chip.h"

void UChipHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


float UChipHUDWidget::GetPlayerHealth() const
{
	if (AChip* OwningCharacter = Cast<AChip>(GetOwningPlayerPawn()))
	{
		return OwningCharacter->GetHealthAsPercentage();
	}
	else
	{
		return 0.0f;
	}
}

float UChipHUDWidget::GetPlayerFury() const
{
	if (AChip* OwningCharacter = Cast<AChip>(GetOwningPlayerPawn()))
	{
		return OwningCharacter->GetFuryAsPercentage();
	}
	else
	{
		return 0.0f;
	}
}

int UChipHUDWidget::GetPlayerHealthConsumableQ() const
{
	if (AChip* OwningCharacter = Cast<AChip>(GetOwningPlayerPawn()))
	{
		return OwningCharacter->GetHConsumablesQuantity();
	}
	else
	{
		return 0;
	}
}

int UChipHUDWidget::GetPlayerFuryConsumableQ() const
{
	if (AChip* OwningCharacter = Cast<AChip>(GetOwningPlayerPawn()))
	{
		return OwningCharacter->GetFConsumablesQuantity();
	}
	else
	{
		return 0;
	}
}


