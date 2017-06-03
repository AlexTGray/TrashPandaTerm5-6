// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Player/Chip.h"
#include "EnemyAIController.h"
#include "AI/Enemy.h"
#include "BTService_SelectTarget.h"



#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text) 


void UBTService_SelectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AChip* OwningCharacter = Cast<AChip>(OwnerComp.GetAIOwner()->GetPawn());
	UAIPerceptionComponent* Perception = OwnerComp.GetAIOwner()->GetPerceptionComponent();

	AActor* FoundTarget = FindTarget(Perception, OwningCharacter);

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(TEXT("Target"), FoundTarget);
	if (FoundTarget != NULL)
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(TEXT("InCombat"), true);
	}
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