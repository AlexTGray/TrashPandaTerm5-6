#include "TrashPanda.h"
#include "Items/BaseItem.h"
#include "Items/BaseWeapon.h"
#include "Player/InventoryComponent.h"
#include "ItemWidget.h"
#include "Items/IMaterial.h"
#include "Player/InventoryWidget.h"
#include "Items/IConsumable.h"
#include "Player/ChipAnimInstance.h"
#include "UI/CharacterWidgetSwitcher.h"
#include "Player/Chip.h"
#include "ChipHUDWidget.h"
#include "TrashPandaGameModeBase.h"

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

	AnimInstance = GetMesh()->GetAnimInstance();
	SetPlayerStats(1);

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

	if (StartingWeaponClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = this;
		CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(StartingWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);

	}


	////Wont Add it to screen,
	////CRASHES THE GAME
	//if (ChipHUDWidgetClass)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("CHIPHUDWIDGETCLASS EXISTS, THIS SHOULD ATTEMPT TO PUT IT ON SCREEN"));
	//	//ChipHUDWidget = CreateWidget<UChipHUDWidget>(GetWorld()->GetFirstPlayerController(), ChipHUDWidgetClass);
	//	//ChipHUDWidget->AddToPlayerScreen();
	//	//ChipHUDWidget->SetVisibility(ESlateVisibility::Visible);
	//}
}

// Called every frame
void AChip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AChip::SetPlayerStats(int32 level)
{
	MaxHealth = 100;
	MaxFury = 100;
	CurrentHealth = MaxHealth;
	CurrentFury = MaxFury;
	Damage = 0;
	Speed = 10;

	CritChance = .10f;
	CritModifier = 1.2f;

	DodgeDistance = 4;
}

void AChip::Interact()
{
	print("Interacting...");
	for (int32 i = 0; i < itemsInRange.Num(); i++)
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
	//If(GetEquippedWeaponType == Slashing)
	//{CalculatedDamage = (Damage + GetWeaponDamage()) * 1.5f;
	//else
	//{CalculatedDamage = (Damage + GetWeaponDamage())
	//OnCollisionWithEnemy
	//DealDamage(CalculatedDamage)
}

void AChip::LightAttackReleased()
{
	bisLightAttacking = false;
}

