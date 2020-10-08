// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EnemyBullet.h"
#include "MyUI.h"
#include "GameFramework/Actor.h"
#include "RupertBoss.generated.h"

UCLASS()
class PARICIALICC_API ARupertBoss : public AActor
{
	GENERATED_BODY()
	
public:
	ARupertBoss();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* damageAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* shotAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* explosionAudio;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* myMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * damageParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * shotParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * deadParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * onLevitate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * levitateFireParticleOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * levitateFireParticleTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* thisPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float enemyLife;

	UPROPERTY(BlueprintReadWrite)
		bool isDead;

	float moveTimer;
	float moveToSkyTimer;
	float shotTimer;
	int yDirection;
	FVector socketLocation;
	FRotator socketRotation;

	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
		float defaultSpeed;
	UPROPERTY(EditAnywhere)
		float levitationTimer;
	UPROPERTY(EditAnywhere)
		float coolDownBetweenBullets;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemyBullet> prefabBullet;

protected:
	virtual void BeginPlay() override;

	bool playerIsNear;
	bool firstStage;
	bool secondStage;
	bool thirdStage;
	bool setupDirection;
	bool stopChangeDirection;

public:
	virtual void Tick(float DeltaTime) override;
	void MoveThisEnemy(float myTimer);
	void MoveEnemyToSky(float myTimer);
	void LookToPlayer();
	void LookToPlayerWhenLevitate();
	void ChangeDirection();
	void Shoot(float deltatimer);
	void CheckEnemyLife();

	UFUNCTION(BlueprintCallable)
		void TakeEnemyDamage(float damage);
	UFUNCTION(BlueprintCallable)
		void CheckDistanceToPlayer(float distance);
};
