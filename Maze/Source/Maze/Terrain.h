// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicFloor.h"
#include "Terrain.generated.h"


UCLASS()
class MAZE_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

	//UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* BaseFloor;

	//Mesh Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberMeshesX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberMeshesY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MeshWidth = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MeshLength = 100.0f;

	UPROPERTY(EditAnywhere, Category = Floor)
	TSubclassOf<ABasicFloor> BaseFloor;

	int seed;

	int count = 0;

	//UPROPERTY(EditDefaultsOnly, Category = UI)
	//TSubclassOf<UTileIndexWidget> tileUI;

	ABasicFloor* SpawnedObject;

	TArray<UStaticMeshComponent*> ObjComps;

	TArray<ABasicFloor*> TileRow;
	TArray<ABasicFloor*> SetA;
	TArray<ABasicFloor*> SetB;
	TArray<ABasicFloor*> SetC;
	int tileNum = -1;

	int ExtendA;
	int ExtendB;
	int ExtendC;

	TArray<int> indexBeginAndEndSplits;
	TArray<int> extendedTilesIndex;
	TArray<int> splitIndex;

	bool prevRow = false;
	bool extended = true;

	int p = 0;
	int a;
	int n;
	int c;
	int blocksSpawned = 0;
	int redWalls = 0;
	int emptyTiles = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OriginalLocation;

	UFUNCTION(BluePrintCallable)
	void Spawn(int X, int Y, FVector SpawnLocation, FRotator SpawnRotation);

	UFUNCTION()
		void ClearFinalRow(TArray<ABasicFloor*> row);
	//bool bCanSpawn;

	//FTimerHandle SpawnTimer;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool spawned = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
