// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Items/Item.h"
#include "MyHealth_C.generated.h"

/**
 * 
 */
UCLASS()
class TRASHPANDA_API AMyHealth_C : public AItem
{
	GENERATED_BODY()
	

public:
	void Use();
	int32 AddHealth(int32 h);
private:
	int32 health;
};
