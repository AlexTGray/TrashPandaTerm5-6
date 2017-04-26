// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "TrashPandaGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TRASHPANDA_API ATrashPandaGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
		ATrashPandaGameModeBase(const FObjectInitializer& ObjectInitializer);
	
		virtual void RestartGame() ;

};
