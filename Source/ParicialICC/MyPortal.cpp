

#include "MyPortal.h"


AMyPortal::AMyPortal()
{

	PrimaryActorTick.bCanEverTick = true;

}


void AMyPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPortal::ChangeLevel()
{
	if (toLevel2)
	{
		auto myManagerUI = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
		myManagerUI->CheckIfPlayerWin(1);
	}
	else if (toLevel3)
	{
		auto myManagerUI = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
		myManagerUI->CheckIfPlayerWin(2);
	}
}

