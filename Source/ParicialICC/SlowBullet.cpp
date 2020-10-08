// Fill out your copyright notice in the Description page of Project Settings.

#include "SlowBullet.h"
#include "FlyDrone.h"
#include "Turret.h"
#include "GroundDrone.h"
#include "PlayerBullet.h"


ASlowBullet::ASlowBullet()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASlowBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlowBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisBullet(DeltaTime);
	CheckLifeTime(DeltaTime);
}

void ASlowBullet::MoveThisBullet(float deltaTimer)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * bulletSpeed * deltaTimer);
}

void ASlowBullet::CheckLifeTime(float deltaTimer)
{
	deadtimer += deltaTimer;
	if (deadtimer >= 4)
		DestroyThisBullet();
}

void ASlowBullet::CheckCollision(AActor * checkIfDrone, AActor * checkIfTurret, AActor* checkIfGroundDrone, AActor* checkIfPlayerBullet)
{
	AFlyDrone *myDrone = Cast<AFlyDrone>(checkIfDrone);
	ATurret *myTurret = Cast<ATurret>(checkIfTurret);
	AGroundDrone *myGroundDrone = Cast<AGroundDrone>(checkIfGroundDrone);

	if (!myDrone)
		DestroyThisBullet();
	else if (!myTurret)
		DestroyThisBullet();
	else if (!myGroundDrone)
		DestroyThisBullet();
	else if (!checkIfPlayerBullet)
		DestroyThisBullet();
}

void ASlowBullet::DestroyThisBullet()
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

