// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "GameFramework/Character.h"
#include "Test_AI_Character.generated.h"
//add
UCLASS()
class TRASHPANDA_API ATest_AI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATest_AI_Character();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComp;

private:
	
	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);
};
