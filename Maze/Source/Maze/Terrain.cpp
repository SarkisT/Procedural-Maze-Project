// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain.h"
#include "Engine.h"
#include <random>
#include "BasicFloor.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("CurrentFloor not NULL"));
	//UWorld* const World = GetWorld();

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("World not NULL, SPAWN PLEASE"));
			
		//GetWorld()->SpawnActor<ABasicFloor>(CurrentFloor, TileLocation, TileRotation, spawnParams);
	

}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	//seed = srand(rand(0, 30000));
	//seed = srand(time(0));
	//FVector TileLocation = FVector(0, 0, 0);

	OriginalLocation = GetActorLocation();

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, OriginalLocation.ToString());
	FRotator TileRotation = FRotator(0, 0, 0);
	//Spawn(OriginalLocation, TileRotation);
	
	FActorSpawnParameters spawnParams;


	for (int i = 0; i < NumberMeshesX; i++)//X number of Meshes to spawn
	{
		for (int j = 0; j < NumberMeshesY; j++)//Y number of Mesh to spawn
		{
			FVector TileLocation = FVector(OriginalLocation.X + (i * MeshWidth),OriginalLocation.Y + (j * MeshLength), OriginalLocation.Z);//Where to spawn

			FRotator TileRotation = FRotator(0,0, 0);
			FActorSpawnParameters spawnParams;

			Spawn(i, j, TileLocation, TileRotation);//Spawn Method

		}

	}
	
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("BLOCKS: %i"), blocksSpawned));
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("WALLS: %i"), redWalls));
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Silver, FString::Printf(TEXT("TILES: %i"), emptyTiles));
}


