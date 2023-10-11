#include "BaseCharacter.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSPrototypeGameModeBase.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ABaseCharacter::GetIsAlive()
{
	return IsAlive;
}

//Character's Death
void ABaseCharacter::Die()
{
    UE_LOG(LogTemp, Warning, TEXT("Actor Died..."));
	IsAlive = false;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AFPSPrototypeGameModeBase* GameMode = Cast<AFPSPrototypeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->CharacterKilled(this);
}

float ABaseCharacter::GetHealthPercent()
{
	return HealthComp->GetHealthPercent();
}

