// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicFloor.h"
#include "Engine.h"

// Sets default values
ABasicFloor::ABasicFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//FloorTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	//RootComponent = FloorTile;

	//FloorTile->SetWorldScale3D(FVector(1.0, 1.0, 0.2f));
	

}

// Called when the game starts or when spawned
void ABasicFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

