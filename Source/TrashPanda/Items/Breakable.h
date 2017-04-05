// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "GameFramework/Actor.h"
#include "BaseItem.h"
#include "IMaterial.h"
#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text) 

#include "Breakable.generated.h"


UCLASS()
class TRASHPANDA_API ABreakable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	UPROPERTY(VisibleAnywhere)
	float health = 2;

	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* Collider;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABaseItem> ItemClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AIMaterial> MaterialClass;

private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
