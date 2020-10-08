// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "EnemyBullet.h"
#include "GameFramework/Actor.h"
#include "GroundDrone.generated.h"

UCLASS()
class PARICIALICC_API AGroundDrone : public AActor
{
	GENERATED_BODY()
	
public:

	AGroundDrone();

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

	UPROPERTY(BlueprintReadWrite)
		bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float enemyLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float distanteToPlayer;

	float moveTimer;
	float shotTimer;
	int xDirection;

	FVector socketLocation;
	FRotator socketRotation;

	UStaticMeshComponent* myMesh;

	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemyBullet> prefabBullet;

protected:

	virtual void BeginPlay() override;

	bool playerIsNear;

public:

	virtual void Tick(float DeltaTime) override;
	void MoveThisEnemy(float myTimer);
	void Shoot(float deltaTimer);
	void CheckEnemyLife();

	UFUNCTION(BlueprintCallable)
		void TakeEnemyDamage(float damage);
	UFUNCTION(BlueprintCallable)
		void CheckDistanceToPlayer(float distance);
	
	
};
