// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "AIController.h"
#include "Test_AI_Controller.generated.h"

/**
 *  AI Controller
 */
UCLASS()
class TRASHPANDA_API ATest_AI_Controller : public AAIController
{
	GENERATED_BODY()

	//Behavior Component
	UBehaviorTreeComponent* BehaviorComp;
	//Blackboard Component
	UBlackboardComponent* BlackboardComp;


	//Blackboard Keys
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey;

	TArray<AActor*> PatrolPoints;
	virtual void Possess(APawn *Pawn) override;



public:
	ATest_AI_Controller();
	
	int32 CurrentPatrolPoint = 0;

	void SetPlayerCaught(APawn* Pawn);

	//Inline Getter Functions
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	
};
