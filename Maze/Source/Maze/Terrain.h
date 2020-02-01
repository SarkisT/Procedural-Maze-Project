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

	UPROPERTY(EditDefaultsOnly, Category = Floor)
	TSubclassOf<ABasicFloor> BaseFloor;

	UPROPERTY(EditDefaultsOnly, Category = Floor)
	TSubclassOf<ABasicFloor> wall1;
	UPROPERTY(EditDefaultsOnly, Category = Floor)
	TSubclassOf<ABasicFloor> wall2;
	UPROPERTY(EditDefaultsOnly, Category = Floor)
	TSubclassOf<ABasicFloor> wall3;
	UPROPERTY(EditDefaultsOnly, Category = Floor)
	TSubclassOf<ABasicFloor> wall4;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OriginalLocation;

	UFUNCTION(BluePrintCallable)
	void Spawn(int X, int Y, FVector SpawnLocation, FRotator SpawnRotation);


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
