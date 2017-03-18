// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "Test_AI.h"

//add
// Sets default values for this component's properties
UTest_AI::UTest_AI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTest_AI::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTest_AI::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

