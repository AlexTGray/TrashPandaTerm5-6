// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "BaseItem.h"
#include "IMaterial.generated.h"

/**
 * 
 */
UCLASS()
class TRASHPANDA_API AIMaterial : public ABaseItem
{
	GENERATED_BODY()

public:
	AIMaterial();
	virtual void BeginPlay() override;

protected:
	bool Consume(int32 toUSE) override;
	TArray<FString> MaterialList;

	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	TEnumAsByte<EMaterials> MatType;
};


//