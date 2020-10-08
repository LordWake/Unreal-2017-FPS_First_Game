#include "MyPowerUp.h"


AMyPowerUp::AMyPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyPowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPowerUp::PlayerRequestPowerUp()
{
	if (typeOfPowerUp == 1)
	{
		auto myPlayer = Cast<AMainPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (myPlayer)
		{
			myPlayer->HealMyPlayer(20);
			Destroy(true);
		}
	}

	else if (typeOfPowerUp == 2)
	{
		auto myPlayer = Cast<AMainPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (myPlayer)
		{
			myPlayer->EnableShield();
			Destroy(true);
		}
	}

	else if (typeOfPowerUp == 3)
	{
		auto myPlayer = Cast<AMainPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (myPlayer)
		{
			myPlayer->EnableRifle();
			Destroy(true);
		}
	}
}

void AMyPowerUp::CheckMyBox()
{
	if (typeOfPowerUp == 1)
	{
		speedBox->DestroyComponent(true);
		weaponBox->DestroyComponent(true);
		myYellowLight->SetVisibility(false);
		myRedLight->SetVisibility(false);
	}

	else if (typeOfPowerUp == 2)
	{
		lifeBox->DestroyComponent(true);
		weaponBox->DestroyComponent(true);
		myGreenLight->SetVisibility(false);
		myRedLight->SetVisibility(false);
	}

	else if (typeOfPowerUp == 3)
	{
		lifeBox->DestroyComponent(true);
		speedBox->DestroyComponent(true);
		myGreenLight->SetVisibility(false);
		myYellowLight->SetVisibility(false);
	}
}
