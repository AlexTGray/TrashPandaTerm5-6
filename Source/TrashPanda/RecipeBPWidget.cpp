// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "RecipeBPWidget.h"
#include "Items/BaseItem.h"
#include "Items/BaseWeapon.h"
#include "Player/Chip.h"

void URecipeBPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SelectItem->OnClicked.AddDynamic(this, &ThisClass::OnItemSelected);
}

/*
Widget components:
-Selection Button
-ItemName
-ItemImage
-RequirementGridPanel
-1stReq
-2ndReq
-3rdReq
*/

/*
TO DO - Nick:
1) return the proper name, image, requirements, etc of each item.
2) Look into DefaultObjects for this maybe
3) Remember how i did it in unity and compare/change
4) Once I'm returning the proper variables, populate the crafting menu.

DONE
*/

void URecipeBPWidget::OnItemSelected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attempting To Craft..."));
	/*
	Current Issue:
	- Cant access the player's inventory properly to check for the requirements.
	- Once I get the check done, I can easily use the same method to add/remove items.
	- Then, crafting is done
	*/

	//if (AChip* player = Cast<AChip>(GetWorld()->GetFirstPlayerController()))
	//{
	//	if (player->Inventory->HasItemOfType(this->Item->GetDefaultObject<ABaseWeapon>()->FirstIDRequirement))
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Has Req1"));
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Display, TEXT("Failed to cast player"));
	//}

	//UE_LOG(LogTemp, Display, TEXT("Item Clicked & Selected"));
}

FText URecipeBPWidget::SetItemName() const
{
	//this->Item->GetDefaultObject<ABaseWeapon>()->itemName;

	FText name = FText::FromString(this->Item->GetDefaultObject<ABaseWeapon>()->itemName);
	return name;
}

FSlateBrush URecipeBPWidget::SetItemImage() const
{
	return this->Item->GetDefaultObject<ABaseWeapon>()->img;
}

UUniformGridPanel* URecipeBPWidget::GetGridPanel() const
{
	return RequirementGridPanel;
}

FText URecipeBPWidget::GetReq1() const
{
	FText firstReq = FText::FromString(this->Item->GetDefaultObject<ABaseWeapon>()->FirstTextRequirement);
	return firstReq;
}

FText URecipeBPWidget::GetReq2() const
{
	FText secondReq = FText::FromString(this->Item->GetDefaultObject<ABaseWeapon>()->SecondTextRequirement);
	return secondReq;
}

FText URecipeBPWidget::GetReq3() const
{
	FText thirdReq = FText::FromString(this->Item->GetDefaultObject<ABaseWeapon>()->ThirdTextRequirement);
	return thirdReq;
}

