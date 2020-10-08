// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "PlayerBullet.generated.h"

UCLASS()
class PARICIALICC_API APlayerBullet : public AActor
{
	GENERATED_BODY()
	
public:	

	APlayerBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * deadParticle;

	UPROPERTY(EditAnywhere)
		float bulletSpeed;
	UPROPERTY(EditAnywhere)
		float timeToDead;

		float deadTimer;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	void MoveThisBullet(float deltaTimer);
	void CheckLifeTime(float deltaTimer);
	UFUNCTION(BlueprintCallable)
		void DestroyThisBullet();
	UFUNCTION(BlueprintCallable)
		void CheckCollision(AActor * actorCheck);
	
	
};
