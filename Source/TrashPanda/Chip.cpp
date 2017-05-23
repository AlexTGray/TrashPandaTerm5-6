// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "BaseItem.h"
#include "InventoryComponent.h"
#include "IMaterial.h"
#include "InventoryWidget.h"
#include "IConsumable.h"
#include "ChipAnimInstance.h"
#include "CharacterWidgetSwitcher.h"

#include "Chip.h"

#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text) 

// Sets default values
AChip::AChip()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	RootComponent->ComponentTags.Add("Player");

	PickupRadius = CreateDefaultSubobject<USphereComponent>(TEXT("PickupRadius"));
	PickupRadius->SetupAttachment(RootComponent);
	PickupRadius->bGenerateOverlapEvents = true;
	PickupRadius->SetSphereRadius(150.0f, true);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
//tags
	RootComponent->ComponentTags.Add("Player");	
	Tags.Add("Player");
	this->Tags.Add("Player");
	PickupRadius->ComponentTags.Add("Player");

}

// Called when the game starts or when spawned
void AChip::BeginPlay()
{
	Super::BeginPlay();
	PickupRadius->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	PickupRadius->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);

	animInstance = GetMesh()->GetAnimInstance();

	if (InvWidgetClass)
	{
		InvWidget = CreateWidget<UInventoryWidget>(GetWorld()->GetFirstPlayerController(), InvWidgetClass);
		InvWidget->AddToPlayerScreen();
		InvWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (WidgetSwitcherClass)
	{
		SwitchWidget = CreateWidget<UCharacterWidgetSwitcher>(GetWorld()->GetFirstPlayerController(), WidgetSwitcherClass);
		SwitchWidget->AddToPlayerScreen();
		SwitchWidget->SetVisibility(ESlateVisibility::Hidden);
	}


}

// Called every frame
void AChip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AChip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
	InputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ThisClass::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ThisClass::LookUpAtRate);

	InputComponent->BindAction("LAttack", IE_Pressed, this, &ThisClass::LightAttackPressed);
	InputComponent->BindAction("LAttack", IE_Released, this, &ThisClass::LightAttackReleased);
	InputComponent->BindAction("HAttack", IE_Pressed, this, &ThisClass::HeavyAttackPressed);
	InputComponent->BindAction("HAttack", IE_Released, this, &ThisClass::LightAttackReleased);
	InputComponent->BindAction("OpenInv", IE_Pressed, this, &ThisClass::OpenInv);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &ThisClass::Dodge);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ThisClass::Interact);
	InputComponent->BindAction("ReadInv", IE_Pressed, this, &ThisClass::ReadInv);
	InputComponent->BindAction("OpenCharPanel", IE_Pressed, this, &ThisClass::OpenCharPanel);
}

bool AChip::GetIsLightAttacking()
{
	return bisLightAttacking;
}

bool AChip::GetIsHeavyAttacking()
{
	return bisHeavyAttacking;
}

void AChip::SetPlayerStats(int level)
{
	Health = 100;
	Damage = 0;
	Fury = 100;
	Speed = 10;

	CritChance = .10f;
	CritModifier = 1.2f;

	DodgeDistance = 4;
}

void AChip::Interact()
{
	print("Interacting...");
	for (int i = 0; i < itemsInRange.Num(); i++)
	{
		if (itemsInRange[i])
		{
			if (ABaseItem* thing = Cast<ABaseItem>(itemsInRange[i]))
			{
				Inventory->AddItem(thing->GetClass());
				UE_LOG(LogTemp, Warning, TEXT("ItemType %s"), *GetNameSafe(thing->GetClass()));

				const int32* count = Inventory->GetItems().Find(thing->GetClass());
				UE_LOG(LogTemp, Warning, TEXT("Items in TMap %d"), *count);

				thing->Destroy();
			}
		}
	}
}

void AChip::LightAttackPressed()
{
	bisLightAttacking = true;
}

void AChip::LightAttackReleased()
{
	bisLightAttacking = false;
}

void AChip::HeavyAttackPressed()
{
	bisHeavyAttacking = true;
	print("Heavy Attack");
}

void AChip::HeavyAttackReleased()
{
	bisHeavyAttacking = false;
}

void AChip::Dodge()
{
	print("Dodge");
}

void AChip::Rabid()
{
	print("Rabid");
}

void AChip::AddFury(int fury)
{
	Fury += fury;
}

void AChip::OpenInv()
{
	if (InvWidget->Visibility == ESlateVisibility::Hidden)
	{
		InvWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else if (InvWidget->Visibility == ESlateVisibility::Visible)
	{
		InvWidget->SetVisibility(ESlateVisibility::Hidden);
	}

}
void AChip::OpenCharPanel()
{
	if (SwitchWidget)
	{
		if (SwitchWidget->Visibility == ESlateVisibility::Hidden)
		{
			SwitchWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else if (SwitchWidget->Visibility == ESlateVisibility::Visible)
		{
			SwitchWidget->SetVisibility(ESlateVisibility::Hidden);
		}
}
}

void AChip::ReSpawn()
{

}

void AChip::Death()
{

}

void AChip::ReadInv()
{
	print("Read Inv Pressed");
	if (int32 num = Inventory->GetItems().Num())
	{
		//const int32* count = Inventory->GetItems().Find(AIConsumable::StaticClass());
		//UE_LOG(LogTemp, Warning, TEXT("Items in TMap %d"), count);
		//count = Inventory->GetItems().Find(AIMaterial::StaticClass());
		//UE_LOG(LogTemp, Warning, TEXT("Items in TMap %d"), count);
		//count = Inventory->GetItems().Find(ABaseItem::StaticClass());
		//UE_LOG(LogTemp, Warning, TEXT("Items in TMap %d"), count);
		UE_LOG(LogTemp, Warning, TEXT("Items in TMap %d"), num);
	}
}

void AChip::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Tags.Contains("Pickup"))
	{
		if (!itemsInRange.Contains(OtherActor))
		{
			itemsInRange.Add(OtherActor);
			print("Item in Range");
		}

	}
}

void AChip::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Tags.Contains("Pickup"))
	{
		if (itemsInRange.Contains(OtherActor))
		{
			itemsInRange.Remove(OtherActor);
			print("Item has left Range");
		}
	}
}
void AChip::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AChip::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AChip::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AChip::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
