

#include "MainPlayer.h"


AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	playerLife = playerMaxLife;
	myCamera = FindComponentByClass<UCameraComponent>();
	myShield->SetVisibility(false);
	freezeShield->SetVisibility(false);
	myRifle->SetVisibility(false);
	rifleLaser->SetVisibility(false);
}


void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ShootCoolDown(DeltaTime);
	RifleCoolDown(DeltaTime);
	DisableShield(DeltaTime);
	DisableRifle(DeltaTime);
	EnableMyWeapons(DeltaTime);
	EnableMyMovement(DeltaTime);
}


void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &AMainPlayer::MoveFront);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Rotation", this, &AMainPlayer::RotatePlayer);
	PlayerInputComponent->BindAxis("RotationY", this, &AMainPlayer::RotateCameraPlayer);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainPlayer::EndJump);
	
	PlayerInputComponent->BindAction("Shot", IE_Pressed, this, &AMainPlayer::Shoot);
	PlayerInputComponent->BindAction("Shot", IE_Released, this, &AMainPlayer::StopShoot);
	PlayerInputComponent->BindAction("ShotRifle", IE_Pressed, this, &AMainPlayer::RifleShoot);
	PlayerInputComponent->BindAction("ShotRifle", IE_Released, this, &AMainPlayer::StopRifleShoot);
	
	PlayerInputComponent->BindAction("ResetLevel", IE_Pressed, this, &AMainPlayer::ResetLevelOne);
	PlayerInputComponent->BindAction("ResetLevel2", IE_Pressed, this, &AMainPlayer::ResetLevelTwo);
	PlayerInputComponent->BindAction("ResetLevel3", IE_Pressed, this, &AMainPlayer::ResetLevelThree);
}

void AMainPlayer::MoveFront(float vertical)
{
	if (playerIsDead || freezePlayerActivated) return;
	AddMovementInput(GetActorForwardVector(), vertical); //Al apretar vertical nos movemos en el forward de nuestro actor.
}

void AMainPlayer::MoveRight(float horizontal)
{
	if (playerIsDead || freezePlayerActivated) return;	
	AddMovementInput(GetActorRightVector(), horizontal); //Lo mismo que arriba, pero lo movemos en su derecha. Si el valor es negativo, se mueve a su izquierda.
}

void AMainPlayer::RotatePlayer(float rotation)
{
	if (playerIsDead) return;
	AddControllerYawInput(rotation); //Yaw es movimiento en Y. Rota al jugador hacia los costados.
}

void AMainPlayer::RotateCameraPlayer(float rotation)
{
	if (playerIsDead) return;
	FRotator rot = myCamera->RelativeRotation; //Se iguala este rotator a la rotación relativa del player.

	float verticalRotation = rot.Pitch + rotation; //Acá agarramos el X del rotator creado, y guardamos eso + el input del joystick en una variable.
	verticalRotation = FMath::ClampAngle(verticalRotation, -60, 45); //Clampeamos el float para que no pase de estos valores.

	FRotator setRotation = FRotator(verticalRotation, rot.Yaw, rot.Roll); //Creamos un rotator final que tiene la rotación del player en Y y Z, pero la
																		 //variable creada por nosotros en X para permitir el movimiento.	
	myCamera->SetRelativeRotation(setRotation); //Asignemos el rotator.
}

void AMainPlayer::Shoot()
{
	if (gunLessActivated) return;
	canShot = true;
}

void AMainPlayer::RifleShoot()
{
	if (!rifleIsAvailable || gunLessActivated) return;
	canShotRifle = true;
}

void AMainPlayer::StopShoot()
{
	if (gunLessActivated) return;
	canShot = false;
}

void AMainPlayer::StopRifleShoot()
{
	if (!rifleIsAvailable || gunLessActivated) return;
	canShotRifle = false;
}

void AMainPlayer::ShootCoolDown(float deltaTimer)
{
	if (gunLessActivated) return;

	shotTimer += deltaTimer;
	
	if (canShot && !playerIsDead)
	{
		if (shotTimer >= myGunCoolDown)
		{
			gunSocketLocation = myGun->GetSocketLocation("Spawner");
			gunSocketRotation = myGun->GetSocketRotation("Spawner");

			UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				gunMuzzle->Template,
				gunSocketLocation + FVector(-2.5f, 0, 0),
				gunSocketRotation,
				FVector(0.1f, 0.1f, 0.1f),
				true);

			FActorSpawnParameters parameters;
			parameters.Owner = this;
			GetWorld()->SpawnActor<APlayerBullet>(prefabBullet, gunSocketLocation, gunSocketRotation, parameters);
		
			gunAudio->Play();
			
			shotTimer = 0;
		}
	}
}

