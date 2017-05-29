// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "EnemyAI.h"
#include "AI/AI_TargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyAI::AEnemyAI()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	PatrolPointKey = "PatrolPoint";
}

void AEnemyAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	//Get possessed character and make sure it's the EnemyAICharacter
	AEnemyAI * AIChar = Cast<AEnemyAI>(InPawn);

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_TargetLocation::StaticClass(), PatrolPoints);
	}
	//if (AIChar)
	//{
	//	//If the blackboard is valid initialize the blackboard for the corresponding behavior tree
	//	if (AIChar->BehaviorTreeAsset->BlackboardAsset)
	//	{
	//		BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTreeAsset->BlackboardAsset));
	//	}

	//	/*Populate the array of available bot target points
	//	The following function needs a TArray of AActors, that's why I declared the
	//	BotTargetPoints as such. When I will need to get an exact point and compare it,
	//	I will cast it to the corresponding class (ABotTargetPoint)*/
	//	RunBehaviorTree(BehaviorTreeAsset);
	//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_TargetLocation::StaticClass(), PatrolPoints);

	//	//Start the behavior tree which corresponds to the specific character
	//	BehaviorComp->StartTree(*AIChar->BehaviorTreeAsset);
	//}
}

ETeamAttitude::Type AEnemyAI::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherCharacter = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherCharacter->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherCharacter->GetController());
		}

		return GetAttitudeTowardsPlayer(Other);
	}

	return ETeamAttitude::Neutral;
}

ETeamAttitude::Type AEnemyAI::GetAttitudeTowards(FGenericTeamId TeamA, FGenericTeamId TeamB)
{
	return TeamA == TeamB ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}

ETeamAttitude::Type AEnemyAI::GetAttitudeTowardsPlayer(const AActor& Other) const
{
	return ETeamAttitude::Hostile;
}





