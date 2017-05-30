// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Item.h"
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
	int AddHealth(int h);
private:
	int health;
};