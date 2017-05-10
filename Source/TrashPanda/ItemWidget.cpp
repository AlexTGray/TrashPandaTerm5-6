// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "ItemWidget.h"




void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemWidget::SetQuantity(int32 count)
{
	if (!Quantity) { return; UE_LOG(LogTemp, Error, TEXT("Quantity Null:")); }
	Quantity->SetText(FText::AsNumber(count));
}

void UItemWidget::SetItemImage()
{

}