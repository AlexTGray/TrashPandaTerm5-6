// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

#include "Player/Chip.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"


/**
 * 
 */
UCLASS()
class TRASHPANDA_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	//Part 1: Alternate way to get variables/functions
	//class AChip* PauseWidgetItem = nullptr;

	//AChip* PauseWidgetItem = Cast<AChip>(ChipPlayer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = PauseWidgetButtons)
		class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = PauseWidgetButtons)
		class UButton* QuitButton;

protected:
	UFUNCTION()
		void OnResumeClicked();

	UFUNCTION()
		void OnQuitClicked();
	
	
};