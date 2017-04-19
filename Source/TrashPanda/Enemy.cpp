// Fill out your copyright notice in the Description page of Project Settings.

#include "Floak.h"
#include "Enemy.h"

#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text) 
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Points[0] = FVector(2, 2, 2);
	int auxX = Points[0].X;
	int auxY = Points[0].Y;
	int auxZ = Points[0].Z;

     //	UE_LOG(YourLog, Warning, TEXT(Points[0]);
	UE_LOG(LogTemp, Warning, TEXT("Positon X:%d //Positon Y:%d//Positon Z:%d " ), auxX,auxY,auxZ);
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

