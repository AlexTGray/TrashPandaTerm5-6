// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
<<<<<<< HEAD
=======
#include "BehaviorTree/BTTaskNode.h"
>>>>>>> refs/remotes/origin/Raph_Branch
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
	
<<<<<<< HEAD
=======
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
>>>>>>> refs/remotes/origin/Raph_Branch
	
};