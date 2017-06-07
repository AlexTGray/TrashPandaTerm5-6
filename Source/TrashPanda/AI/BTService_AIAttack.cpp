// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "EnemyAIController.h"
#include "BTService_AIAttack.h"



#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text) 


void UBTService_AIAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	AEnemyAIController*  controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()->GetBrainComponent()); 

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

//	if (controller != NULL)
//	controller->AttackBasic();

	// set the calculation to distance here
	
	print("I attacked bitch");

}
