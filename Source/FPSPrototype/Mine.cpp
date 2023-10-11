#include "Mine.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "BomberCharacter.h"
#include "DamageComponent.h"

AMine::AMine()
{
	//Components setup
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	SetActorEnableCollision(false);

	DamageComp = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComp"));
}

void AMine::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AMine::DamageTaken);
}

void AMine::Arm()
{
	//Arming Mine
	IsArmed = true;
	ChangeMineColor();
	SetActorEnableCollision(true);
}

void AMine::Explode()
{
	//Explosion and double jump
	if(IsArmed)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEmitter, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
		ABomberCharacter* MyOwner = Cast<ABomberCharacter>(GetOwner());
		if(MyOwner)
		{
			UE_LOG(LogTemp, Warning, TEXT("Owner is Valid..."));
			if(MyOwner->RocketJumpCheck(this))
			{
				MyOwner->RocketJump();
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Owner is invalid..."));
		}
		DamageComp->RadialDamage(Damage, DamageRadius);
		Destroy();
	}
	
}

void AMine::DamageTaken(AActor* DamagedActor, float BaseDamage, const UDamageType* DamageType, class AController* EventInstigator, AActor* DamageCauser)
{
	//Reacting to taking damage
	if(Cast<AMine>(DamageCauser)) return;
	Explode();
}

bool AMine::GetIsArmed()
{
	return IsArmed;
}