void AChip::HeavyAttackPressed()
{
	AGameMode* aux = Cast <AGameMode>(GetWorld()->GetAuthGameMode());
	aux->RestartGame();

	bisHeavyAttacking = true;
	print("Heavy Attack");
	//If(GetEquippedWeaponType == Bludgeoning)
	//{CalculatedDamage = (Damage + GetWeaponDamage()) * 1.5f;
	//else
	//{CalculatedDamage = (Damage + GetWeaponDamage())
	//OnCollisionWithEnemy
	//DealDamage(CalculatedDamage)
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

void AChip::AddFury(int32 fury)
{
	CurrentFury += fury;
}

//void AChip::OpenInv()
//{
//	if (InvWidget->Visibility == ESlateVisibility::Hidden)
//	{
//		InvWidget->SetVisibility(ESlateVisibility::Visible);
//	}
//	else if (InvWidget->Visibility == ESlateVisibility::Visible)
//	{
//		InvWidget->SetVisibility(ESlateVisibility::Hidden);
//	}
//
//}
void AChip::OpenInv()
{
	if (InvWidget->Visibility == ESlateVisibility::Hidden)
	{
		InvWidget->SetVisibility(ESlateVisibility::Visible);
		int16 columns = 0;
		int16 rows = 0;
		for (int32 i = 0; i < CountInv(); i++)
		{
			UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld()->GetFirstPlayerController(), ItemWidgetClass);
			UUniformGridSlot* test = InvWidget->GetGridPanel()->AddChildToUniformGrid(ItemWidget);
			if (test)
				{
				test->UUniformGridSlot::SetColumn(columns);
				test->UUniformGridSlot::SetRow(rows);
				}
			else
				 {
				UE_LOG(LogTemp, Error, TEXT("UniformGridSlot Pointer NULL"));
				return;
				}
						//ItemWidget->SetItemImage();
				ItemWidget->SetQuantity(10);
			columns++;
			if (columns >= 3)
			{
				columns = 0;
				rows++;
			}
		}
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

<<<<<<< HEAD
void AChip::ReSpawn()
=======

//Experience bar needs to update a bar on the HUD eventually. ------TO DO----------------
void AChip::GainExperience(int32 amount)
>>>>>>> refs/remotes/origin/Nick_Branch2
{

<<<<<<< HEAD
}

void AChip::Death()
=======
	//If the player has earned enough exp to level up
	if (PlayerExperience >= ExperienceToLevel(PlayerLevel))
	{
		//Calculate the overflow of experience gained (Eg; 1200 PlayerExperience - 900)
		int32 overflowExperience = PlayerExperience - ExperienceToLevel(PlayerLevel);
		//Call LevelUp and pass it the overflow of exp. (Alternatively, I could just do that in here, but why not.
		LevelUp(overflowExperience);
	}
}

void AChip::LevelUp(int32 overflowExperience)
>>>>>>> refs/remotes/origin/Nick_Branch2
{

}
int32 AChip::CountInv()
{

	int32 num = Inventory->GetItems().Num();
	return num;

	
	if (bGamePaused == false) //Is the game Paused? If not, pause it.
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		print("Paused Game");
		bGamePaused = true;
		FInputModeGameAndUI Mode;
		Mode.SetWidgetToFocus(PauseGameWidget->GetCachedWidget());
		GetWorld()->GetFirstPlayerController()->SetInputMode(Mode);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

		//Trying to get the mouse to return to center screen when you pause the game.
		//FViewport* v = Cast<FViewport>(GetWorld()->GetGameViewport()->Viewport->SetMouse(0.5, 0.5));


		//Is the inventory open? Then don't open the pause menu.
		if (InvWidget->Visibility == ESlateVisibility::Hidden)
		{
			PauseGameWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else //Is the game paused? If so, un-pause it.
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		print("Un-Paused Game");
		bGamePaused = false;
		FInputModeGameOnly GameOnly;
		GetWorld()->GetFirstPlayerController()->SetInputMode(GameOnly);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

		if (InvWidget->Visibility == ESlateVisibility::Hidden)
		{
			PauseGameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		if (InvWidget->Visibility == ESlateVisibility::Visible)
		{
			InvWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		if (PauseGameWidget->SetVisibility(ESlateVisibility::Visible))
		{
			PauseGameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AChip::ReSpawn()
{
	print("Hello World");
	//Needs to reset the player position, player stats, enemies, and everything in the whole level, basically. 
	//We need the reset function to accurately reset everything in level 1.
}

void AChip::Death()
{
	print("You died...");//Dark souls style lol

	//Need to instantiate a menu that asks whether the player wants to retry (ReSpawn();) or return to the main menu? (Maybe just respawn and quit.)

	//ReSpawn(); //?
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

float AChip::GetHealthAsPercentage()
{
	return GetHealth() / GetMaxHealth();
}

float AChip::GetHealth()
{
	return CurrentHealth;
}

float AChip::GetMaxHealth()
{
	return MaxHealth;
}

float AChip::GetFuryAsPercentage()
{
	return GetFury() / GetMaxFury();
}

float AChip::GetFury()
{
	return CurrentFury;
}

float AChip::GetMaxFury()
{
	return MaxFury;
}

int AChip::GetHConsumablesQuantity()
{
	return 5; //Setting to test
}

int AChip::GetFConsumablesQuantity()
{
	return 4; //setting to test
}

void AChip::DebugHealth()
{
	//Debugging to the screen
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0F, FColor::Yellow, FString::Printf(TEXT("Health: %f"), this->CurrentHealth));

	UE_LOG(LogTemp, Warning, TEXT("Health %f"), this->GetHealthAsPercentage());
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth %f"), this->GetHealth());
	UE_LOG(LogTemp, Warning, TEXT("MaxHealth %f"), this->GetMaxHealth());
}

void AChip::DebugFury()
{
	UE_LOG(LogTemp, Warning, TEXT("Health %f"), this->GetFuryAsPercentage());
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth %f"), this->GetFury());
	UE_LOG(LogTemp, Warning, TEXT("MaxHealth %f"), this->GetMaxFury());
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
