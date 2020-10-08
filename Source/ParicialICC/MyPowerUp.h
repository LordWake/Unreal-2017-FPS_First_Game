
#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "MainPlayer.h"
#include "GameFramework/Actor.h"
#include "MyPowerUp.generated.h"

UCLASS()
class PARICIALICC_API AMyPowerUp : public AActor
{
	GENERATED_BODY()
	
public:	

	AMyPowerUp();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int typeOfPowerUp;
	// 1 = Life, 2 = Shield, 3= Weapon.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * lifeBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * speedBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * weaponBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent * myGreenLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent * myRedLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent * myYellowLight;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void CheckMyBox();

	UFUNCTION(BlueprintCallable)
	void PlayerRequestPowerUp();	
};
