// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "FindPlayer.h"


// Sets default values
AFindPlayer::AFindPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AFindPlayer::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AFindPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (player != NULL)
	{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("FUCK ME BITCHES")));
	}
	FVector distance = this->GetActorLocation() - player->GetActorLocation();
	int32 aux = distance.SizeSquared();
	//int32 aux = FVector::Dist(this->GetActorLocation(), player->GetActorLocation());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f,%f,%f"),distance.X,distance.Y,distance.Z ));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f"), aux));



}

