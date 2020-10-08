// Fill out your copyright notice in the Description page of Project Settings.

#include "RupertBoss.h"


ARupertBoss::ARupertBoss()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARupertBoss::BeginPlay()
{
	Super::BeginPlay();
	yDirection = 1;
	speed = defaultSpeed;
	firstStage = true;
	damageParticle->SetActive(false);
	shotParticle->SetActive(false);
	onLevitate->SetActive(false);
	levitateFireParticleOne->SetActive(false);
	levitateFireParticleTwo->SetActive(false);
}

void ARupertBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveThisEnemy(DeltaTime);
	MoveEnemyToSky(DeltaTime);
	LookToPlayer();
	LookToPlayerWhenLevitate();
	Shoot(DeltaTime);
	ChangeDirection();
}

//STAGE 3
void ARupertBoss::MoveThisEnemy(float myTimer)
{
	if (!thirdStage || isDead) return;
	speed = defaultSpeed;

	moveTimer += myTimer;
	if (moveTimer >= levitationTimer)
	{
		yDirection = yDirection * -1;
		moveTimer = 0;
	}
	SetActorLocation(GetActorLocation() + GetActorUpVector() * speed * myTimer * yDirection);
}

//STAGE 2
void ARupertBoss::MoveEnemyToSky(float myTimer)
{
	if (!secondStage || isDead) return;
	moveToSkyTimer += myTimer;
	if (moveToSkyTimer >= levitationTimer)
	{
		yDirection = yDirection * -1;
		speed = 0;
	}

	SetActorLocation(GetActorLocation() + GetActorUpVector() * speed * myTimer * yDirection);
}

//STAGE 1
void ARupertBoss::LookToPlayer()
{
	//STAGE 1

	if (!playerIsNear || !firstStage || isDead) return;
	FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator playerRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), MyCharacterPosition);

	FRotator lookToPlayer(0, playerRotation.Yaw, 0.0f);

	SetActorRotation(lookToPlayer);
}

//STAGE 2 Y 3
void ARupertBoss::LookToPlayerWhenLevitate()
{

	if (!playerIsNear && !secondStage || !playerIsNear && !thirdStage || isDead) return;
	FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator playerRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), MyCharacterPosition);

	FRotator lookToPlayer(playerRotation.Pitch, playerRotation.Yaw, playerRotation.Roll);

	SetActorRotation(lookToPlayer);
}

void ARupertBoss::ChangeDirection()
{
	if (setupDirection)
	{
		if (!stopChangeDirection)
		{
			yDirection = -1;
			stopChangeDirection = true;
		}
	}
}

void ARupertBoss::Shoot(float deltaTimer)
{
	//STAGE 1
	if (!playerIsNear || isDead) return;
	
	shotTimer += deltaTimer;
	socketLocation = myMesh->GetSocketLocation("Spawner");
	socketRotation = myMesh->GetSocketRotation("Spawner");

	if (shotTimer >= coolDownBetweenBullets)
	{
		FActorSpawnParameters parameters;
		parameters.Owner = this;
		GetWorld()->SpawnActor<AEnemyBullet>(prefabBullet, socketLocation, socketRotation, parameters);
		UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			shotParticle->Template,
			socketLocation,
			GetActorRotation(),
			FVector(1.0f, 1.0f, 1.0f),
			true);

		shotAudio->Play();
		shotTimer = 0;
	}
}

void ARupertBoss::TakeEnemyDamage(float damage)
{
	if (isDead) return;
	enemyLife = enemyLife - damage;
	damageAudio->Play();
	CheckEnemyLife();
}

void ARupertBoss::CheckEnemyLife()
{
	if (enemyLife <= 60 && enemyLife > 30) //STAGE 2
	{
		onLevitate->SetActive(true);
		levitateFireParticleOne->SetActive(true);
		levitateFireParticleTwo->SetActive(true);
		firstStage = false;
		secondStage = true;
	}
	else if (enemyLife <= 30 && enemyLife > 15) //STAGE 3
	{
		secondStage = false;
		thirdStage = true;
		setupDirection = true;
	}

	else if (enemyLife <= 15 && enemyLife > 0)
	{
		damageParticle->SetActive(true);
	}

	if (enemyLife <= 0)
	{
		if (isDead) return;
		explosionAudio->Play();
		UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			deadParticle->Template,
			GetActorLocation(),
			GetActorRotation(),
			FVector(1.0f, 1.0f, 1.0f),
			true);

		thisPortal->SetActorHiddenInGame(false);
		thisPortal->SetActorEnableCollision(true);

		SetActorHiddenInGame(true);
		isDead = true;
	}
}

void ARupertBoss::CheckDistanceToPlayer(float distance)
{
	if (distance <= 3000)
		playerIsNear = true;
	else
		playerIsNear = false;
}
