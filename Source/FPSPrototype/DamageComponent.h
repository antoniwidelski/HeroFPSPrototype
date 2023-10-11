#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSPROTOTYPE_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void RadialDamage(float Damage, float Radius);

	void PointDamage(float Damage, AActor* OtherActor);

private:
	AActor* Causer;
	class ABaseCharacter* Character;
	AController* InstigatorController;
	FVector Location;
	TArray<AActor*> Actors;

	bool SetData();
};

