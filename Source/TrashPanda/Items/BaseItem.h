// All Rights Reserved for Students Graduating TFS Summer 2017

#pragma once
//\helloworld
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class TRASHPANDA_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//getters
	FString GetName();
	int32 GetId();

protected:
	UPROPERTY(VisibleAnywhere)
	FString itemName;
	int32 itemId;
	int32 quantity;
	bool isOnGround;
	

	FSlateBrush* invImage;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* collider;


	UFUNCTION(Category = Item)
	void Combine(int32 toADD);
	
	UFUNCTION(Category = Item)
	virtual bool Consume(int32 toUSE);

	UFUNCTION()
	void setIsOnGround();
};

UENUM(BlueprintType, Category = "ConsumableType")
enum EConsumables
{
	Health,
	Whisky
};

UENUM(BlueprintType, Category = "ConsumableType")
enum EMaterials
{
	LawnmowerBlade, // Machette1
	Newspaper, //Machette1
	DuctTape, //Machette1 and Shiv1
	Stick, //Hammer1
	TinCan, //Hammer1
	Rock, //Hammer1
	Nails, //Hammer2
	Bolts, //Fist1
	Glue, //Fist1
	ClothScraps, //Fist1
	BoxingGlove, //Fist2
	RazorBlade, //Fist2
	Glass, //Shiv1
	ChickenBone //Shiv2
};