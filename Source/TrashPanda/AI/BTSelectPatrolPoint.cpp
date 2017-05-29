// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "BTSelectPatrolPoint.h"
#include "AI_TargetLocation.h"
#include "AI/EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"

//add
EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyAI* AICon = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		//Get BB component
		UBlackboardComponent * BlackboardComp = AICon->GetBlackboardComp();

		AAI_TargetLocation * CurrentPoint = Cast<AAI_TargetLocation>(BlackboardComp->GetValueAsObject("PatrolPoint"));
		
		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

		int32 RandomIndex;

		AAI_TargetLocation* NextPatrolPoint = nullptr;
		
		do
		{
			RandomIndex = FMath::RandRange(0, AvailablePatrolPoints.Num()-1);
			int32 i = AvailablePatrolPoints.Num();
		
			UE_LOG(LogTemp, Warning, TEXT("Available Patrol Points: %d"), i);
			
			NextPatrolPoint = Cast<AAI_TargetLocation>(AvailablePatrolPoints[RandomIndex]);

		} while (CurrentPoint == NextPatrolPoint);

		BlackboardComp->SetValueAsObject("PatrolPoint", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
