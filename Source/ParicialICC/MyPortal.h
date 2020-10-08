
#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "MyUI.h"
#include "GameFramework/Actor.h"
#include "MyPortal.generated.h"

UCLASS()
class PARICIALICC_API AMyPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyPortal();
	UPROPERTY(EditAnywhere)
		bool toLevel2;
	UPROPERTY(EditAnywhere)
		bool toLevel3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool enableFromStart;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void ChangeLevel();
	
};
