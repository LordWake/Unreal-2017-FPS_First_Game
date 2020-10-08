// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMenuUI.h"

void AMyMenuUI::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = false;

	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);
	if (canvas)
		canvas->AddToViewport();
}

void AMyMenuUI::StartGame()
{
	canvas->aButtonPressed = true;
}

void AMyMenuUI::ShowCredits()
{
	canvas->yButtonPressed = true;
}

void AMyMenuUI::ShowHowToPlay()
{
	canvas->xButtonPressed = true;
}

void AMyMenuUI::BackButtonPressed()
{
	canvas->backButtonPressed = true;
}


