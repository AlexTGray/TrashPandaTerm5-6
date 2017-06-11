// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Player/Chip.h"
#include "Blueprint/UserWidget.h"
#include "PopUpWindowWidgetClass.generated.h"



/**
 * 
 */
UCLASS()
class TRASHPANDA_API UPopUpWindowWidgetClass : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct();

	UFUNCTION()
		void OnExitSelected();

	UFUNCTION(BlueprintCallable, Category = PopUp)
		FText GetPopUpText() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PopUp)
		FText DisplayText;

	UFUNCTION(BlueprintCallable, Category = PopUp)
		void SetPopUpText(const FText& NewDisplayText);

protected:
	UPROPERTY(EditAnywhere, BluePrintReadOnly, meta = (BindWidget), Category = PopUp)
		class UTextBlock* PopUpText;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, meta = (BindWidget), Category = PopUp)
		class UButton* ExitButton;
};
