// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 *
 */
UCLASS()
class TRASHPANDA_API AEnemyAIController : public AAIController
{

	GENERATED_BODY()

public:
	virtual void Possess(APawn* InPawn) override;
	void AttackBasic();

protected:
	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviorTreeAsset;



	UPROPERTY(EditDefaultsOnly)
		FGenericTeamId TeamId;

public:
	FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	static ETeamAttitude::Type GetAttitudeTowards(FGenericTeamId TeamA, FGenericTeamId TeamB);



protected:
	virtual ETeamAttitude::Type GetAttitudeTowardsPlayer(const AActor& Other) const;


	void CalculateRandomPos();

};
