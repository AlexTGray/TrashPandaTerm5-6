// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "Skill.h"


// Sets default values for this component's properties
USkill::USkill()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkill::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkill::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

