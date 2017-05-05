// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRASHPANDA_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UUniformGridPanel* GetGridPanel();
	

protected:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = Widgets)
	class UUniformGridPanel* GridPanel;
	
	
};
