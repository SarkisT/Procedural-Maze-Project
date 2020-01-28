// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain.h"
#include "Engine.h"
#include "BasicFloor.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	//FVector TileLocation = FVector(0, 0, 0);

	//FRotator TileRotation = FRotator(0, 0, 0);
	//FActorSpawnParameters spawnParams;

	// who did the spawn, and we are say this controller did 
	//spawnParams.Owner = this;

	// Set the instigator to default 
	//spawnParams.Instigator = Instigator;
	//spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	//AActor* SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(CurrentFloor, TileLocation, TileRotation, spawnParams);
	
	
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Hope this works...."));
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("%s"), FString::Printf(CurrentFloor));


	//if (CurrentFloor != NULL) {
	

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("CurrentFloor not NULL"));
	//UWorld* const World = GetWorld();

		//if (World != NULL) {
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("World not NULL, SPAWN PLEASE"));
			
			//GetWorld()->SpawnActor<ABasicFloor>(CurrentFloor, TileLocation, TileRotation, spawnParams);
			
		//}



	//}
	//auto currentObject = Cast<ABasicFloor>(SpawnedObject);

	
	//AttachToComponent(RootComponent,)APowerUP_Parent* ourNewObject = GetWorld()->SpawnActor<APowerUP_Parent>(ourSpawningObject, ourLoc, ourRotation, spawnParams);

	

	//BaseFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	//RootComponent = BaseFloor;


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
	
	
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Hope this works...."));
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("%s"), FString::Printf(CurrentFloor));


	//if (CurrentFloor != NULL) {

	//FVector TileLocation = FVector(0, 0, 0);

	//FRotator TileRotation = FRotator(0, 0, 0);
	FActorSpawnParameters spawnParams;

	//spawnParams.Owner = this;
	//spawnParams.Instigator = Instigator;

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("CurrentFloor not NULL"));
	//UWorld*const World = GetWorld();

		//if (World != NULL) {
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("World not NULL"));
			//World->SpawnActor<ABasicFloor>(CurrentFloor, TileLocation, TileRotation, spawnParams);
			//AActor* SpawnedObject = World->SpawnActor<AActor>(CurrentFloor, TileLocation, TileRotation, spawnParams);//Cast<ABasicFloor>(CurrentFloor);

			//AActor* newActor = GetWorld()->SpawnActor<AProc_Tree>(treeOne, newVec, FRotator::ZeroRotator, spawnParams);

			//World->SpawnActor
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("Skipped spawning"));

			//if (SpawnedObject != nullptr) {

				//World->SpawnActor<ABasicFloor*>(SpawnedObject, TileLocation, TileRotation, spawnParams);

			//}
			
		
		//}



	//}

	for (int i = 0; i < (NumberMeshesX); i++)
	{
		for (int j = 0; j < NumberMeshesY; j++)
		{
			FVector TileLocation = FVector(OriginalLocation.X + (i * MeshWidth),OriginalLocation.Y + (j * MeshLength), OriginalLocation.Z);
			//FVector TileLocation = FVector(10.0, 10.0, 1.0);

			FRotator TileRotation = FRotator(0, 0, 0);
			FActorSpawnParameters spawnParams;

			Spawn(TileLocation, TileRotation);

			//GetWorld()->SpawnActor(SpawnedObject);
			//Spawn(TileLocation, TileRotation);
			//GetWorld()->SpawnActor<ABasicFloor>()
			//CreateDefaultSubobject<UStaticMesh>(BaseFloor);
			//AddComponent(TileLocation, BaseFloor);

		}

	}
	
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATerrain::Spawn(FVector SpawnLocation, FRotator SpawnRotation)
{

	FActorSpawnParameters spawnParams;
	//spawnParams.Owner = this;
	//spawnParams.Instigator = Instigator;

	AActor* SpawnedObject = GetWorld()->SpawnActor<AActor>(CurrentFloor, SpawnLocation, SpawnRotation, spawnParams);

	//DEBUG STUFF
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("We spawned an object"));
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, SpawnLocation.ToString());
}

