// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBullet.h"
#include "FlyDrone.h"
#include "Turret.h"
#include "GroundDrone.h"
#include "RupertBoss.h"
#include "PlayerBullet.h"


AEnemyBullet::AEnemyBullet()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
}


void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisBullet(DeltaTime);
	CheckLifeTime(DeltaTime);
}

void AEnemyBullet::MoveThisBullet(float deltaTimer)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * bulletSpeed * deltaTimer);
}

void AEnemyBullet::CheckLifeTime(float deltaTimer)
{
	deadtimer += deltaTimer;
	if (deadtimer >= 4)
		DestroyThisBullet();
}

void AEnemyBullet::CheckCollision(AActor *checkIfBoss, AActor * checkIfDrone, AActor * checkIfTurret, AActor* checkIfGroundDrone, AActor* checkIfPlayerBullet)
{
	ARupertBoss *rupertBoss = Cast<ARupertBoss>(checkIfBoss);
	AFlyDrone *myDrone = Cast<AFlyDrone>(checkIfDrone);
	ATurret *myTurret = Cast<ATurret>(checkIfTurret);
	AGroundDrone *myGroundDrone = Cast<AGroundDrone>(checkIfGroundDrone);

	if (!rupertBoss)
		DestroyThisBullet();
	else if (!myDrone)
		DestroyThisBullet();
	else if (!myTurret)
		DestroyThisBullet();
	else if (!myGroundDrone)
		DestroyThisBullet();
	else if (!checkIfPlayerBullet)
		DestroyThisBullet();
}

void AEnemyBullet::DestroyThisBullet()
{
	UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		deadParticle->Template,
		GetActorLocation(),
		GetActorRotation(),
		FVector(0.1f, 0.1f, 0.1f),
		true);

	Destroy(true);
}

