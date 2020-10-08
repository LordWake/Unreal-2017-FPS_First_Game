
#include "WoodStock.h"


AWoodStock::AWoodStock()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWoodStock::BeginPlay()
{
	Super::BeginPlay();
	
	anim = Cast<UMyAnimInstance>(FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance());
	
	damageParticle->SetActive(false);
	shotParticle->SetActive(false);
	shield->SetVisibility(false);
	levitateParticle->SetActive(true);
	enemyLife = 50;
	shotCoolDown = 0.1f;
	
	onDamage = true;
}

void AWoodStock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttackPlayer(DeltaTime);
	WaitToAttackAgain(DeltaTime);
	LookToPlayer();
}


void AWoodStock::TakeEnemyDamage(float damage)
{
	if (!onDamage || bossIsDead) return;

	enemyLife = enemyLife - damage;
	damageAudio->Play();

	UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		damageParticle->Template,
		GetActorLocation(),
		GetActorRotation(),
		FVector(0.4f, 0.4f, 0.4f),
		true);
	
	if (!firstShot) 
	{
		firstShot = true;
		canAttack = true;
	}

	CheckEnemyLife();
}

void AWoodStock::CheckEnemyLife()
{
	if (enemyLife <= 0)
	{
		bossIsDead = true;
		anim->UpdateDead(true);
		shield->SetVisibility(false);
		levitateParticle->SetActive(false);


		auto myManagerUI = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
		myManagerUI->CheckIfPlayerWin(3);
	}
}

void AWoodStock::AttackPlayer(float timer)
{	
	if (!canAttack || bossIsDead) return;

	anim->UpdateSpecialAttack(true);
	onAttackTimer += timer;
	shield->SetVisibility(true);
	levitateParticle->SetActive(false);
	
	if (onAttackTimer <= 10)
	{
		onDamage = false;
		shotTimer += timer;

		if (shotTimer >= shotCoolDown)
		{
			socketLocation = myWeapon->GetSocketLocation("Spawner");
			FActorSpawnParameters parameters;
			parameters.Owner = this;

			GetWorld()->SpawnActor<AEnemyBullet>(prefabBullet, socketLocation, GetActorRotation(), parameters);
			UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				shotParticle->Template,
				socketLocation,
				GetActorRotation(),
				FVector(0.1f, 0.1f, 0.1f),
				true);

			shotAudio->Play();
			shotTimer = 0;
		}
	}

	else
	{
		canAttack = false;
		onAttackTimer = 0;
		shotTimer = 0;
		takeABreak = true;
	}
}

void AWoodStock::WaitToAttackAgain(float timer)
{
	if (!takeABreak || bossIsDead) return;
	onDamage = true;
	shield->SetVisibility(false);
	anim->UpdateSpecialAttack(false);
	levitateParticle->SetActive(true);


	breakTimer += timer;
	if (breakTimer >= 5.0f)
	{
		takeABreak = false;
		canAttack = true;
		breakTimer = 0;
	}
}

void AWoodStock::LookToPlayer()
{
	if (bossIsDead) return;

	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator playerRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), playerPosition);

	FRotator lookToPlayer(GetActorRotation().Pitch, playerRotation.Yaw, GetActorRotation().Roll);
	SetActorRotation(lookToPlayer);
}


