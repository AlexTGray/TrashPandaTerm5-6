// Fill out your copyright notice in the Description page of Project Settings.

#include "TrashPanda.h"
#include "TrashPandaGameState.h"
#include "TrashPandaPlayerState.h"
#include "TrashPandaGameModeBase.h"




ATrashPandaGameModeBase::ATrashPandaGameModeBase(const FObjectInitializer& ObjectInitializer)
{
	GameStateClass = ATrashPandaGameState::StaticClass();
	PlayerStateClass = ATrashPandaPlayerState::StaticClass();
}
