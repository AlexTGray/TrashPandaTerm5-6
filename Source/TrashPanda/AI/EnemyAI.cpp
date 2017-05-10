// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "EnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"

void AEnemyAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
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



