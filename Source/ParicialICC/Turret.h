// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EnemyBullet.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class PARICIALICC_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:

	ATurret();

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

	float shotTimer;
	FVector socketLocation;

	UStaticMeshComponent *myMesh;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemyBullet> prefabBullet;


protected:

	virtual void BeginPlay() override;

	bool playerIsNear;

public:

	virtual void Tick(float DeltaTime) override;
	void LookToPlayer();
	void Shoot(float deltaTimer);
	void CheckEnemyLife();

	UFUNCTION(BlueprintCallable)
		void TakeEnemyDamage(float damage);
	UFUNCTION(BlueprintCallable)
		void CheckDistanceToPlayer(float distance);
	
};
