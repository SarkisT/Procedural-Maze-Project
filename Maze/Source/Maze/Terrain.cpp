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
	
	

}


// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	
	//If player put seed, Load custom seed. Otherwise random seed.
	if (customSeed != 0) {
		seed.Initialize(customSeed);
	}
	else {
		seed.Initialize(FMath::RandRange(0, 30000));
	}

	
	//Difficulty which will be set by the Buttons. (Easy, Normal, Hard)
	if (Difficulty == 1) {
		Timer = 90;
		NumberMeshesX = 8;
		NumberMeshesY = 8;
	}
	else if (Difficulty == 2)
	{
		Timer = 120;
		NumberMeshesX = 15;
		NumberMeshesY = 15;
	}
	else if (Difficulty == 3)
	{
		Timer = 240;
		NumberMeshesX = 30;
		NumberMeshesY = 30;
	}

	

	
	//Glowing Objective balls, which will be randomly chosen where to spawn inside the maze.

	obj1 = seed.RandRange(1, (NumberMeshesX * NumberMeshesY));

	do {
		obj2 = seed.RandRange(1, (NumberMeshesX * NumberMeshesY));
	} while (obj2 == obj1);

	do {
		obj3 = seed.RandRange(1, (NumberMeshesX * NumberMeshesY));
	} while (obj3 == obj1 || obj3 == obj2);
	
	
	//Just Debug Text, showing what seed was chosen and ball locations.
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Initial seed chosen: %i  , but we chose this seed %i "), seed.GetInitialSeed() , seed.GetCurrentSeed()));
	
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Ball 1: %i  , Ball 2: %i  , Ball 3: %i  , "), obj1, obj2, obj3));

	//Maze Starting point (0,0)
	OriginalLocation = GetActorLocation();

	//Default Parameters for spawning.
	FRotator TileRotation = FRotator(0, 0, 0);

	FActorSpawnParameters spawnParams;
	
	//Spawning of the maze!
	for (int i = 0; i < NumberMeshesX; i++)//X number of Meshes to spawn
	{
		for (int j = 0; j < NumberMeshesY; j++)//Y number of Mesh to spawn
		{
			//Spawning location for our tile.
			FVector TileLocation = FVector(OriginalLocation.X + (i * MeshWidth),OriginalLocation.Y + (j * MeshLength), OriginalLocation.Z);

			//Spawning Method
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
	FActorSpawnParameters spawnParams;//Default params
	
	//Counts the number of tiles spawned.
	count++;

	//Spawning Objectives.
	if (obj1 == count) {
		//Where to spawn
		FVector BallLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z + 250);

		//Ball we spawning
		GetWorld()->SpawnActor<AObjective>(Ball, BallLocation, SpawnRotation, spawnParams);
	}

	if (obj2 == count) {
		//Where to spawn
		FVector BallLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z + 250);

		//Ball we spawning
		GetWorld()->SpawnActor<AObjective>(Ball, BallLocation, SpawnRotation, spawnParams);
	}

	if (obj3 == count) {
		//Where to spawn
		FVector BallLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z + 250);

		//Ball we spawning
		GetWorld()->SpawnActor<AObjective>(Ball, BallLocation, SpawnRotation, spawnParams);
	}

	
	//We will now start to fill Up the row, adding one tile each time the Spawn method is called.
	if (tileNum < (NumberMeshesY - 1))
	{
		//Number of tiles for the row.
		tileNum++;
		
		//Spawn Tile
		SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(BaseFloor, SpawnLocation, SpawnRotation, spawnParams);//Tile we spawning

		//Add the object in an array, which will be our row.
		TileRow.Add(SpawnedObject);
		
	}

	//After finishing adding the row, this will start splitting them into groups.
	if(tileNum == (NumberMeshesY - 1)) {
		tileNum = -1;
		
		//Measure of splitting, if maze is higher than 20 we will be splitting more.
		if (NumberMeshesX <= 20) {
			//How long is going to be the split.
			splitNum = seed.RandRange(2, (NumberMeshesY / 2)); //How long is the split.	

			//Chose a random index location for our current split.
			indexNum = seed.RandRange(1, (NumberMeshesY - splitNum - 1));	

		}
		else if(NumberMeshesX > 20) {
			splitNum = seed.RandRange(3, (NumberMeshesY / 3)); 
				
			splitNum2 = splitNum;
		
			indexNum = seed.RandRange(1, (NumberMeshesY / 3) - 1);	
				
		}

		//This is another array, it will keep track the starting index of the splits
		indexBeginAndEndSplits.Add(indexNum);
				
		//Keep splitting until the length reaches 0.
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

		//Same Array but this time we keep track the ending index of our current split.
		indexBeginAndEndSplits.Add((indexNum - 1));


		//Since we know the start and end points of our split, we can now make them into a group.
		for (int j = indexBeginAndEndSplits[0]; j <= indexBeginAndEndSplits[1]; j++) {//Join them together
			
			if (TileRow[j]->split == true) {
				//Destroying walls here to join them together	
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

		//Start of second split, will not do this if maze is smaller than 20 tiles, same process as first split.
		//====================================================
		if (NumberMeshesX > 20) {
						
			indexNum2 = seed.RandRange(indexNum, (NumberMeshesY - 1 - splitNum2));

			//Being split 2, keeping track of beginning index.
			indexBeginAndEndSplits.Add(indexNum2);

			//Second split
			while (splitNum2 > 0) {
							
				if (TileRow[indexNum2]->split == false) {

					TileRow[indexNum2]->split = true;

					indexNum2++;
				}
				splitNum2--;

			}

			//End of split, keeping track of ending index.
			indexBeginAndEndSplits.Add((indexNum2 - 1));

			//Group up second split
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
		//End Second split


		//After split, rest of tiles that weren't selected for the split become their own groups.
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

		//This part of code starts after we make first row, since we will now be extending. Making gaps between the rows. Extension part 2, check part 1 first!
		if (prevRow == true ) {
			//We will now check all the index numbers
			for (int i = 0; i < (extendedTilesIndex.Num()); i++)
			{					
				TileRow[extendedTilesIndex[i]]->DestroyWalls(4);			
			}
			
			//We have finished the extension, we will now reset the indexes we are tracking.
			if (extended == false) {
				extendedTilesIndex.Empty();
			}
		}
		else {//Doing this to avoid first row.
			prevRow = true;
		}				
	
		//Extension part 1
		ExtendA = 1;
		while (ExtendA > 0) {//Current Row. Extend the tile

			//Randomly pick a Tile INSIDE SetA.
			a = seed.RandRange(indexBeginAndEndSplits[0], indexBeginAndEndSplits[1]);
					
			//First Extension! Tile INSIDE SetA
			if (TileRow[a]->E == true) {

				if (X != (NumberMeshesX - 1)) {
					TileRow[a]->DestroyWalls(3);
				}

				if (X != 0) {
					TileRow[a]->DestroyWalls(4);
				}

				//This array tracks the tiles who are extending, so the next row can use it.
				extendedTilesIndex.Add(a);			
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
						b = seed.RandRange(indexBeginAndEndSplits[2], indexBeginAndEndSplits[3]);//Second set

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
						c = seed.RandRange((indexBeginAndEndSplits[1] + 1), (TileRow.Num() - 1));//Tile AFTER SetB

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

			ExtendA--;				
		}						

		//Makes final row no walls
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
	for (int i = 0; i < (TileRow.Num()); i++)
	{
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