void ATerrain::Spawn(int X, int Y, FVector SpawnLocation, FRotator SpawnRotation)
{
	FActorSpawnParameters spawnParams;//Default params

	



	if(NumberMeshesX == NumberMeshesY){// If 5 x 5, 10 x 10, etc.//For some reason. 0 has red wall. final tile is full walled.
		
		if (tileNum < (NumberMeshesY - 1))		//ROW BEING ADDED.
		{
			blocksSpawned++;
			tileNum++;
			
			SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(BaseFloor, SpawnLocation, SpawnRotation, spawnParams);//Tile we spawning
			SpawnedObject->HP = tileNum;

			TArray<UStaticMeshComponent*> StaticComps;
			SpawnedObject->GetComponents(StaticComps);//Get the floor and walls.
			TileRow.Add(SpawnedObject);//Add this to array.//0,1,2,3,4,

			/*
			if (X == 0) {//CORNERS
				//SpawnedObject->DestroyWalls(1);
				//SpawnedObject->DestroyWalls(2);//3
				SpawnedObject->DestroyWalls(3);
				//SpawnedObject->DestroyWalls(4);
				if (Y == 0) {								 //0 - 0
					//SpawnedObject->DestroyWalls(2);//2

				}
				else if (Y == (NumberMeshesY - 1)) {	    //0 - 1
					//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed Last line of Y")));
					SpawnedObject->DestroyWalls(1);
					SpawnedObject->DestroyWalls(2);
				}
			}
			else if (X == (NumberMeshesX - 1)) {
				//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed Last line of X")));		
				SpawnedObject->DestroyWalls(4);
				if (Y == (NumberMeshesY - 1)) {				//1 - 1	
					SpawnedObject->DestroyWalls(1);
				}
				else if (Y == 0) {							//1 - 0
					//SpawnedObject->DestroyWalls(2);
				}
			}
			*/



			
		//	GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Black, FString::Printf(TEXT("Tile index is  %i"), SpawnedObject->HP));//Seems good.

			
		}

		if(tileNum == (NumberMeshesY - 1)) {//After we done with adding the row. Time to split it
			tileNum = -1;
			int setNumber = 1;//The amount of times we are planning to split it. Will be randomized

			
			if(setNumber == 1){ //This will be a case. And this is 1 split.
				//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, FString::Printf(TEXT("TileRow     %i"), (TileRow.Num() - 1)));
				int splitNum = FMath::RandRange(2, (NumberMeshesY / 2));//How long is the split.						//SPLIT, RANDOM AMOUNT OF TILES (1 to HALF)
				int indexNum = FMath::RandRange(0, (NumberMeshesY - splitNum - 1));	//Starting index of row array to split (RANDOM)
				

					//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Yellow, FString::Printf(TEXT("TileRow Array Last Index %i , Currently at index : %i , TILENUM %i , X %i , Y %i "), (TileRow.Num() - 1), indexNum, tileNum, X, Y));//Seems good.
				
				indexBeginAndEndSplits.Add(indexNum);//Begin of the split. Keeping track of it.
				
					while(splitNum > 0) {
						TileRow[indexNum]->GetComponents(ObjComps);//Current tile component.

						
						if (TileRow[indexNum]->split == false) {//DON'T TOUCH ANYTHING HERE YET.!!!!!!!!!!!!!!!!
							
							redWalls++;
							//++indexNum;
							SetA.Add(TileRow[indexNum]);//This is part of a set
						
							TileRow[indexNum]->split = true;
							//TileRow.RemoveAtSwap(indexNum, 1, true);
							indexNum++;
						}
						else{
							
							GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Black, FString::Printf(TEXT("SPLIT is TRUE ERROR   %i"), indexNum));//Seems good.
						}
						//indexNum++;
						splitNum--;

					} 

					indexBeginAndEndSplits.Add((indexNum - 1));//End of the split. Keeping track of it.
			
					for (int j = indexBeginAndEndSplits[0]; j <= indexBeginAndEndSplits[1]; j++) {// First split group, Join them together
						if (TileRow[j]->split == true) {
							TileRow[j]->GetComponents(ObjComps);

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

					
					/*//WORKING SPLIT!!================================================================================================================================
					for (int j = 0; j < SetA.Num(); j++) {// First split group, Join them together
						if (SetA[j]->split == true) {
							SetA[j]->GetComponents(ObjComps);

							if (j == 0) {
								SetA[j]->DestroyWalls(2);
							}
							else if (j > 0 && j < (SetA.Num() - 1)) {
								SetA[j]->DestroyWalls(1);
								SetA[j]->DestroyWalls(2);
							}
							else {
								SetA[j]->DestroyWalls(1);
							}
						}
					}
					*///===============================================================================================================================================

					//After split, Rest of tiles become it's own group.
					for (int i = 0; i < TileRow.Num(); i++)
					{
						if (TileRow[i]->split == false) {
							//TileRow[i]->HP = i;
							count++;
							
							TileRow[i]->GetComponents(ObjComps);

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
								//TileRow[i]->DestroyWalls(2);
								//TileRow[i]->DestroyWalls(3);
								//TileRow[i]->DestroyWalls(4);
							//	ObjComps[1]->DestroyComponent();
							}

							//SetB.Add(TileRow[i]);
							//TileRow[i]->split = true;


							if (i == (TileRow.Num() - 1)) {//This makes sure the the end of the row is not isolated.
								if (count % 2 == 1) {
									if (X > 0 && Y < (NumberMeshesY - 1)) {//3, 4
										//TileRow[i]->DestroyWalls(1);
										//TileRow[i]->DestroyWalls(2);
										//TileRow[i]->DestroyWalls(3);
										//TileRow[i]->DestroyWalls(4);
									}
								}
							}					

						}
					}

					

					if (prevRow == true ) {//This happens when we have already made our first row.//Put omsething here for last row.

						for (int i = 0; i < (extendedTilesIndex.Num()); i++)
						{
							p = extendedTilesIndex[i];
							GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, FString::Printf(TEXT("extendedTiles index  %i , Amount total %i , Value of P %i "), i, (extendedTilesIndex.Num() - 1), p));//Seems good.
							//TileRow[p]->DestroyWalls(3);
							TileRow[p]->DestroyWalls(3);
							//TileRow[p]->DestroyWalls(3);
							
							TileRow[p]->GetComponents(ObjComps);
							//ObjComps[0]->DestroyComponent();
							//TileRow[p]->DestroyWalls(3);//
							//TileRow[p]->DestroyWalls(4);
							//ObjComps[1]->DestroyComponent();
							//ObjComps[2]->DestroyComponent();
							//ObjComps[3]->DestroyComponent();
							//ObjComps[4]->DestroyComponent();
					
							

						}
						GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Yellow, FString::Printf(TEXT("ROW CHECK ENDED ")));//Seems good.

						if (extended == false) {
							extendedTilesIndex.Empty();
						}
					}
					else {
						prevRow = true;
					}

					
					//Random extensions, Let's change that.
					ExtendA = 1;//rand() % 2 + 2;//Extend tiles. Make some connections between rows. Must have at least 2
					while (ExtendA > 0 && extended == false) {
						a = FMath::RandRange(indexBeginAndEndSplits[0], indexBeginAndEndSplits[1]);//Randomly pick a Tile INSIDE SetA.
						
						//if (X != (NumberMeshesX - 1)) {//
						
						if (TileRow[a]->W == true) {
							//TileRow[a]->DestroyWalls(4);
						}
						else {
							//do {
								a = FMath::RandRange(indexBeginAndEndSplits[0], indexBeginAndEndSplits[1]);//Randomly pick a Tile INSIDE SetA.
							//} while (TileRow[a]->W == false);

							GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Blue, FString::Printf(TEXT("Wall is already destroyed from A %i"), a));//Seems good.

							//TileRow[a]->DestroyWalls(4);
						}

						if (indexBeginAndEndSplits[0] != 0) {
							n = FMath::RandRange(0, (indexBeginAndEndSplits[0] - 1));
							TileRow[n]->DestroyWalls(4);
							extendedTilesIndex.Add(n);
						}
						else {
							//do {
								//n = FMath::RandRange(0, indexBeginAndEndSplits[0]);

							//} while (TileRow[n]->W == false || n != 0);
							GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Blue, FString::Printf(TEXT("Wall is already destroyed from N %i"), n));//Seems good.

							//TileRow[n]->DestroyWalls(4);
						}


						if (indexBeginAndEndSplits[1] != (TileRow.Num() - 1)) {
							c = FMath::RandRange((indexBeginAndEndSplits[1] + 1), (TileRow.Num() - 1));
							TileRow[c]->DestroyWalls(4);
							extendedTilesIndex.Add(c);
						}
						else {
							//do {
							//	c = FMath::RandRange(indexBeginAndEndSplits[1], (TileRow.Num() - 1));
							//} while (TileRow[c]->W == false || c != (TileRow.Num() - 1));

							GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Blue, FString::Printf(TEXT("Wall is already destroyed from C %i"), c));//Seems good.

							//TileRow[c]->DestroyWalls(4);
						}
						

						extendedTilesIndex.Add(a);//Randomly pick a Tile INSIDE SetA.
			
						//extendedTilesIndex.Add(c);
						//}//
						ExtendA--;
					

					}
					
					

				

					extended = false;
					indexBeginAndEndSplits.Empty();

					TileRow.Empty();
					SetA.Empty();
					

					//TileRow.Empty();
						//else {
							//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Black, FString::Printf(TEXT("SET HAS ERROR!!!!!!"), (TileRow.Num() - 1), indexNum, tileNum));//Seems good.
							
						//}

				
					//}
					//else {
					//	GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, FString::Printf(TEXT("HAD TO GO NEGATIVE!!!"), (TileRow.Num() - 1), indexNum, tileNum));//Seems good.

					//	splitNum = 1; // - 1
					//}
				//}//SPLIT DONE. Check rest of  the row now.
				//(TileRow.Num() - 1)<= tileNum
				
				
				
				
				
				/*
				do//for (int p = 0; p < (TileRow.Num()); p++) // - 1
				{

				//	GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Emerald, FString::Printf(TEXT("P %i , TILEROW NUM %i , TILENUM %i"), p, (TileRow.Num() - 1), tileNum));
					
					TileRow[p]->GetComponents(ObjComps);//Current tile component.

					if (TileRow.IsValidIndex(p)) {
						ObjComps[1]->DestroyComponent();
						ObjComps[2]->DestroyComponent();
						ObjComps[3]->DestroyComponent();
						ObjComps[4]->DestroyComponent();
						emptyTiles++;
						p++;
						//TileRow.RemoveAt(p);
						//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Blue, FString::Printf(TEXT("Removed %i "), p));//Seems good.
						//TileRow.RemoveAtSwap(p, 1, true);

					} else{
						GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, FString::Printf(TEXT("INVALID")));

					}
					TileRow.RemoveAt(p);
				} while (p < (TileRow.Num() - 1));

				*/
				//TileRow.Empty();//We done this whole row. Going next row now. RESET.
				//tileNum = -1;

					//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Purple, FString::Printf(TEXT("Reset!!!!!!!!!!! %i , %i"), (TileRow.Num() - 1), tileNum));//Seems good.

				
				//TileRow.Remove();
				//tileNum = 0;
			

			}
			else if (setNumber == 2) {

				int splitNum = FMath::RandRange(2, (NumberMeshesY / 2));//How long is the split.						//SPLIT, RANDOM AMOUNT OF TILES (1 to HALF)
				int indexNum = FMath::RandRange(0, (NumberMeshesY - splitNum - 1));	//Starting index of row array to split (RANDOM)


			


				while (splitNum > 0) {
					TileRow[indexNum]->GetComponents(ObjComps);//Current tile component.


				if (TileRow[indexNum]->split == false) {

					SetA.Add(TileRow[indexNum]);
					
					TileRow[indexNum]->split = true;

					indexNum++;
				}
				else {

					GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Black, FString::Printf(TEXT("SPLIT is TRUE ERROR   %i"), indexNum));//Seems good.
				}
				splitNum--;

			}


			for (int j = 0; j < SetA.Num(); j++) {// First split group, Join them together
				if (SetA[j]->split == true) {
					SetA[j]->GetComponents(ObjComps);

					if (j == 0) {
						SetA[j]->DestroyWalls(2);
					}
					else if (j > 0 && j < (SetA.Num() - 1)) {
						SetA[j]->DestroyWalls(1);
						SetA[j]->DestroyWalls(2);
					}
					else {
						SetA[j]->DestroyWalls(1);
					}
				}
			}

			//After split, Rest of tiles become it's own group.
			for (int i = 0; i < TileRow.Num(); i++)
			{
				if (TileRow[i]->split == false) {
					//TileRow[i]->HP = i;
					count++;

					TileRow[i]->GetComponents(ObjComps);

					if (i == 0) {
						TileRow[i]->DestroyWalls(2);
					}
					else if (i > 0 && i < (TileRow.Num() - 1)) {
						TileRow[i]->DestroyWalls(1);
						TileRow[i]->DestroyWalls(2);
					}
					else {
						TileRow[i]->DestroyWalls(1);
						//	ObjComps[1]->DestroyComponent();
					}

					//SetB.Add(TileRow[i]);
					//TileRow[i]->split = true;


					if (i == (TileRow.Num() - 1)) {//This makes sure the the end of the row is not isolated.
						if (count % 2 == 1) {
							if (X > 0 && Y < (NumberMeshesY - 1)) {
								TileRow[i]->DestroyWalls(3);
								TileRow[i]->DestroyWalls(4);
							}
						}
					}

				}
			}

			if (prevRow == true) {//This happens when we have already made our first row.

				for (int i = 0; i < (extendedTilesIndex.Num() - 1); i++)
				{
					GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Black, FString::Printf(TEXT("extendedTiles index  %i"), extendedTilesIndex[i]));//Seems good.
					TileRow[extendedTilesIndex[i]]->DestroyWalls(4);
				}
				if (extended == false) {
					extendedTilesIndex.Empty();
				}
			}
			else {
				prevRow = true;
			}



			ExtendA = rand() % (NumberMeshesX / 2) + 1;//Extend tiles. Make some connections between rows.
			while (ExtendA > 0 && extended == false) {
				 n = rand() % (TileRow.Num() - 1);
				 a = rand() % (SetA.Num() - 1);

				extendedTilesIndex.Add(n);
				extendedTilesIndex.Add(a);

				//if (X != (NumberMeshesX - 1)) {//
				TileRow[n]->DestroyWalls(3);
				SetA[a]->DestroyWalls(3);
				//}//
				ExtendA--;


			}





			extended = false;

			TileRow.Empty();
			SetA.Empty();


			}
			//else if (setNumber == 2) {
			
		}
		
		//After we completed the row.
	}


	












		/*
		if (X == 0) {//CORNERS
			StaticComps[3]->DestroyComponent();
			if (Y == 0) {								 //0 - 0
				StaticComps[2]->DestroyComponent();
			}
			else if (Y == (NumberMeshesY - 1)) {	    //0 - 1
				//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed Last line of Y")));
				StaticComps[1]->DestroyComponent();
			}
		}
		else if (X == (NumberMeshesX - 1)) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed Last line of X")));
			StaticComps[4]->DestroyComponent();
			if (Y == (NumberMeshesY - 1)) {				//1 - 1	
				StaticComps[1]->DestroyComponent();
			}
			else if (Y == 0) {							//1 - 0
				StaticComps[2]->DestroyComponent();
			}
		}
		*/
		
	//spawned = true;

	//StaticComps[4]->SetActive(false);
	//StaticComps[4]->DestroyComponent();
	//StaticComps[3]->DestroyComponent();
	//StaticComps[2]->DestroyComponent();
	//StaticComps[1]->DestroyComponent();
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

			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red,(TEXT("NUMBER: %s"), StaticComps[i]->GetName()));

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, SpawnLocation.ToString());

			//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, FString::Printf(TEXT("TILE NUM %i , TILE ARRAY LENGTH %i, Y %i , X %i"), tileNum, (TileRow.Num() - 1), NumberMeshesY, NumberMeshesX));
			//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Yellow, FString::Printf(TEXT("TileRow Array Last Index %i , indexNum %i "), (TileRow.Num() - 1), tileNum));

	//indexNum++;
						//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Yellow, FString::Printf(TEXT("TileRow Array Last Index %i , SplitNum %i , indexNum %i , TILENUM %i"), (TileRow.Num() - 1), splitNum, indexNum, tileNum));//Seems good.


	//NORTH = 1
		//SOUTH = 2
		//EAST = 3
		//WEST = 4
		//for (int i = 1; i < StaticComps.Num(); i++)//This was how I check my walls order.
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, FString::Printf(TEXT("NUMBER: %i"), i));

			//FString name = FString::Printf(TEXT("%s"),StaticComps[i]->GetName());
			//FString name = StaticComps[i]->GetName();
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red,(TEXT("NUMBER: %s"), StaticComps[i]->GetName()));
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::Printf("NAME " + name + " ok"));
			//FString::Printf(TEXT("NUMBER: %i"), i));
			//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("BLOCKS: %i"), blocksSpawned));
		//}

}

void ATerrain::ClearFinalRow(TArray<ABasicFloor*> row)
{
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

