// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "Breakable.h"
#include "BaseItem.h"
#include "IMaterial.h"
#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text) 


// Sets default values
ABreakable::ABreakable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> MatBP(TEXT("'/Game/DropMaterials/RazorBladesBP.RazorBladesBP'"));
	if (MatBP.Object)
	{
		MaterialClass = (UClass*)MatBP.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ABreakable::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABreakable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ABreakable::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//UE_LOG(LogTemp, Display, TEXT("WE ARE IN THE BEAM"));
	UWorld* wp = GetWorld();
	FActorSpawnParameters SpawnParameters;
	FVector aux = GetActorLocation();

	//print(	OtherActor->TagSubobjects.ActorHasTag("Player"));
	if (OtherActor->ActorHasTag("Player"))
	{
		print("hue");
		//ABaseItem* item = GetWorld()->SpawnActor<ABaseItem>(ABaseItem::StaticClass(), GetActorLocation() + 60, FRotator::ZeroRotator);
		AIMaterial* item = GetWorld()->SpawnActor<AIMaterial>(MaterialClass, GetActorLocation(), FRotator::ZeroRotator);

	}

	this->Destroy();
 

	
}


	