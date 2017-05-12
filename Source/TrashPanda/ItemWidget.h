// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
*
*/
UCLASS()
class TRASHPANDA_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetQuantity(int32 count);
	void SetItemImage();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = ItemWidget)
		class UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = ItemWidget)
		class UTextBlock* Quantity;
};