// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

void UPlayerWidget::ChangeNoMeshes(int numberofX, int numberofY, int diff)
{
	maze.GetDefaultObject()->NumberMeshesX = numberofX;
	maze.GetDefaultObject()->NumberMeshesY = numberofY;
	maze.GetDefaultObject()->Difficulty = diff;
}

void UPlayerWidget::StartGame()
{
	
}
