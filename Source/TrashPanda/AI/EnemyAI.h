// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "AIController.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class TRASHPANDA_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
		
		
public:
	virtual void Possess(APawn* InPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly)
		FGenericTeamId TeamId;
	
	virtual ETeamAttitude::Type GetAttitudeTowardsPlayer(const AActor& Other) const;

public:
	FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	static ETeamAttitude::Type GetAttitudeTowards(FGenericTeamId TeamA, FGenericTeamId TeamB);

};
