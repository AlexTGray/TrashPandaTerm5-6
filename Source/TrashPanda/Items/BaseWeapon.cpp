// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "BaseWeapon.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	collider->CanCharacterStepUp(false);
	RootComponent = collider;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	collider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);
}

void ABaseWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Tags.Contains("Enemy"))
	{

	}
}

void ABaseWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Tags.Contains("Enemy"))
	{

	}
}

