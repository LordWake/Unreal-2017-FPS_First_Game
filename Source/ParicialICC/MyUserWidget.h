// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PARICIALICC_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float playerHUDlife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float playerWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool myPlayerIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool myPlayerWin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool myPlayerWinTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool myPlayerWinThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool aButtonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool xButtonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool yButtonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool backButtonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool resetThisLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool resetSecondLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool resetThirdLevel;
	
	
};
