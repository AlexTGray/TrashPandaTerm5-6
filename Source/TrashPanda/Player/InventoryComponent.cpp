// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInventoryComponent::AddItem(TSubclassOf<class AActor> ItemType)
{
	int32 CurrentItemCount = GetItemCount(ItemType);

	Items.Add(ItemType, ++CurrentItemCount);
}

bool UInventoryComponent::RemoveItem(TSubclassOf<class AActor> ItemType)
{
	if (HasItemOfType(ItemType))
	{
		int32 CurrentItemCount = GetItemCount(ItemType);
		Items.Add(ItemType, --CurrentItemCount);
		return true;
	}
	return false;
}

bool UInventoryComponent::HasItemOfType(TSubclassOf<class AActor> ItemType)
{
	return GetItemCount(ItemType) > 0;
}

int32 UInventoryComponent::GetItemCount(TSubclassOf<class AActor> ItemType)
{
	if (Items.Contains(ItemType))
	{
		int32 CurrentItemCount = Items.FindRef(ItemType);
		return CurrentItemCount;
	}
	return 0;
}

