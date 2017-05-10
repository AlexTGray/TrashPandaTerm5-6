// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "Test_AI_Controller.h"
#include "Test_AI_Character.h"
#include "AI_TargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

//add
ATest_AI_Controller::ATest_AI_Controller()
{
	//Initialize Blackboard and Behavior Tree
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	//Initialize Keys
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";

	CurrentPatrolPoint = 0;
}

void ATest_AI_Controller::SetPlayerCaught(APawn * pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, pawn);
	}
}

void ATest_AI_Controller::Possess(APawn * pawn)
{
	Super::Possess(pawn);
	//Get Reference to Character
	ATest_AI_Character* AICharacter = Cast<ATest_AI_Character>(pawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
		//Populate patrol point array
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_TargetLocation::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}



}

