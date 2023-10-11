#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"


UCLASS()
class FPSPROTOTYPE_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

private:
	bool IsAttacking = false;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* DyingSound;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HealthBar;

	virtual void Die() override;
	void BodyDissolution();

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack();

	UFUNCTION(BlueprintCallable)
	virtual void StopAttack();
	
	UFUNCTION(BlueprintPure)
	bool GetIsAttacking();	

	FTimerHandle DissolutionTimerHandle;
};
