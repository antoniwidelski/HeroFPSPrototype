#include "DamageComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

//Health and Damage Components are responsible for handling Health and Damage

bool UDamageComponent::SetData()
{
	//Setting Data neccecary to component
	Causer = GetOwner();
	if(!Causer)
	{
		UE_LOG(LogTemp, Error, TEXT("Causer Invalid!"));
		return false;
	} 
	UE_LOG(LogTemp, Warning, TEXT("Causer's Name: %s"), *Causer->GetName());

	if(Cast<ABaseCharacter>(Causer))
	{
		Character = Cast<ABaseCharacter>(Causer);
	}
	else
	{
		Character = Cast<ABaseCharacter>(Causer->GetOwner());
	}
	
	if(!Character) 
	{
		UE_LOG(LogTemp, Error, TEXT("Character Invalid!"));
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Character's Name: %s"), *Character->GetName());
	InstigatorController = Character->GetInstigatorController();
	if(!InstigatorController)
	{
		UE_LOG(LogTemp, Error, TEXT("Instigator Controller Invalid!"));
		return false;
	}
	Location = Causer->GetActorLocation();
	Actors.Add(Character);

	return true;
}

void UDamageComponent::RadialDamage(float Damage, float Radius)
{
	//Applying radial damage
	if(!SetData()) return;
	
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, Location, Radius, UDamageType::StaticClass(), Actors, Causer, InstigatorController, true);
}

void UDamageComponent::PointDamage(float Damage, AActor* OtherActor)
{
	//Applying radial damage
	if(!SetData()) return;

	UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorController, Causer, UDamageType::StaticClass());
}