// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBullet.h"
#include "MainPlayer.h"


APlayerBullet::APlayerBullet()
{
	PrimaryActorTick.bCanEverTick = true;
}


void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();
}


void APlayerBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveThisBullet(DeltaTime);
	CheckLifeTime(DeltaTime);
}

void APlayerBullet::MoveThisBullet(float deltaTimer)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * bulletSpeed * deltaTimer);
}

void APlayerBullet::CheckLifeTime(float deltaTimer)
{
	deadTimer += deltaTimer;
	if (deadTimer >= timeToDead)
		DestroyThisBullet();
}

void APlayerBullet::CheckCollision(AActor * actorCheck)
{
	AMainPlayer *player = Cast<AMainPlayer>(actorCheck);
	if (!player)
		DestroyThisBullet();

}

void APlayerBullet::DestroyThisBullet()
{
	UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		deadParticle->Template,
		GetActorLocation(),
		GetActorRotation(),
		FVector(0.8f, 0.8f, 0.8f),
		true);

	Destroy(true);
}

