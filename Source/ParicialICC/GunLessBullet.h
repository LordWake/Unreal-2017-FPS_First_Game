

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "GunLessBullet.generated.h"

UCLASS()
class PARICIALICC_API AGunLessBullet : public AActor
{
	GENERATED_BODY()
	
public:	

	AGunLessBullet();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * deadParticle;

	UPROPERTY(EditAnywhere)
		float bulletSpeed;
		float deadtimer;


protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void MoveThisBullet(float deltaTimer);
	void CheckLifeTime(float deltaTimer);

	UFUNCTION(BlueprintCallable)
		void DestroyThisBullet();
	UFUNCTION(BlueprintCallable)
		void CheckCollision(AActor * checkIfDrone, AActor * checkIfTurret, AActor *checkIfGroundDrone, AActor *checkIfPlayerBullet);
	
};
