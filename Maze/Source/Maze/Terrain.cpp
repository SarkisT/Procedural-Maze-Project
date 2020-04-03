// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain.h"
#include "Engine.h"
#include <random>
#include "BasicFloor.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//FRandomStream(100);
	//Frandom

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("CurrentFloor not NULL"));
	//UWorld* const World = GetWorld();

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("World not NULL, SPAWN PLEASE"));
			
		//GetWorld()->SpawnActor<ABasicFloor>(CurrentFloor, TileLocation, TileRotation, spawnParams);
	

}


// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();

	//FRandomStream()
	//FRandomStream seed;

	//seed.GenerateNewSeed();
	
	if (customSeed != 0) {
		seed.Initialize(customSeed);
	}
	else {
		seed.Initialize(FMath::RandRange(0, 30000));
	}

	obj1 = seed.RandRange(1, (NumberMeshesX * NumberMeshesY));

	do {
		obj2 = seed.RandRange(1, (NumberMeshesX * NumberMeshesY));
	} while (obj2 == obj1);

	do {
		obj3 = seed.RandRange(1, (NumberMeshesX * NumberMeshesY));
	} while (obj3 == obj1 || obj3 == obj2);
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Initial seed chosen: %i  , but we chose this seed %i "), seed.GetInitialSeed() , seed.GetCurrentSeed()));

	OriginalLocation = GetActorLocation();

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, OriginalLocation.ToString());
	FRotator TileRotation = FRotator(0, 0, 0);
	//Spawn(OriginalLocation, TileRotation);
	
	FActorSpawnParameters spawnParams;
	
	if (Difficulty == 1) {
		Timer = 50;
		NumberMeshesX = 10;
		NumberMeshesY = 10;
	}
	else if (Difficulty == 2)
	{
		Timer = 30;
		NumberMeshesX = 20;
		NumberMeshesY = 20;
	}
	else if (Difficulty == 3)
	{
		Timer = 20;
		NumberMeshesX = 40;
		NumberMeshesY = 40;
	}

	for (int i = 0; i < NumberMeshesX; i++)//X number of Meshes to spawn
	{
		for (int j = 0; j < NumberMeshesY; j++)//Y number of Mesh to spawn
		{
			FVector TileLocation = FVector(OriginalLocation.X + (i * MeshWidth),OriginalLocation.Y + (j * MeshLength), OriginalLocation.Z);//Where to spawn

			Spawn(i, j, TileLocation, TileRotation);//Spawn Method

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
	FActorSpawnParameters spawnParams;//Default params
	
	count++;

	//Spawning Objectives.
	if (obj1 == count) {
		FVector BallLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z + 250);//Where to spawn

		GetWorld()->SpawnActor<AObjective>(Ball, BallLocation, SpawnRotation, spawnParams);//Ball we spawning
	}

	if (obj2 == count) {
		FVector BallLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z + 250);//Where to spawn

		GetWorld()->SpawnActor<AObjective>(Ball, BallLocation, SpawnRotation, spawnParams);//Ball we spawning
	}

	if (obj3 == count) {
		FVector BallLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z + 250);//Where to spawn

		GetWorld()->SpawnActor<AObjective>(Ball, BallLocation, SpawnRotation, spawnParams);//Ball we spawning
	}

	
		
		if (tileNum < (NumberMeshesY - 1))		//ROW BEING ADDED.
		{
			blocksSpawned++;
			tileNum++;
			
			SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(BaseFloor, SpawnLocation, SpawnRotation, spawnParams);//Tile we spawning

			TileRow.Add(SpawnedObject);//Add this to array.//0,1,2,3,4,
		
		}

		if(tileNum == (NumberMeshesY - 1)) {//After we done with adding the row. Time to split it
			tileNum = -1;
		
				//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, FString::Printf(TEXT("TileRow     %i"), (TileRow.Num() - 1)));
			if (NumberMeshesX <= 20) {
				splitNum = seed.RandRange(2, (NumberMeshesY / 2)); //How long is the split.	
				indexNum = seed.RandRange(1, (NumberMeshesY - splitNum - 1));	//Starting index of row array to split (RANDOM)	

			}
			else if(NumberMeshesX > 20) {
				splitNum = seed.RandRange(3, (NumberMeshesY / 3)); //How long is the split.	
				
				splitNum2 = splitNum;
		
				indexNum = seed.RandRange(1, (NumberMeshesY / 3) - 1);	
				
			}	

			indexBeginAndEndSplits.Add(indexNum);//Begin of the split. Keeping track of it.
				
			while(splitNum > 0) {
						
				if (TileRow[indexNum]->split == false) {//DON'T TOUCH ANYTHING HERE YET.!!!!!!!!!!!!!!!!
								
					TileRow[indexNum]->split = true;
		
					indexNum++;
				}
				else{			
					GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Black, FString::Printf(TEXT("SPLIT is TRUE ERROR   %i"), indexNum));//Seems good.
				}
					splitNum--;
			} 

					indexBeginAndEndSplits.Add((indexNum - 1));//End of the split. Keeping track of it.
			
					for (int j = indexBeginAndEndSplits[0]; j <= indexBeginAndEndSplits[1]; j++) {//Join them together
						if (TileRow[j]->split == true) {
							
							if (j == indexBeginAndEndSplits[0]) {
								TileRow[j]->DestroyWalls(2);
							}
							else if (j > 0 && j < indexBeginAndEndSplits[1]) {
								TileRow[j]->DestroyWalls(1);
								TileRow[j]->DestroyWalls(2);
							}
							else {
								TileRow[j]->DestroyWalls(1);
							}
						}
					}

					//Start
					//====================================================
					if (NumberMeshesX > 20) {
						
						indexNum2 = seed.RandRange(indexNum, (NumberMeshesY - 1 - splitNum2));

						indexBeginAndEndSplits.Add(indexNum2);//Begin of the split. Keeping track of it.

						while (splitNum2 > 0) {
							
							if (TileRow[indexNum2]->split == false) {//DON'T TOUCH ANYTHING HERE YET.!!!!!!!!!!!!!!!!


								TileRow[indexNum2]->split = true;

								indexNum2++;
							}
							splitNum2--;

						}

						indexBeginAndEndSplits.Add((indexNum2 - 1));//End of the split. Keeping track of it.

						for (int j = indexBeginAndEndSplits[2]; j <= indexBeginAndEndSplits[3]; j++) {//Join them together
							if (TileRow[j]->split == true) {
							
								if (j == indexBeginAndEndSplits[2]) {
									TileRow[j]->DestroyWalls(2);
								}
								else if (j > 0 && j < indexBeginAndEndSplits[3]) {
									TileRow[j]->DestroyWalls(1);
									TileRow[j]->DestroyWalls(2);
								}
								else {
									TileRow[j]->DestroyWalls(1);
								}
							}
						}

					}
					//===========================================
					//End

					//After split, Rest of tiles become it's own group.
					for (int i = 0; i < TileRow.Num(); i++)
					{
						if (TileRow[i]->split == false) {
						
						
							if (i == 0) {//2
						
								TileRow[i]->DestroyWalls(2);
				
							}
							else if (i > 0 && i < (TileRow.Num() - 1)) {//1, 2
								TileRow[i]->DestroyWalls(1);
			
								TileRow[i]->DestroyWalls(2);
							}
							else {// 1
								TileRow[i]->DestroyWalls(1);
								
							}
						}
					}

					

					if (prevRow == true ) {//Split part 2. Starts At second row.

						for (int i = 0; i < (extendedTilesIndex.Num()); i++)
						{
						
							TileRow[extendedTilesIndex[i]]->DestroyWalls(4);
					
						}
					
						if (extended == false) {
							extendedTilesIndex.Empty();
						}
					}
					else {//Doing this to avoid first row.
						prevRow = true;
					}				
					
					ExtendA = 1;//Extend tiles. Part 1
					while (ExtendA > 0) {//Current Row. Time to extend the tile, Remove wall 3

						a = seed.RandRange(indexBeginAndEndSplits[0], indexBeginAndEndSplits[1]);//Randomly pick a Tile INSIDE SetA.
						
						//First Extension! Tile INSIDE FIRST SET
						if (TileRow[a]->E == true) {

							if (X != (NumberMeshesX - 1)) {
								TileRow[a]->DestroyWalls(3);
							}

							if (X != 0) {
								TileRow[a]->DestroyWalls(4);
							}

							extendedTilesIndex.Add(a);//Adds chosen index so next row keeps track of it.						
						}
						else {				
							do
							{
								a = seed.RandRange(indexBeginAndEndSplits[0], indexBeginAndEndSplits[1]);//Randomly pick a Tile INSIDE SetA.

							} while ( TileRow[a]->E == false);

							if (X != (NumberMeshesX - 1)) {//Last row only
								TileRow[a]->DestroyWalls(3);
							}

							if (X != 0) {//First row only
								TileRow[a]->DestroyWalls(4);
							}						
							extendedTilesIndex.Add(a);							
						}

						//Second extension, This is Before SET A
						if (indexBeginAndEndSplits[0] != 0) {//Make sure this isn't first tile

							
							n = seed.RandRange(0, (indexBeginAndEndSplits[0] - 1));//Pick a tile BEFORE SetA
							
							if (TileRow[n]->E == true) {
								
								if (X != (NumberMeshesX - 1)) {
									TileRow[n]->DestroyWalls(3);
								}

								if (X != 0) {
									TileRow[n]->DestroyWalls(4);
								}
								extendedTilesIndex.Add(n);
							}
							else {

								do
								{
									n = seed.RandRange(0, (indexBeginAndEndSplits[0] - 1));//Pick a tile BEFORE SetA

								} while (TileRow[n]->E == false);

								if (X != (NumberMeshesX - 1)) {
									TileRow[n]->DestroyWalls(3);
								}

								if (X != 0) {
									TileRow[n]->DestroyWalls(4);
								}
								extendedTilesIndex.Add(n);
							}							
						}
						
						if (NumberMeshesX > 20) {

							d = seed.RandRange((indexBeginAndEndSplits[1] + 1), (indexBeginAndEndSplits[2] - 1));//Pick a tile BETWEEN SetA AND B
		
							b = seed.RandRange(indexBeginAndEndSplits[2], indexBeginAndEndSplits[3]);//Pick a tile After SetA
							
							if (TileRow[b]->E == true) {

								if (X != (NumberMeshesX - 1)) {
									TileRow[b]->DestroyWalls(3);
									TileRow[d]->DestroyWalls(3);
								}

								if (X != 0) {
									TileRow[b]->DestroyWalls(4);
									TileRow[d]->DestroyWalls(4);
								}
								extendedTilesIndex.Add(b);
								extendedTilesIndex.Add(d);

							}
							else {

								do
								{
									b = seed.RandRange(indexBeginAndEndSplits[2], indexBeginAndEndSplits[3]);//SEcond set

								} while (TileRow[b]->E == false);

								if (X != (NumberMeshesX - 1)) {
									TileRow[b]->DestroyWalls(3);
									TileRow[d]->DestroyWalls(3);
								}

								if (X != 0) {
									TileRow[b]->DestroyWalls(4);
									TileRow[d]->DestroyWalls(4);
								}
								extendedTilesIndex.Add(b);
								extendedTilesIndex.Add(d);
							}
						}

						//Final extension
						if (indexBeginAndEndSplits[1] != (TileRow.Num() - 1) && NumberMeshesX <= 20) {//Make sure this isn't last tile
							
							c = seed.RandRange((indexBeginAndEndSplits[1] + 1), (TileRow.Num() - 1));//Tile AFTER SetA

							if (TileRow[c]->E == true) {

								if (X != (NumberMeshesX - 1)) {
									TileRow[c]->DestroyWalls(3);
								}

								if (X != 0) {
									TileRow[c]->DestroyWalls(4);
								}
								extendedTilesIndex.Add(c);

							}
							else {

								do
								{
									c = seed.RandRange((indexBeginAndEndSplits[1] + 1), (TileRow.Num() - 1));//Tile AFTER SetA

								} while (TileRow[c]->E == false);

								if (X != (NumberMeshesX - 1)) {
									TileRow[c]->DestroyWalls(3);
								}

								if (X != 0) {
									TileRow[c]->DestroyWalls(4);
								}
								extendedTilesIndex.Add(c);
							}
						}
						else if(indexBeginAndEndSplits[3] != (TileRow.Num() - 1) && NumberMeshesX > 20){
							
							c = seed.RandRange((indexBeginAndEndSplits[3] + 1), (TileRow.Num() - 1));

							if (TileRow[c]->E == true) {

								if (X != (NumberMeshesX - 1)) {
									TileRow[c]->DestroyWalls(3);
								}

								if (X != 0) {
									TileRow[c]->DestroyWalls(4);
								}
								extendedTilesIndex.Add(c);

							}
							else {

								do
								{
									c = seed.RandRange((indexBeginAndEndSplits[1] + 1), (TileRow.Num() - 1));//Tile AFTER SetA

								} while (TileRow[c]->E == false);

								if (X != (NumberMeshesX - 1)) {
									TileRow[c]->DestroyWalls(3);
								}

								if (X != 0) {
									TileRow[c]->DestroyWalls(4);
								}
								extendedTilesIndex.Add(c);
							}
						}
						else {

							
							if (X != (NumberMeshesX - 1)) {
								TileRow[c]->DestroyWalls(3);
							}

							if (X != 0) {
								TileRow[c]->DestroyWalls(4);
							}

							extendedTilesIndex.Add((NumberMeshesX - 1));
						}


						//GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Blue, FString::Printf(TEXT("End of Set A %i , Start of Set B  %i , Chosen Tile index Between %i "), indexBeginAndEndSplits[1], indexBeginAndEndSplits[2], d));

						ExtendA--;				
					}						

					if (X == (NumberMeshesX - 1)) {
						ClearFinalRow();
					}

					extended = false;
					indexBeginAndEndSplits.Empty();

					TileRow.Empty();
					
	
		}
	
}

void ATerrain::ClearFinalRow()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("TileRow Num for Clear %i"), TileRow.Num()));

	for (int i = 0; i < (TileRow.Num()); i++)
	{
		if (i == 0) {//2
								//TileRow[i]->DestroyWalls(1);
			TileRow[i]->DestroyWalls(2);
			//TileRow[i]->DestroyWalls(3);
			//TileRow[i]->DestroyWalls(4);
		}
		else if (i > 0 && i < (TileRow.Num() - 1)) {//1, 2
			TileRow[i]->DestroyWalls(1);
			//	TileRow[i]->DestroyWalls(3);
			//TileRow[i]->DestroyWalls(4);
			TileRow[i]->DestroyWalls(2);
		}
		else {// 1
			TileRow[i]->DestroyWalls(1);
		}
	}
}

