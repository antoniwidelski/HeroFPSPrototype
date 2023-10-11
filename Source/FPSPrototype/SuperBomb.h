#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Actor.h"
#include "SuperBomb.generated.h"

UCLASS()
class FPSPROTOTYPE_API ASuperBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	ASuperBomb();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool Grounded = false;
	
	FTransform Transform;

	FTimerHandle ExplosionTimerHandle;
	FTimerHandle CollisionTimerHandle;

	UPROPERTY(EditAnywhere, Category="Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ExplosionEmitter;
	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float CollisionTime = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float SuperBombExplosionTime = 0;

	UPROPERTY(EditDefaultsOnly)
	class UDamageComponent* DamageComp;

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float Damage = 0;
	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float DamageRadius = 0;

	void ChangeCollisionSettings();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Explode();	
};
