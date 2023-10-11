#include "EnemyCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"

AEnemyCharacter::AEnemyCharacter()
{
	//Components setup
	PrimaryActorTick.bCanEverTick = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::Attack()
{
	//When triggered Enemy rotates to look at Player                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	UE_LOG(LogTemp, Warning, TEXT("Attacking..."));

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if(Player == nullptr) return;

    FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());
	Rotation.Roll = 0;
	Rotation.Pitch = 0;

    SetActorRotation(Rotation);

	IsAttacking = true;
}

bool AEnemyCharacter::GetIsAttacking()
{
    return IsAttacking;
}

void AEnemyCharacter::StopAttack()
{
	IsAttacking = false;
}

void AEnemyCharacter::Die()
{
	//Enemy's Death
	Super::Die();

	GetWorldTimerManager().SetTimer(DissolutionTimerHandle, this, &AEnemyCharacter::BodyDissolution, 5, false);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DyingSound, GetActorLocation());
	DetachFromControllerPendingDestroy();
}

void AEnemyCharacter::BodyDissolution()
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Body dissolved...:("));
}