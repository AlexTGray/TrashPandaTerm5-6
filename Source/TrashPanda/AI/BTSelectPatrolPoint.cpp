// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "BTSelectPatrolPoint.h"
#include "AI_TargetLocation.h"
#include "Test_AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"

//add
EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ATest_AI_Controller* AICon = Cast<ATest_AI_Controller>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		//Get BB component
		UBlackboardComponent * BlackboardComp = AICon->GetBlackboardComp();

		AAI_TargetLocation * CurrentPoint = Cast<AAI_TargetLocation>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

		AAI_TargetLocation* NextPatrolPoint = nullptr;


		if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<AAI_TargetLocation>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]);
		}
		else
		{
			NextPatrolPoint = Cast<AAI_TargetLocation>(AvailablePatrolPoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
