// Fill out your copyright notice in the Description page of Project Settings.

#include "MyVictoryUI.h"

void AMyVictoryUI::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);
	if (canvas)
		canvas->AddToViewport();
}

void AMyVictoryUI::StartGame()
{
	canvas->aButtonPressed = true;
}


