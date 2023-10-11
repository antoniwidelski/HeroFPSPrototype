// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class FPSPROTOTYPE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComp;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool GetIsAlive();

	UFUNCTION(BlueprintPure)
	float GetHealthPercent();

	virtual void Die();

private:
	bool IsAlive = true;
};
