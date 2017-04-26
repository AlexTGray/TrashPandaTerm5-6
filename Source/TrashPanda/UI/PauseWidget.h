// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = Widgets)
		class UButton* ResumeButton;

protected:
	UFUNCTION()
		void OnResumeClicked();
	
	
};
