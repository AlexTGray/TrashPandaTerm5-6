// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "RecipeBPWidget.h"
#include "Items/BaseItem.h"
#include "Items/BaseWeapon.h"
#include "Player/Chip.h"
#include "Player/InventoryComponent.h"

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

void URecipeBPWidget::OnItemSelected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attempting To Craft..."));
	/*
	Current Issue:
	- Cant access the player's inventory properly to check for the requirements.
	- Once I get the check done, I can easily use the same method to add/remove items.
	- Then, crafting is done
	*/

	if (AChip* player = Cast<AChip>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{ 
		if (player->Inventory->HasItemOfType(this->Item->GetDefaultObject<ABaseWeapon>()->FirstIDRequirement))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Has Req1"));

			if (player->Inventory->HasItemOfType(this->Item->GetDefaultObject<ABaseWeapon>()->SecondIDRequirement))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Has Req2"));

				//Check for 3rd requirement
				if (this->Item->GetDefaultObject<ABaseWeapon>()->ThirdIDRequirement != NULL)
				{
					if (player->Inventory->HasItemOfType(this->Item->GetDefaultObject<ABaseWeapon>()->ThirdIDRequirement))
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Has Req3"));

						//Craft and remove 3 items
						player->Inventory->AddItem(this->Item);
						player->Inventory->RemoveItem(this->Item->GetDefaultObject<ABaseWeapon>()->FirstIDRequirement);
						player->Inventory->RemoveItem(this->Item->GetDefaultObject<ABaseWeapon>()->SecondIDRequirement);
						player->Inventory->RemoveItem(this->Item->GetDefaultObject<ABaseWeapon>()->ThirdIDRequirement);
						UE_LOG(LogTemp, Display, TEXT("Added Item"));
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Doesnt have Req3"));
					}
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Item doesn't have a 3rd Req"));

					//Craft and remove 2 items


					player->Inventory->AddItem(this->Item);
					player->Inventory->RemoveItem(this->Item->GetDefaultObject<ABaseWeapon>()->FirstIDRequirement);
					player->Inventory->RemoveItem(this->Item->GetDefaultObject<ABaseWeapon>()->SecondIDRequirement);
					UE_LOG(LogTemp, Display, TEXT("Added Item"));

				}

			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Doesnt have Req2"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Doesnt have Req1"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Failed to cast player"));
	}

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

