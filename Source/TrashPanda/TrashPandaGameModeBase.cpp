// Fill out your copyright notice in the Description page of Project Settings.

#include "TrashPanda.h"
#include "Player/Chip.h"
#include "TrashPandaPlayerState.h"
#include "TrashPandaGameState.h"
#include "TrashPandaGameModeBase.h"
#include "UI/PlayerHUD.h"



ATrashPandaGameModeBase::ATrashPandaGameModeBase(const FObjectInitializer& ObjectInitializer)
{
	DefaultPawnClass = AChip::StaticClass();
	GameStateClass = ATrashPandaGameState::StaticClass();
	PlayerStateClass = ATrashPandaPlayerState::StaticClass();
	HUDClass = APlayerHUD::StaticClass();

	ConstructorHelpers::FClassFinder<AChip> CharacterClass(
		TEXT("Blueprint'/Game/Player/Chip_BP.Chip_BP_C'"));

	if (CharacterClass.Class)
	{
		DefaultPawnClass = CharacterClass.Class;
	}

	ConstructorHelpers::FClassFinder<APlayerHUD>ChipHUDWidgetClass(
		TEXT("Blueprint'/Game/UI/ChipHUD.ChipHUD_C'"));
	//cant find the HUD for some reason. fix.

	if (ChipHUDWidgetClass.Class)
	{
		HUDClass = ChipHUDWidgetClass.Class;
		UE_LOG(LogTemp, Warning, TEXT("SET CHIPHUDWIDGETCLASS AS DEFAULT HUD CLASS!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("!!!DID NOT SET CHIPHUDWIDGETCLASS AS DEFAULT HUD CLASS"));
	}

}




void ATrashPandaGameModeBase::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}

