// All Rights Reserved for Students Graduating TFS Summer 2017
#pragma once

#include "Blueprint/UserWidget.h"
#include "ChipHUDWidget.generated.h"


/**
 * 
 */
UCLASS()
class TRASHPANDA_API UChipHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;





	
protected:
	//For displaying current health on HUD
	UFUNCTION(BlueprintCallable, Category = HUD)
	float GetPlayerHealth() const;

	//For displaying current fury on HUD
	UFUNCTION(BlueprintCallable, Category = HUD)
	float GetPlayerFury() const;

	//For displaying quantity of Health consumables on HUD
	UFUNCTION(BlueprintCallable, Category = HUD)
	int32 GetPlayerHealthConsumableQ() const;
	//For displaying quantity of Fury consumables on HUD	
	UFUNCTION(BlueprintCallable, Category = HUD)
	int32 GetPlayerFuryConsumableQ() const;
};