// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TileIndexWidget.generated.h"

class ABasicFloor;

/**
 * 
 */
UCLASS()
class MAZE_API UTileIndexWidget : public UUserWidget
{
	GENERATED_BODY()

public:
		UPROPERTY(BlueprintReadWrite)
		ABasicFloor* Tile;
	
};
