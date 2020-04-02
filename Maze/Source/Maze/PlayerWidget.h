// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Terrain.h"
#include "PlayerWidget.generated.h"

UCLASS()
class MAZE_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere)
	TSubclassOf<ATerrain> maze;
	int Timer;

	UFUNCTION(BluePrintCallable)
	void ChangeNoMeshes(int numberofX, int numberofY);

	UFUNCTION(BluePrintCallable)
	void ChangeTimer(int timer);

	UFUNCTION(BluePrintCallable)
	void StartGame();

};
