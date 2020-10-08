#pragma once

#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"


UCLASS()
class PARICIALICC_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool fire;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool isDead;

		void UpdateSpecialAttack(bool shotNow);
		void UpdateDead(bool deadNow);
		
};
