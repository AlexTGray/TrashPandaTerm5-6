#include "TrashPanda.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sphere component to react to physics.
	USphereComponent* EnemySphere = CreateDefaultSubobject<USphereComponent>(TEXT("ROOT COMPONENT"));
	EnemySphere->SetupAttachment(RootComponent);
	EnemySphere->InitSphereRadius(40.0f);
	EnemySphere->SetCollisionProfileName(TEXT("PAWN"));

	//InventoryComponent for loot table;
	//Inventory = CreateDefaultSubobject<Inventory>(TEXT("Inventory Class Directory Here"));
	//Inventory->SetupAttachment(RootComponent);

	//Attach Skeletal Mesh to Enemy.  Edit path to attach proper enemy mesh.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemySkeletalMesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin"));
	if (EnemySkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(EnemySkeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	}
	//Attach Animation Blueprint to the enemy.  Edit path to attach proper enemy animation blueprint.
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> EnemyAnim(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP"));
	if (EnemyAnim.Succeeded())
	{
		this->GetMesh()->SetAnimInstanceClass(EnemyAnim.Object->GetAnimBlueprintGeneratedClass());
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void AEnemy::LootDrop()
{

}