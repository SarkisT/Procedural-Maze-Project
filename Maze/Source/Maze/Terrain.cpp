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

}


void ATerrain::Spawn(int X, int Y, FVector SpawnLocation, FRotator SpawnRotation)
{

	FActorSpawnParameters spawnParams;//Default params
	//int n = FMath::RandRange(0, 3);//Random pick on what we gonna spawn
		SpawnedObject = GetWorld()->SpawnActor<ABasicFloor>(BaseFloor, SpawnLocation, SpawnRotation, spawnParams);//Tile we spawning

		TArray<UStaticMeshComponent*> StaticComps;
		SpawnedObject->GetComponents(StaticComps);//Get the floor and walls.



	//if (spawned == true) {//Doing this to avoid the first spawn, since I'm gonna check the previous tile.
			
			//ABasicFloor* PreviousObject = SpawnedObject;//The last tile that got spawned

			//TArray<UStaticMeshComponent*> PrevComps;
			//PreviousObject->GetComponents(PrevComps);//Get it's walls.

			//PrevComps[1]->DestroyComponent();
			//PrevComps[2]->DestroyComponent();
			//PrevComps[3]->DestroyComponent();
			//PrevComps[4]->DestroyComponent();


	//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Blue, FString::Printf(TEXT("X %i , Y %i"), &NumberMeshesX, &NumberMeshesY));
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, FString::Printf(TEXT("X %i , MeshesX %i"), X, NumberMeshesX));
	
		/*
		if(X == 0 && Y == 0) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed walls of X %i , Y %i"), X, Y));
			//StaticComps[3]->DestroyComponent();
			//StaticComps[2]->DestroyComponent();
		}
		else if (X == 0 && Y == 1) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed walls of X %i , Y %i"), X, Y));
			//StaticComps[3]->DestroyComponent();
			//StaticComps[1]->DestroyComponent();
		}
		else if (X == 1 && Y == 0) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed walls of X %i , Y %i"), X, Y));
			//StaticComps[4]->DestroyComponent();
			//StaticComps[2]->DestroyComponent();
		}
		else if (X == 1 && Y == 1) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed walls of X %i , Y %i"), X, NumberMeshesX));
			//StaticComps[4]->DestroyComponent();
			//StaticComps[1]->DestroyComponent();
		}
		else if (X == (NumberMeshesX - 1)) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed Last line of X")));
			//StaticComps[4]->DestroyComponent();
		}
		else if (Y == (NumberMeshesY - 1)) {
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Destroyed Last line of Y")));
			//StaticComps[3]->DestroyComponent();
		}
		*/
	//}
	
	/*
	if (NumberMeshesX > NumberMeshesY) {
		for (int i = 0; i < (NumberMeshesX - 1);i++)
		{
			TileRow[i] = SpawnedObject;
		}
	}
	else if (NumberMeshesY > NumberMeshesX) {
		if (tileNum < 1)// (NumberMeshesY - 1))//We start at 0, then reach the corner.
		{
			TileRow.Add(SpawnedObject);//Add a tile to row
			tileNum++;
		}
	}

	*/

	if(NumberMeshesX == NumberMeshesY){
		
		if (tileNum < NumberMeshesY)		//ROW BEING ADDED
		{
			TileRow.Add(SpawnedObject);
			tileNum++;
		}									//ROW ADD ENDS

		else {//After we done with adding the row. Time to split it

			int setNumber = 1;

			if (setNumber == 1) {


				int indexNum = FMath::RandRange(0, (tileNum / 2));	//Starting index of split (RANDOM)

				for (int splitNum = FMath::RandRange(1, (tileNum / 2)); splitNum > 0; splitNum--)						//SPLIT, RANDOM AMOUNT OF TILES (1 to HALF)
				{
					if (indexNum <  (TileRow.Num() - 1)) {
						GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Yellow, FString::Printf(TEXT("TileRow Array Last Index %i , Currently at index : %i , TILENUM %i , X %i , Y %i "), (TileRow.Num() - 1), indexNum, tileNum, X, Y));//Seems good.

						TileRow[indexNum]->GetComponents(ObjComps);//Current tile component.
						
						if (TileRow.IsValidIndex(indexNum)) {
							ObjComps[2]->DestroyComponent();
							ObjComps[3]->DestroyComponent();
							ObjComps[4]->DestroyComponent();

							SetA.Add(TileRow[indexNum]);//This is part of a set
							TileRow.RemoveAt(indexNum);	//Remove, as we moved it into SetA. //Not moving  array, just leave it null for now.
							
						}
						else {
							GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Black, FString::Printf(TEXT("SET HAS ERROR!!!!!!"), (TileRow.Num() - 1), indexNum, tileNum));//Seems good.
							
						}

				
					}
					else {
						GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, FString::Printf(TEXT("HAD TO GO NEGATIVE!!!"), (TileRow.Num() - 1), indexNum, tileNum));//Seems good.

						splitNum = -1;
					}
				}//SPLIT DONE. Check rest of  the row now.
				//(TileRow.Num() - 1)<= tileNum
				for (int p = 0; p < (TileRow.Num() - 1); p++)
				{

					GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Emerald, FString::Printf(TEXT("P %i , TILEROW NUM %i , TILENUM %i"), p, (TileRow.Num() - 1), tileNum));
					
					TileRow[p]->GetComponents(ObjComps);//Current tile component.

					if (TileRow.IsValidIndex(p)) {
						ObjComps[1]->DestroyComponent();
						ObjComps[2]->DestroyComponent();
						ObjComps[3]->DestroyComponent();
						ObjComps[4]->DestroyComponent();
						//TileRow.RemoveAt(p);
						GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Blue, FString::Printf(TEXT("Removed %i "), p));//Seems good.

					} else{
						GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Red, FString::Printf(TEXT("INVALID")));

					}
					//TileRow.RemoveAt(p);
				}
					TileRow.Empty();//We done this whole row. Going next row now. RESET.
					tileNum = -1;

				//	GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Purple, FString::Printf(TEXT("Reset!!!!!!!!!!! %i "), (TileRow.Num() - 1)));//Seems good.

				
				//TileRow.Remove();
				//tileNum = 0;



















































			}else if (setNumber == 2) {
				int indexNum = rand() % (tileNum / 3);	//Starting index of split
				int splitNum = rand() % ((tileNum / 3) + 1); //Length of split

			}
			else if (setNumber == 3) {

			}
		}

		//After we completed the row.
	}


	












	/*
		if (X == 0) {//CORNERS
			StaticComps[3]->DestroyComponent();
			if (Y == 0) {								 //0 - 0
				//StaticComps[1]->DestroyComponent();
				//StaticComps[4]->DestroyComponent();
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
		
	spawned = true;

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
			//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("NUMBER: %i"), i));
		//}
}

