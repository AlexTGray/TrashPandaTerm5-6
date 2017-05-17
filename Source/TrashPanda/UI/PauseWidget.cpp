// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "UI/PauseWidget.h"
#include "Player/Chip.h"



void UPauseWidget::NativeConstruct()
{
		Super::NativeConstruct();

		

	
			ResumeButton->OnClicked.AddDynamic(this, &ThisClass::OnResumeClicked);
		

	
			QuitButton->OnClicked.AddDynamic(this, &ThisClass::OnQuitClicked);
		
		//Part 2: Alternate way to get variables/functions from other classes
		//PauseWidgetItem = Cast<AChip>(GetWorld()->GetFirstPlayerController()->GetPawn());
		//if (!PauseWidgetItem)
		//{
		//	UE_LOG(LogTemp, Display, TEXT("Pause widget failed to find player"));
		//}
}

void UPauseWidget::OnResumeClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Resume Clicked"));

	//Get chip and all of his functions/variables
	if (AChip* player = Cast<AChip>(GetOwningPlayer()->GetPawn()))
	{
		player->PauseGame();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Failed to cast player"));
	}
}

void UPauseWidget::OnQuitClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Exit Clicked"));

	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}