// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "Chip.h"
#include "ChipAnimInstance.h"




void UChipAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AChip* OwningPawn = Cast<AChip>(TryGetPawnOwner());
	if (OwningPawn)
	{
		Speed = OwningPawn->GetVelocity().Size();
		bisLightAttackingAnim = OwningPawn->GetIsLightAttacking();

	}
}

void UChipAnimInstance::isAttacking(bool onOff)
{
	//if (onOff == true)
	//{
	//	bisAttackingAnim = true;
	//}
	//else if (onOff == false)
	//{
	//	bisAttackingAnim = false;
	//}
}

void UChipAnimInstance::AnimNotify_DamageON()
{
	
}

void UChipAnimInstance::AnimNotify_DamageOFF()
{

}

bool UChipAnimInstance::getbIsAttacking()
{
	return bisLightAttackingAnim;
}
