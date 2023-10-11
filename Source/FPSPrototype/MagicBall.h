#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Actor.h"
#include "MagicBall.generated.h"

UCLASS()
class FPSPROTOTYPE_API AMagicBall : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicBall();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float Speed = 100;

	UFUNCTION()
	void Overlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditDefaultsOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float Damage = 10;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UDamageComponent* DamageComp;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* WhooshSound;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	
};