void AMainPlayer::RifleCoolDown(float deltaTimer)
{
	if (!rifleIsAvailable || gunLessActivated) return;
	
	rifleShotTimer += deltaTimer;
	
	if (canShotRifle && !playerIsDead)
	{
		if (rifleShotTimer >= myRifleCoolDown)
		{
			rifleSocketLocation = myRifle->GetSocketLocation("Spawner");
			rifleSocketRotation = myRifle->GetSocketRotation("Spawner");

			UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				rifleMuzzle->Template,
				rifleSocketLocation + FVector(8, 0, 0),
				rifleSocketRotation,
				FVector(0.1f, 0.1f, 0.1f),
				true);

			FActorSpawnParameters parameters;
			parameters.Owner = this;
			GetWorld()->SpawnActor<APlayerBullet>(prefabRifleBullet, rifleSocketLocation, rifleSocketRotation, parameters);
			
			rifleAudio->Play();
			
			rifleShotTimer = 0;
		}
	}
}

void AMainPlayer::StartJump()
{
	if (playerIsDead) return;
	bPressedJump = true; //Booleano heredado del character que sirve para hacer un salto que ya está hecho por Unreal.
}

void AMainPlayer::EndJump()
{
	if (playerIsDead) return;
	bPressedJump = false;
}

void AMainPlayer::UpdatePlayerHUDLife()
{
	auto life = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
	float updateLifeValue = playerLife / playerMaxLife;
	if (life)
	life->UpdatePlayerLife(updateLifeValue);
}

void AMainPlayer::TakePlayerDamage(float damage)
{
	if (shieldActivated) return;
	playerLife = playerLife - damage;

	damageAudio->Play();
	
	UpdatePlayerHUDLife();
	CheckPlayerLife();
}

void AMainPlayer::HealMyPlayer(float lifeToHeal)
{
	playerLife += lifeToHeal;
	if (playerLife >= playerMaxLife)
		playerLife = playerMaxLife;

	powerUpAudio->Play();

	UpdatePlayerHUDLife();
}

void AMainPlayer::CheckPlayerLife()
{
	if (playerLife <= 0)
	{
		playerIsDead = true;
		auto myManagerUI = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
		myManagerUI->isDead = true;
	}
}

void AMainPlayer::ResetLevelOne()
{
	auto myManagerUI = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
	myManagerUI->resetFirstLevel = true;
}

void AMainPlayer::ResetLevelTwo()
{
	auto myManagerUI = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
	myManagerUI->resetSecondLevel = true;
}

void AMainPlayer::ResetLevelThree()
{
	auto myManagerUI = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
	myManagerUI->resetThirdLevel = true;
}

void AMainPlayer::EnableShield()
{
	powerUpAudio->Play();

	shieldActivated = true;
	myShield->SetVisibility(true);
}

void AMainPlayer::DisableShield(float timer)
{
	if (!shieldActivated) return;
	
	shieldTimer += timer;
	if (shieldTimer >= 10)
	{
		shieldActivated = false;
		myShield->SetVisibility(false);
		shieldTimer = 0;
	}
		
}

void AMainPlayer::EnableRifle()
{
	powerUpAudio->Play();

	rifleIsAvailable = true;
	myRifle->SetVisibility(true);
	rifleLaser->SetVisibility(true);
	canShotRifle = false;
}

void AMainPlayer::DisableRifle(float timer)
{
	if (!rifleIsAvailable) return;

	rifleAvailableTimer += timer;
	if(rifleAvailableTimer >= 30)
	{
		rifleIsAvailable = false;
		myRifle->SetVisibility(false);
		rifleLaser->SetVisibility(false);
		rifleShotTimer = 0;
		rifleAvailableTimer = 0;
	}
}

void AMainPlayer::GunLess()
{
	gunLessActivated = true;
	rifleIsAvailable = false;
	canShotRifle = false;
	canShot = false;
	rifleAvailableTimer = 0;
	rifleShotTimer = 0;
	shotTimer = 0;

	myRifle->SetVisibility(false);
	rifleLaser->SetVisibility(false);
	myGun->SetVisibility(false);
	gunLaser->SetVisibility(false);

}

void AMainPlayer::FreezeMyPlayer()
{
	freezePlayerActivated = true;
	freezeShield->SetVisibility(true);
}

void AMainPlayer::EnableMyWeapons(float timer)
{
	if (!gunLessActivated) return;

	waitForGuns += timer;
	
	if (waitForGuns <= 5)
	{
		auto weaponsHUD = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
		float updateValue = waitForGuns / 5;
		if (weaponsHUD)
			weaponsHUD->UpdatePlayerWeapons(updateValue);
	}

	else if (waitForGuns > 5)
	{
		gunLessActivated = false;
		myGun->SetVisibility(true);
		gunLaser->SetVisibility(true);
		waitForGuns = 0;
		
		auto weaponsHUD = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
		if (weaponsHUD)
		weaponsHUD->UpdatePlayerWeapons(1);

	}
}

void AMainPlayer::EnableMyMovement(float timer)
{
	if (!freezePlayerActivated) return;

	waitForMove += timer;
	if (waitForMove >= 2.5f)
	{
		freezePlayerActivated = false;
		freezeShield->SetVisibility(false);
		waitForMove = 0;
	}
}

