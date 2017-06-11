// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "Player/Chip.h"
#include "PopUpWindowWidgetClass.h"

void UPopUpWindowWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton->OnClicked.AddDynamic(this, &ThisClass::OnExitSelected);
}

void UPopUpWindowWidgetClass::OnExitSelected()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Clicked Exit"));
	this->SetVisibility(ESlateVisibility::Hidden);
}

FText UPopUpWindowWidgetClass::GetPopUpText() const
{
	/*FText textToDisplay = FText::FromString(text);
	return textToDisplay;*/
	return DisplayText;
}

void UPopUpWindowWidgetClass::SetPopUpText(const FText & NewDisplayText)
{
	DisplayText = NewDisplayText;
}
