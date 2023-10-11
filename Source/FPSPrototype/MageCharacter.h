#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "MageCharacter.generated.h"

UCLASS()
class FPSPROTOTYPE_API AMageCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	AMageCharacter();

private:
	FVector TeleportLocation();
	
	UFUNCTION(BlueprintCallable)
	void SpawnMagicBall();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* BallSpawnPoint;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMagicBall> MagicBallClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABorderPole> BorderPoleClass;

	class AMagicBall* CurrentBall;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* TeleportSound;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack() override;

	void Teleport();


};
