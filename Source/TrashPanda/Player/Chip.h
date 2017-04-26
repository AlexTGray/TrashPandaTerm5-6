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
	int GetHConsumablesQuantity();
	int GetFConsumablesQuantity();

	//Functions to debug health and fury
	void DebugHealth();
	void DebugFury();


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

	class UAnimInstance* animInstance;

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

	void SetPlayerStats(int level);
	void Interact();
	void LightAttackPressed();
	void LightAttackReleased();
	void HeavyAttackPressed();
	void HeavyAttackReleased();
	void Dodge();
	void Rabid();
	void AddFury(int fury);
	void OpenInv();
	void OpenCharPanel();
	void PauseGame();

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