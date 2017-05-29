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
		
	UBlackboardComponent* BlackboardComp;
	UBehaviorTreeComponent* BehaviorComp;

	TArray<AActor*> PatrolPoints;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PatrolPointKey;
		
public:
	virtual void Possess(APawn* InPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly)
	FGenericTeamId TeamId;
	
	virtual ETeamAttitude::Type GetAttitudeTowardsPlayer(const AActor& Other) const;

public:
	AEnemyAI();

	FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	static ETeamAttitude::Type GetAttitudeTowards(FGenericTeamId TeamA, FGenericTeamId TeamB);

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

};
