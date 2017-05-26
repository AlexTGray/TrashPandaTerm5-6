// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTService_SelectTarget.generated.h"

/**
 * 
 */
UCLASS()
class TRASHPANDA_API UBTService_SelectTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	virtual AActor* FindTarget(class UAIPerceptionComponent* PerceptionComponent, class AChip* OwningCharacter);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
