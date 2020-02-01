// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain.h"
#include "Engine.h"
#include "BasicFloor.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("CurrentFloor not NULL"));
	//UWorld* const World = GetWorld();

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("World not NULL, SPAWN PLEASE"));
			
		//GetWorld()->SpawnActor<ABasicFloor>(CurrentFloor, TileLocation, TileRotation, spawnParams);
	

}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	//FVector TileLocation = FVector(0, 0, 0);

	OriginalLocation = GetActorLocation();

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, OriginalLocation.ToString());
	FRotator TileRotation = FRotator(0, 0, 0);
	//Spawn(OriginalLocation, TileRotation);
	
	FActorSpawnParameters spawnParams;


	for (int i = 0; i < (NumberMeshesX); i++)//X number of Meshes to spawn
	{
		for (int j = 0; j < NumberMeshesY; j++)//Y number of Mesh to spawn
		{
			FVector TileLocation = FVector(OriginalLocation.X + (i * MeshWidth),OriginalLocation.Y + (j * MeshLength), OriginalLocation.Z);

			//int rotation = FMath::RandRange(0, 2);//Rotation spawn

		
			FRotator TileRotation = FRotator(0,0, 0);
			FActorSpawnParameters spawnParams;

			Spawn(i, j, TileLocation, TileRotation);

		}

	}
	
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATerrain::Spawn(int X, int Y, FVector SpawnLocation, FRotator SpawnRotation)
{

	FActorSpawnParameters spawnParams;
	//spawnParams.Owner = this;
	//spawnParams.Instigator = Instigator;


	//int n = FMath::RandRange(0, 3);//Random pick on what we gonna spawn
	ABasicFloor* SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(BaseFloor, SpawnLocation, SpawnRotation, spawnParams);
	if (X == 0 && Y == 0) {
		//SpawnedObject->GetComponents<
	}
	/*
	if (n == 0) {
		ABasicFloor* SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(BaseFloor, SpawnLocation, SpawnRotation, spawnParams);
	}
	else if (n == 1) {
		ABasicFloor* SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(wall1, SpawnLocation, SpawnRotation, spawnParams);
	}
	else if (n == 2){
		ABasicFloor* SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(wall2, SpawnLocation, SpawnRotation, spawnParams);
	}
	else {
		ABasicFloor* SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(wall3, SpawnLocation, SpawnRotation, spawnParams);

	}
	*/
	//DEBUG STUFF
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("We spawned an object"));
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, SpawnLocation.ToString());
}

