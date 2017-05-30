// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once

UENUM(BlueprintType, Category = "WeaponType")
enum WeaponType
{
	Slashing, Bludgeoning
};

#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class TRASHPANDA_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	class UCapsuleComponent* collider;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	int32 LightDamage;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	int32 HeavyDamage;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	int32 AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TEnumAsByte<WeaponType> WType;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};