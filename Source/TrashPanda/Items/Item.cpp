// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "Item.h"
// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void AItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
// Abstract Functions
void AItem::Use(){} // overwrite
FString AItem::GetName()
{
	return itemName;
}
int32 AItem::GetId() 
{
	return itemId;
}
