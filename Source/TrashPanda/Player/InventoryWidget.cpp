// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "InventoryWidget.h"




void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
UUniformGridPanel* UInventoryWidget::GetGridPanel()
{
	return GridPanel;
}