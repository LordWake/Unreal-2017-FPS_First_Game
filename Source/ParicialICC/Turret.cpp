// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"


ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ATurret::BeginPlay()
{
	Super::BeginPlay();
	myMesh = FindComponentByClass<UStaticMeshComponent>();
	damageParticle->SetActive(false);
	shotParticle->SetActive(false);
}


void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookToPlayer();
	Shoot(DeltaTime);
}

void ATurret::LookToPlayer()
{
	if (!playerIsNear) return;
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator playerRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), playerPosition);

	FRotator lookToPlayer(GetActorRotation().Pitch, playerRotation.Yaw, GetActorRotation().Roll);
	SetActorRotation(lookToPlayer);
}

void ATurret::Shoot(float deltaTimer)
{
	if (!playerIsNear || isDead) return;

	shotTimer += deltaTimer;
	socketLocation = myMesh->GetSocketLocation("Spawner");
	
	if (shotTimer >= 1.0f)
	{
		FActorSpawnParameters parameters;
		parameters.Owner = this;
		GetWorld()->SpawnActor<AEnemyBullet>(prefabBullet, socketLocation, GetActorRotation(), parameters);

		UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			shotParticle->Template,
			socketLocation,
			GetActorRotation(),
			FVector(0.3f, 0.3f, 0.1f),
			true);

		shotAudio->Play();
		shotTimer = 0;
	}
}

void ATurret::TakeEnemyDamage(float damage)
{
	if (isDead) return;
	enemyLife = enemyLife - damage;
	damageAudio->Play();
	CheckEnemyLife();
}

void ATurret::CheckEnemyLife()
{
	if (enemyLife <= 8)
		damageParticle->SetActive(true);

	if (enemyLife <= 0)
	{
		if (isDead) return;
		explosionAudio->Play();
		UParticleSystemComponent *myParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			deadParticle->Template,
			GetActorLocation(),
			GetActorRotation(),
			FVector(0.5f, 0.5f, 0.5f),
			true);
	
		SetActorHiddenInGame(true);
		isDead = true;
	}
}

void ATurret::CheckDistanceToPlayer(float distance)
{
	if (distance <= 1500)
		playerIsNear = true;
	else
		playerIsNear = false;
}

