// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicFloor.h"
#include "Objective.h"
//#include "PlayerWidget.h"
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

	//Timer for the maze
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		int Timer = 0;
	//Difficulty of maze
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		int Difficulty;

	//Dimension of maze
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int NumberMeshesX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	int NumberMeshesY;
	
	//Sizes of individual tiles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	float MeshWidth = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
	float MeshLength = 100.0f;

	//Tile reference
	UPROPERTY(EditAnywhere, Category = "Floor")
	TSubclassOf<ABasicFloor> BaseFloor;

	//Objective reference
	UPROPERTY(EditAnywhere, Category = "Objective")
	TSubclassOf<AObjective> Ball;

	//Input custom seed, else it's random
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
		int customSeed;//Using this to change seed inside BP

	FRandomStream seed;	//Game seed!

	int count = 0;

	int obj1, obj2, obj3; //Objectives to spawn
	
	
	ABasicFloor* SpawnedObject;

	TArray<ABasicFloor*> TileRow;//Row of  our tiles.

	int tileNum = -1;//Counts us the row

	int ExtendA;//Used for extension


	TArray<int> indexBeginAndEndSplits;//Tracks Index where Sets have been split.

	TArray<int> extendedTilesIndex;//Tracks Index of extended Tiles

	bool prevRow = false;
	bool extended = true;

	int splitNum;	//Length of split Set A
	int splitNum2;  //split B

	int indexNum;	//Index of starting split A
	int indexNum2;	


	int n; //Extension before Set A
	int a; //Extension inside Set A
	int b; //Extension Between Sets A and B
	int d; //Extension Inside Set B
	int c; //After Set B

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OriginalLocation;

	UFUNCTION(BluePrintCallable)
	void Spawn(int X, int Y, FVector SpawnLocation, FRotator SpawnRotation);

	UFUNCTION()
		void ClearFinalRow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool spawned = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
