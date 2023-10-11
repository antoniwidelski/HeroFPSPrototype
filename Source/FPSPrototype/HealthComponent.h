#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSPROTOTYPE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

private:
	class ABaseCharacter* Owner;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 1000;

	float Health;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float BaseDamage, const UDamageType* DamageType, class AController* EventInstigator, AActor* DamageCauser);

	float GetHealthPercent();
		
};