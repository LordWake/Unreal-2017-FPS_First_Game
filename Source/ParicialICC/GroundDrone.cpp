// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundDrone.h"


AGroundDrone::AGroundDrone()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AGroundDrone::BeginPlay()
{
	Super::BeginPlay();
	xDirection = 1;
	myMesh = FindComponentByClass<UStaticMeshComponent>();
	damageParticle->SetActive(false);
	shotParticle->SetActive(false);
}


void AGroundDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisEnemy(DeltaTime);
	Shoot(DeltaTime);
}

void AGroundDrone::MoveThisEnemy(float myTimer)
{
	if (isDead) return;
	moveTimer += myTimer;
	if (moveTimer > 0.5f)
	{
		xDirection = xDirection * -1;
		moveTimer = 0;
	}

	SetActorLocation(GetActorLocation() + GetActorRightVector() * speed * myTimer * xDirection);
}

void AGroundDrone::Shoot(float deltaTimer)
{
	if (!playerIsNear || isDead) return;

	shotTimer += deltaTimer;
	socketLocation = myMesh->GetSocketLocation("Spawner");
	socketRotation = myMesh->GetSocketRotation("Spawner");
	
	if (shotTimer >= 0.5f)
	{
		FActorSpawnParameters parameters;
		parameters.Owner = this;
		GetWorld()->SpawnActor<AEnemyBullet>(prefabBullet, socketLocation, socketRotation, parameters);

		UParticleSystemComponent *myParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			shotParticle->Template,
			socketLocation,
			GetActorRotation(),
			FVector(0.5f, 0.5f, 0.5f),
			true);

		shotAudio->Play();
		shotTimer = 0;
	}
}

void AGroundDrone::TakeEnemyDamage(float damage)
{
	if (isDead) return;
	enemyLife = enemyLife - damage;
	damageAudio->Play();
	CheckEnemyLife();
}

void AGroundDrone::CheckEnemyLife()
{
	if (enemyLife <= 5)
		damageParticle->SetActive(true);

	if (enemyLife <= 0)
	{
		if (isDead) return;
		explosionAudio->Play();
		UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			deadParticle->Template,
			GetActorLocation(),
			FRotator(0.0f, 90.0f, 0.0f),
			FVector(0.8f, 0.8f, 0.8f),
			true);

		SetActorHiddenInGame(true);
		isDead = true;
	}
}

void AGroundDrone::CheckDistanceToPlayer(float distance)
{
	if (distance <= 1500)
		playerIsNear = true;
	else
		playerIsNear = false;
}
