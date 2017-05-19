// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "GameFramework/Actor.h"
#include "FindPlayer.generated.h"

UCLASS()
class TRASHPANDA_API AFindPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFindPlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* Collider;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;


	ACharacter* player=NULL;
};
