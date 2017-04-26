// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class TRASHPANDA_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UChipHUDWidget>ChipHUDWidgetClass;
	class UChipHUDWidget* ChipHUDWidget;

	
	
};
