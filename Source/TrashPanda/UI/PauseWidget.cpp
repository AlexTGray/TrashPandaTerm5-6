// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "PauseWidget.h"




void UPauseWidget::NativeConstruct()
{
		Super::NativeConstruct();

		ResumeButton->OnClicked.AddDynamic(this, &ThisClass::OnResumeClicked);
}

void UPauseWidget::OnResumeClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Resume Clicked"));
}
