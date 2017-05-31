// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

typedef TMap<TSubclassOf<class AActor>, int32> InventoryMap;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRASHPANDA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void AddItem(TSubclassOf<class AActor> ItemType);

	bool RemoveItem(TSubclassOf<class AActor> ItemType);

	bool HasItemOfType(TSubclassOf<class AActor> ItemType);

	const InventoryMap& GetItems() { return Items; }

	int32 GetItemCount(TSubclassOf<class AActor> ItemType);
	
private:
	InventoryMap Items;
};
