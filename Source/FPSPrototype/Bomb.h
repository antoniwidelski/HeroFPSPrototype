// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class FPSPROTOTYPE_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	ABomb();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* MoveComp;

	UPROPERTY(EditAnywhere, Category="Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ExplosionEmitter;

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* ExplosionSound;

	void Explode();

	FTimerHandle ExplosionTimerHanlde;

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float BombLifeSpan = 3.f;

	UPROPERTY(EditDefaultsOnly)
	class UDamageComponent* DamageComp;

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float Damage = 0;
	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float DamageRadius = 0;

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
