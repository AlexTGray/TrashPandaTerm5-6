// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "BTService_SelectTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Player/Chip.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "AI/Enemy.h"
#include "AI/EnemyAI.h"
#include "AI/AI_TargetLocation.h"

void UBTService_SelectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AChip* OwningCharacter = Cast<AChip>(OwnerComp.GetAIOwner()->GetPawn());
	UAIPerceptionComponent* Perception = OwnerComp.GetAIOwner()->GetPerceptionComponent();

	AActor* FoundTarget = FindTarget(Perception, OwningCharacter);
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(TEXT("Target"), FoundTarget);
}

EBTNodeResult::Type UBTService_SelectTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyAI* AICon = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		//Get BB component
		UBlackboardComponent * BlackboardComp = AICon->GetBlackboardComp();

		AAI_TargetLocation * CurrentPoint = Cast<AAI_TargetLocation>(BlackboardComp->GetValueAsObject("PatrolPoint"));

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

		BlackboardComp->SetValueAsObject("PatrolPoint", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

AActor* UBTService_SelectTarget::FindTarget(class UAIPerceptionComponent* PerceptionComponent, class AChip* OwningCharacter)
{
	TArray<AActor*> Hostiles;
	PerceptionComponent->GetHostileActors(Hostiles);

	if (Hostiles.Num() > 0)
	{
		return Hostiles[0];
	}

	return NULL;
}




