// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "BomberCharacter.generated.h"


/**
 * 
 */
UCLASS()
class FPSPROTOTYPE_API ABomberCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
private:
	bool IsAttacking = false;

	UPROPERTY(EditAnywhere, Category="Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* WeaponFire;

	//Bomb
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Combat|Bomb")
	TSubclassOf<class ABomb> BombClass;
	ABomb* Bomb;
protected:
	virtual void BeginPlay() override;

	class UCharacterMovementComponent* CharMoveComp;

	class AMyPlayerController* Controller;

	//Input
	virtual void MainAttack() override;
	virtual void FirstAbility() override;
	virtual void SecondAbility() override;
	virtual void UltimateAbility() override;
	virtual void CustomAction() override;
	virtual void Jump() override;

	//Bomb
	void SpawnBomb();
	UPROPERTY(EditDefaultsOnly, Category="Combat|Bomb")
	USoundBase* LauncherSound;

	//RocketJump
	UPROPERTY(EditAnywhere, Category="Combat|Rocket Jump")
	float MaxDistanceZ;
	UPROPERTY(EditAnywhere, Category="Combat|Rocket Jump")
	float MaxDistanceXandY;
	UPROPERTY(EditAnywhere, Category="Combat|Rocket Jump")
	float UpVelocity;

	//Burst
	FTimerHandle BurstTimerHanlde;
	UPROPERTY(EditDefaultsOnly, Category="Combat|Burst")
	float BurstRate = 1;
	int BurstCounter = 0;
	void Burst();

	//Mine
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Combat|Mine")
	TSubclassOf<class AMine> MineClass;
	bool IsPlacingMine = false;
	void StartPlacingMine();
	void StopPlacingMine(bool Commit);
	class AMine* CurrentMine;
	float MineZ = 0;
	bool PlaceTrace(FHitResult& HitResult, float PlaceRange);
	UPROPERTY(EditDefaultsOnly, Category="Combat|Mine")
	float MaxMinePlacingRange;
	int MineCounter();
	void ExplodeAllMines();

	//SuperBomb
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Combat|SuperBomb")
	TSubclassOf<class APointer> PointerClass;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Combat|SuperBomb")
	TSubclassOf<class ASuperBomb> SuperBombClass;

	void StartPointing();
	void StopPointing(bool Commit);
	class APointer* Pointer;
	float PointerZ = 0;
	bool IsPointing = false;
	class ASuperBomb* SuperBomb;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//RocketJump
	bool RocketJumpCheck(AActor* Actor);
	void RocketJump();
	

	

	
	
	

	
};
