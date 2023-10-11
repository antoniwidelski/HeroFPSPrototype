#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Actor.h"
#include "Mine.generated.h"

UCLASS()
class FPSPROTOTYPE_API AMine : public AActor
{
	GENERATED_BODY()
	
public:	
	AMine();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ExplosionEmitter;
	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* ExplosionSound;

	bool IsArmed = false;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UDamageComponent* DamageComp;

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float Damage = 0;
	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float DamageRadius = 0;

protected:
	virtual void BeginPlay() override;

public:	
	
	void Arm();
	bool GetIsArmed();

	void Explode();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeMineColor();

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float BaseDamage, const UDamageType* DamageType, class AController* EventInstigator, AActor* DamageCauser);
};
