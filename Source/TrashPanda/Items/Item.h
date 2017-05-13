// All Rights Reserved for Students Graduating TFS Summer 2017
#pragma once
#include "GameFramework/Actor.h"
#include "Item.generated.h"
UCLASS()
 class TRASHPANDA_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	// functions to 
	virtual void Use(); // have to check on game settings the button

//getters
	FString GetName();
	int32 GetId();

private:
		FString itemName;
		int32 itemId;
protected:
	UStaticMesh *mesh;	
};
