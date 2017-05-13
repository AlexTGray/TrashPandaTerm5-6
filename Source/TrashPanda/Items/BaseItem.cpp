// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "BaseItem.h"

#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text) 

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Tags.Add("Pickup");

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = collider;
	collider->bGenerateOverlapEvents = true;

	RootComponent->ComponentTags.Add("Pickup");

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(true);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
//Returns the ItemName
FString ABaseItem::GetName()
{
	return itemName;
}
//Returns the ItemID
int32 ABaseItem::GetId()
{
	return itemId;
}

void ABaseItem::Combine(int32 toADD)
{
	quantity += toADD;
}

bool ABaseItem::Consume(int32 toUSE)
{
	if (toUSE >= quantity)
	{
		return true;
	}
	else
	{
		print("Not Enough Items");
		return false;
	}
}
//Sets the isOnGround bool
void ABaseItem::setIsOnGround()
{
	isOnGround = !isOnGround;
}