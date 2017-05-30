// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "Test_AI_Character.h"
#include "Test_AI_Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
//add
// Sets default values
ATest_AI_Character::ATest_AI_Character()
{
	//ALEX CODE
	//initialize pawn sensor
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

}

// Called when the game starts or when spawned
void ATest_AI_Character::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ATest_AI_Character::OnPlayerCaught);
	}
}


// Called to bind functionality to input
void ATest_AI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATest_AI_Character::OnPlayerCaught(APawn* Pawn)
{
	//Get Reference to Player Controller
	ATest_AI_Controller *AIController = Cast<ATest_AI_Controller>(GetController());
	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I'm touching you."));
		AIController->SetPlayerCaught(Pawn);
	}
}