#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

//Health and Damage Components are responsible for handling Health and Damage

UHealthComponent::UHealthComponent()
{

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Setting up
	Owner = Cast<ABaseCharacter>(GetOwner());
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
		UE_LOG(LogTemp, Warning, TEXT("Owner Validowatny!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Owner Invalid!"));
	}

	Health = MaxHealth;
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float BaseDamage, const UDamageType* DamageType, class AController* EventInstigator, AActor* DamageCauser)
{	
	//Handling Damage
	Health -= BaseDamage;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	if(Health<=0 && Owner!=nullptr)
	{
		Health = 0;
		Owner->Die();
	}
}

float UHealthComponent::GetHealthPercent()
{
	if(MaxHealth!=0) 
	{
		return Health/MaxHealth;
	}
	return 0;
}
