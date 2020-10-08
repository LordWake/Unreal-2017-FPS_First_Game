// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyDrone.h"



AFlyDrone::AFlyDrone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFlyDrone::BeginPlay()
{
	Super::BeginPlay();
	yDirection = 1;
	myMesh = FindComponentByClass<UStaticMeshComponent>();
	damageParticle->SetActive(false);
	shotParticle->SetActive(false);
}

void AFlyDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisEnemy(DeltaTime);
	LookToPlayer();
	Shoot(DeltaTime);
}

void AFlyDrone::MoveThisEnemy(float myTimer)
{
	if (isDead) return;
	moveTimer += myTimer;
	if (moveTimer >= 2)
	{
		yDirection = yDirection * -1;
		moveTimer = 0;
	}
	SetActorLocation(GetActorLocation() + GetActorUpVector() * speed * myTimer * yDirection);
}

void AFlyDrone::LookToPlayer()
{
	if (!playerIsNear) return;
	FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator playerRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), MyCharacterPosition);

	FRotator lookToPlayer(playerRotation.Pitch, playerRotation.Yaw, 0.0f);

	SetActorRotation(lookToPlayer);
}

void AFlyDrone::Shoot(float deltatimer)
{
	if (!playerIsNear || isDead) return;

	shotTimer += deltatimer;
	socketLocation = myMesh->GetSocketLocation("Spawner");

	if (shotTimer >= timeToShot)
	{
		if (typeOfDron == 0)
		{
			FActorSpawnParameters parameters;
			parameters.Owner = this;
			GetWorld()->SpawnActor<AEnemyBullet>(prefabBullet, socketLocation, GetActorRotation(), parameters);

			UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				shotParticle->Template,
				socketLocation,
				GetActorRotation(),
				FVector(0.5f, 0.5f, 0.5f),
				true);
			
			shotAudio->Play();
			shotTimer = 0;
		}

		else if (typeOfDron == 1)
		{
			FActorSpawnParameters parameters;
			parameters.Owner = this;
			GetWorld()->SpawnActor<ASlowBullet>(prefabSlowBullet, socketLocation, GetActorRotation(), parameters);

			UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				shotParticle->Template,
				socketLocation,
				GetActorRotation(),
				FVector(0.5f, 0.5f, 0.5f),
				true);
			
			shotAudio->Play();
			shotTimer = 0;
		}

		else if (typeOfDron == 2)
		{
			FActorSpawnParameters parameters;
			parameters.Owner = this;
			GetWorld()->SpawnActor<AGunLessBullet>(prefabGunLessBullet, socketLocation, GetActorRotation(), parameters);

			UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
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
}

void AFlyDrone::TakeEnemyDamage(float damage)
{
	if (isDead) return;
	enemyLife = enemyLife - damage;
	damageAudio->Play();
	CheckEnemyLife();
}

void AFlyDrone::CheckEnemyLife()
{
	if (enemyLife <= 8)
		damageParticle->SetActive(true);

	if (enemyLife <= 0)
	{
		if (isDead) return;
		explosionAudio->Play();
		UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			deadParticle->Template,
			GetActorLocation(),
			GetActorRotation(),
			FVector(0.7f, 0.7f, 0.7f),
			true);
		
		SetActorHiddenInGame(true);
		isDead = true;
	}
}

void AFlyDrone::CheckDistanceToPlayer(float distance)
{
	if (distance <= 1500)
		playerIsNear = true;
	else
		playerIsNear = false;
}

