// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "PlayerBullet.h"
#include "MyUI.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class PARICIALICC_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:

	AMainPlayer();

	float shotTimer;
	float rifleShotTimer;
	float shieldTimer;
	float rifleAvailableTimer;
	float waitForGuns;
	float waitForMove;

	FVector gunSocketLocation;
	FVector rifleSocketLocation;
	FRotator gunSocketRotation;
	FRotator rifleSocketRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float playerLife;
	UPROPERTY(EditAnywhere)
		float playerMaxLife;
	UPROPERTY(EditAnywhere)
		float myGunCoolDown;
	UPROPERTY(EditAnywhere)
		float myRifleCoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * gunMuzzle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent * rifleMuzzle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class APlayerBullet> prefabBullet;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class APlayerBullet> prefabRifleBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* myGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* myRifle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* myShield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* freezeShield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* rifleLaser;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* gunLaser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* damageAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* gunAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* rifleAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* powerUpAudio;

protected:

	virtual void BeginPlay() override;

	bool canShot;
	bool canShotRifle;
	bool playerIsDead;
	bool shieldActivated;
	bool rifleIsAvailable;
	bool gunLessActivated;
	bool freezePlayerActivated;

	UCameraComponent* myCamera;

	FVector position;
	FRotator viewRotation;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ResetLevelOne();
	void ResetLevelTwo();
	void ResetLevelThree();

	void MoveFront(float vertical);
	void MoveRight(float horizontal);

	void RotatePlayer(float rotation);
	void RotateCameraPlayer(float rotation);

	void Shoot();
	void RifleShoot();

	void StopRifleShoot();
	void StopShoot();

	void ShootCoolDown(float deltaTimer);
	void RifleCoolDown(float deltaTimer);

	void StartJump();
	void EndJump();

	void UpdatePlayerHUDLife();
	void CheckPlayerLife();
	void HealMyPlayer(float lifeToHeal);

	void EnableShield();
	void DisableShield(float timer);

	void EnableRifle();
	void DisableRifle(float timer);
	void EnableMyWeapons(float timer);
	void EnableMyMovement(float timer);

	UFUNCTION(BlueprintCallable)
		void TakePlayerDamage(float damage);

	UFUNCTION(BlueprintCallable)
		void GunLess();

	UFUNCTION(BlueprintCallable)
		void FreezeMyPlayer();
};
