#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FPSPROTOTYPE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

	virtual void MainAttack();
	virtual void FirstAbility();
	virtual void SecondAbility();
	virtual void UltimateAbility();
	virtual void CustomAction();
	virtual void Jump() override;

	virtual void Menu();

	bool IsMACooled = true;
	bool IsFACooled = true;
	bool IsSACooled = true;
	bool IsUACooled = true;

	float ChargingPoints;

	//Cooldown
	UPROPERTY(EditDefaultsOnly, Category="Combat|Cooldown", meta = (AllowPrivateAccess = "true"))
	float MainAttackCooldownTime = 0;
	UPROPERTY(EditDefaultsOnly, Category="Combat|Cooldown", meta = (AllowPrivateAccess = "true"))
	float FirstAbilityCooldownTime = 0;
	UPROPERTY(EditDefaultsOnly, Category="Combat|Cooldown", meta = (AllowPrivateAccess = "true"))
	float SecondAbilityCooldownTime = 0;
	UPROPERTY(EditDefaultsOnly, Category="Combat|Cooldown", meta = (AllowPrivateAccess = "true"))
	float UltimateAbilityChargingCapacity = 0;

	FTimerHandle MATimerHandle;
	FTimerHandle FATimerHandle;
	FTimerHandle SATimerHandle;
	FTimerHandle UATimerHandle;

	void AbilityFailed();
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UCameraComponent* GetCamera();

	virtual void Die() override;
	
	void AddChargingPoints(float Points);
	UFUNCTION(BlueprintPure)
	float GetChargingPoints();

	void MACooldown();
	void FACooldown();
	void SACooldown();
	void UACooldown();

	UFUNCTION(BlueprintPure)
	float GetMACT();
	UFUNCTION(BlueprintPure)
	float GetFACT();
	UFUNCTION(BlueprintPure)
	float GetSACT();
	UFUNCTION(BlueprintPure)
	float GetUACC();

	UPROPERTY(EditDefaultsOnly, Category="Combat|Cooldown", meta=(AllowPrivateAccess = "true"))
	USoundBase* CooldownSound;

	
};
