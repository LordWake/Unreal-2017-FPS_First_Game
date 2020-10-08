

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "EnemyBullet.generated.h"

UCLASS()
class PARICIALICC_API AEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:

	AEnemyBullet();
	
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
		void CheckCollision(AActor *checkIfBoss, AActor * checkIfDrone, AActor * checkIfTurret, AActor *checkIfGroundDrone, AActor *playerBullet);

	
};
