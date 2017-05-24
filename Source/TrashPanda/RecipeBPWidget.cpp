// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "RecipeBPWidget.h"
#include "Items/BaseItem.h"
#include "Items/BaseWeapon.h"

void URecipeBPWidget::NativeConstruct()
{
	Super::NativeConstruct();
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

*/

void URecipeBPWidget::OnItemSelected() const
{
	UE_LOG(LogTemp, Display, TEXT("Item Clicked & Selected"));
}

FText URecipeBPWidget::SetItemName() const
{
	FText name;
	name = FText::FromString(Item->GetName());
	return name;
}

FSlateBrush URecipeBPWidget::SetItemImage() const
{
	return FSlateBrush();
}

UUniformGridPanel* URecipeBPWidget::GetGridPanel() const
{
	return RequirementGridPanel;
}

FText URecipeBPWidget::GetReq1() const
{
		return FText();
}

FText URecipeBPWidget::GetReq2() const
{
		return FText();
}

FText URecipeBPWidget::GetReq3() const
{
		return FText();
}

