// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicFloor.h"
#include "Engine.h"

// Sets default values
ABasicFloor::ABasicFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FloorTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	FloorTile->SetupAttachment(RootComponent);
	
	
	//FTransform Root = FloorTile->GetComponentTransform();
	
	//NWall = AddComponent(FName("WALL"), false, Root, UStaticMeshComponent);//CreateSubobject<UStaticMeshComponent>(TEXT("Wall"));
	//AddComponent("Wall", true, Root, UStaticMeshComponent);
	

	//EWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	//EWall->SetupAttachment(FloorTile);

	//WWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	//WWall->SetupAttachment(FloorTile);

	//SWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	//SWall->SetupAttachment(FloorTile);

	//FloorTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	//RootComponent = FloorTile;

	//FloorTile->SetWorldScale3D(FVector(1.0, 1.0, 0.2f));
	

}

// Called when the game starts or when spawned
void ABasicFloor::BeginPlay()
{
	Super::BeginPlay();
	FloorTile->SetWorldScale3D(FVector(7.0, 7.0, 0.25));
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FloorTile->GetComponentScale().ToString());
}

// Called every frame
void ABasicFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

