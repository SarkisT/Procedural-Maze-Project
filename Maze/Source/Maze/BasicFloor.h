// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicFloor.generated.h"

UCLASS()
class MAZE_API ABasicFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicFloor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FloorTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeshWidth = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeshLength = 300.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};