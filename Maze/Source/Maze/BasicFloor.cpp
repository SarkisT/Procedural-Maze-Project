// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicFloor.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TileIndexWidget.h"


// Sets default values
ABasicFloor::ABasicFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FloorTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	FloorTile->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABasicFloor::BeginPlay()
{
//NORTH = 1
//SOUTH = 2
//EAST = 3
//WEST = 4
	Super::BeginPlay();
	this->GetComponents(StaticComps);

	FloorTile->SetWorldScale3D(FVector(MeshWidth, MeshLength, 0.25));

}

// Called every frame
void ABasicFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicFloor::DestroyWalls(int n)
{
	switch (n) {
	case 1:
		if (N == true) {
			StaticComps[1]->DestroyComponent();
			N = false;
		}
		break;
	case 2:
		if (S == true) {
			StaticComps[2]->DestroyComponent();
			S = false;

		}
		break;
	case 3:
		if (E == true) {
			StaticComps[3]->DestroyComponent();		
			E = false;

		}
		break;
	case 4:
		if (W == true) {
			StaticComps[4]->DestroyComponent();			
			W = false;
		}
		break;
	}

}

