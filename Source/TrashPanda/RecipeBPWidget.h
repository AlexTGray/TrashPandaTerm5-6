// All Rights Reserved for Students Graduating TFS Summer 2017

#include "Blueprint/UserWidget.h"
#include "Items/BaseWeapon.h"
#include "RecipeBPWidget.generated.h"


#pragma once

/**
 * 
 */
UCLASS()
class TRASHPANDA_API URecipeBPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	/*
	Widget Layout & Components:
	-Selection Button
	-ItemName
	-ItemImage
	-RequirementGridPanel
	-1stReq
	-2ndReq
	-3rdReq
	*/

	UFUNCTION(BlueprintCallable, Category = Crafting)
		void OnItemSelected() const;

	UFUNCTION(BlueprintCallable, Category = Crafting)
	FText SetItemName() const;

	UFUNCTION(BlueprintCallable, Category = Crafting)
	FSlateBrush SetItemImage() const;

	UFUNCTION(BlueprintCallable, Category = Crafting)
	UUniformGridPanel* GetGridPanel() const;

	UFUNCTION(BlueprintCallable, Category = Crafting)
	FText GetReq1() const;

	UFUNCTION(BlueprintCallable, Category = Crafting)
	FText GetReq2() const;

	UFUNCTION(BlueprintCallable, Category = Crafting)
	FText GetReq3() const;
	
	//Do TsSubclassOf like in chip.h at the bottom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crafting)
	TSubclassOf <class ABaseWeapon> Item;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = CraftingWidgets)
		class UButton* SelectItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = CraftingWidgets)
		class UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = CraftingWidgets)
		class UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = CraftingWidgets)
		class UUniformGridPanel* RequirementGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = CraftingWidgets)
		class UTextBlock* Requirement1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = CraftingWidgets)
		class UTextBlock* Requirement2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = CraftingWidgets)
		class UTextBlock* Requirement3;

};
