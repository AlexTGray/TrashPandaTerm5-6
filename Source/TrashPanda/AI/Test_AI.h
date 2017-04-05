// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Test_AI.generated.h"

//add
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRASHPANDA_API UTest_AI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTest_AI();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
