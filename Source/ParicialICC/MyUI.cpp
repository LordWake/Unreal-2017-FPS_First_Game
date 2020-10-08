// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUI.h"

void AMyUI::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = false;

	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);
	if (canvas)
		canvas->AddToViewport();
}

void AMyUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckIfPlayerIsDead();
	ResetTheLevel();
}

void AMyUI::UpdatePlayerLife(float life)
{
	canvas->playerHUDlife = life; 
}

void AMyUI::UpdatePlayerWeapons(float weaponsValue)
{
	canvas->playerWeapons = weaponsValue;
}

void AMyUI::CheckIfPlayerIsDead()
{
	if (isDead)
		canvas->myPlayerIsDead = true;
}

void AMyUI::CheckIfPlayerWin(int levelWin)
{
	switch (levelWin)
	{
	case  1:
		canvas->myPlayerWin = true;
		break;

	case  2:
		canvas->myPlayerWinTwo = true;
		break;

	case  3:
		canvas->myPlayerWinThree = true;
		break;
	}
}

void AMyUI::ResetTheLevel()
{
	if (resetFirstLevel)
		canvas->resetThisLevel = true;
	else if (resetSecondLevel)
		canvas->resetSecondLevel = true;
	else if (resetThirdLevel)
		canvas->resetThirdLevel = true;

}




