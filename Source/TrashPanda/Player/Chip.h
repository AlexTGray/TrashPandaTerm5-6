#pragma once

#include "GameFramework/Character.h"
#include "Chip.generated.h"

UCLASS()
class TRASHPANDA_API AChip : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChip();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	bool GetIsLightAttacking();
	bool GetIsHeavyAttacking();

	int32 PlayerExperience;
	int32 PlayerLevel;

	float CurrentHealth;
	float MaxHealth;
	int32 CurrentFury;
	int32 MaxFury;

	float GetHealthAsPercentage();
	float GetHealth();
	float GetMaxHealth();
	float GetFuryAsPercentage();
	float GetFury();
	float GetMaxFury();
	int32 GetHConsumablesQuantity();
	int32 GetFConsumablesQuantity();

	//void TakeDamage(float damage);

	//Functions to debug health and fury
	void DebugHealth();
	void DebugFury();

	//Pause
	void PauseGame();

protected:
	bool bisRabid;
	bool bisLightAttacking;
	bool bisHeavyAttacking;
	int32 Damage;
	int32 DamageReduction;
	int32 Speed;
	int32 DodgeDistance;

	int32 CritChance;
	int32 CritModifier;

	//UENUM(BlueprintType, Category = "Levels")
	enum ExperienceToLevel //28 levels for now, increase/decrease according to # of skills in skill trees/ max level
	{
		LevelOne = 300, LevelTwo = 900, LevelThree = 1200, LevelFour = 1500, LevelFive = 1800, LevelSix = 2100, LevelSeven = 2400, LevelEight = 2700, LevelNine = 3000, LevelTen = 3300, LevelEleven = 3600, LevelTwelve = 3900,
		LevelThirteen = 4200, LevelFourteen = 4500, LevelFifteen = 4800, LevelSixteen = 5100, LevelSeventeen = 5400, LevelEighteen = 5700, LevelNineteen = 6000, LevelTwenty = 6300, LevelTwentyOne = 6600,
		LevelTwentyTwo = 6900, LevelTwentyThree = 7200, LevelTwentyFour = 7500, LevelTwentyFive = 7800, LevelTwentySix = 8100, LevelTwentySeven = 8400, LevelTwentyEight = 8700, LevelTwentyNine = 9000, LevelThirty = 9300
	};

	//Pause Toggle
	bool bGamePaused = false;

	//Pickup Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
		class USphereComponent* PickupRadius;

	//Camera Boom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
		class USpringArmComponent* CameraBoom;

	//Follow Cam
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = Player)
		class UInventoryComponent* Inventory;

	class UAnimInstance* AnimInstance;

	//PauseMenu
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UPauseWidget> PauseWidgetClass;

	class UPauseWidget* PauseGameWidget;




	//class Inventory* PlayerInventory;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UInventoryWidget> InvWidgetClass;

	class UInventoryWidget* InvWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UChipHUDWidget>ChipHUDWidgetClass;

	class UChipHUDWidget* ChipHUDWidget;


	TSubclassOf<class UCharacterWidgetSwitcher> WidgetSwitcherClass;

	class UCharacterWidgetSwitcher* SwitchWidget;

	UPROPERTY(VisibleAnywhere, Category = Player)
		TArray<AActor*> itemsInRange;

	void SetPlayerStats(int32 level);
	void Interact();
	void LightAttackPressed();
	void LightAttackReleased();
	void HeavyAttackPressed();
	void HeavyAttackReleased();
	void Dodge();
	void Rabid();
	void AddFury(int32 fury);
	void OpenInv();
	void OpenCharPanel();

	void GainExperience(int32 amount);
	void LevelUp(int32 overflowExperience);


	void ReSpawn();
	void Death();

	void ReadInv();





	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



protected:
	UPROPERTY()
		TSubclassOf <class ABaseWeapon> StartingWeaponClass;

	class ABaseWeapon* CurrentWeapon;

};