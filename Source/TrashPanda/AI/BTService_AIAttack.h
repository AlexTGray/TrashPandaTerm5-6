// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "BehaviorTree/BTService.h"
#include "AI/Enemy.h"
#include "BTService_AIAttack.generated.h"

/**
 * 
 */
UCLASS()
class TRASHPANDA_API UBTService_AIAttack : public UBTService
{
	GENERATED_BODY()
	
public :
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:




};
