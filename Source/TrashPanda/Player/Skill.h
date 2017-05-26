// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Skill.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRASHPANDA_API USkill : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkill();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
