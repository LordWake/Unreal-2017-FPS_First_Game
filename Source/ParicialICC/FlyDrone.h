// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EnemyBullet.h"
#include "SlowBullet.h"
#include "GunLessBullet.h"
#include "GameFramework/Actor.h"
#include "FlyDrone.generated.h"

UCLASS()
class PARICIALICC_API AFlyDrone : public AActor
{
	GENERATED_BODY()
	
public:
	AFlyDrone();

	UPROPERTY(EditAnywhere)
		int typeOfDron;
	UPROPERTY(EditAnywhere)
		float timeToShot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* damageAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* shotAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* explosionAudio;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * damageParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * shotParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * deadParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float enemyLife;
	
	UPROPERTY(BlueprintReadWrite)
		bool isDead;

	float moveTimer;
	float shotTimer;
	int yDirection;

	FVector socketLocation;

	UStaticMeshComponent* myMesh;

	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemyBullet> prefabBullet;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASlowBullet> prefabSlowBullet;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGunLessBullet> prefabGunLessBullet;

protected:
	virtual void BeginPlay() override;

	bool playerIsNear;

public:
	virtual void Tick(float DeltaTime) override;
	void MoveThisEnemy(float myTimer);
	void LookToPlayer();
	void Shoot(float deltatimer);
	void CheckEnemyLife();

	UFUNCTION(BlueprintCallable)
		void TakeEnemyDamage(float damage);
	UFUNCTION(BlueprintCallable)
		void CheckDistanceToPlayer(float distance);

	
};
