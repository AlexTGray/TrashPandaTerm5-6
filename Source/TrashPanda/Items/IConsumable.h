// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "BaseItem.h"
#include "IConsumable.generated.h"

/**
 * 
 */

UCLASS()
class TRASHPANDA_API AIConsumable : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AIConsumable();
	virtual void BeginPlay() override;


protected:
	TArray<FString> ConsumableList;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Consumable")
	TEnumAsByte<EConsumables> ConsType;
	
};

