#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "BarbarianCharacter.generated.h"

UCLASS()
class FPSPROTOTYPE_API ABarbarianCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	ABarbarianCharacter();

	UFUNCTION()
	void Overlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected:
	virtual void BeginPlay() override;

	virtual void Attack() override;

private:

	UFUNCTION(BlueprintCallable)
	void JumpAttack();

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* HitBox;

	UPROPERTY(EditDefaultsOnly)
	class UDamageComponent* DamageComp;

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float Damage = 10;

	virtual void StopAttack() override;
	bool HitAlready = false;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float JumpPower = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* SlashSound;
};
