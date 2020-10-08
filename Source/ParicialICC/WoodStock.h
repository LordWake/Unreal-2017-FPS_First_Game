#pragma once

#include "Engine.h"
#include "EnemyBullet.h"
#include "MyUI.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "MyAnimInstance.h"
#include "WoodStock.generated.h"

UCLASS()
class PARICIALICC_API AWoodStock : public AActor
{
	GENERATED_BODY()
	
public:	

	AWoodStock();

	float shotTimer;
	float onAttackTimer;
	float breakTimer;
	float enemyLife;
	float shotCoolDown;

	bool firstShot;
	bool canAttack;
	bool onDamage;
	bool takeABreak;
	bool bossIsDead;
	
	FVector socketLocation;
	
	UMyAnimInstance* anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* damageAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* shotAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* myWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent * damageParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent * levitateParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent * shotParticle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBullet> prefabBullet;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	void AttackPlayer(float timer);
	void WaitToAttackAgain(float timer);
	void CheckEnemyLife();
	void LookToPlayer();

	UFUNCTION(BlueprintCallable)
		void TakeEnemyDamage(float damage);
	
};
