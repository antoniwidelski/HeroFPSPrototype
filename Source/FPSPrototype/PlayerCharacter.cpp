#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Components Setup
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookRight);

	PlayerInputComponent->BindAction(TEXT("MainAttack"), IE_Pressed, this, &APlayerCharacter::MainAttack);
	PlayerInputComponent->BindAction(TEXT("FirstAbility"), IE_Pressed, this, &APlayerCharacter::FirstAbility);
	PlayerInputComponent->BindAction(TEXT("SecondAbility"), IE_Pressed, this, &APlayerCharacter::SecondAbility);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("UltimateAbility"), IE_Pressed, this, &APlayerCharacter::UltimateAbility);
	PlayerInputComponent->BindAction(TEXT("CustomAction"), IE_Pressed, this, &APlayerCharacter::CustomAction);

	PlayerInputComponent->BindAction(TEXT("Menu"), IE_Pressed, this, &APlayerCharacter::Menu);
}

UCameraComponent* APlayerCharacter::GetCamera()
{
	return Camera;
}

//Movement and Abilities
void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::MainAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Main Attack..."));
}

void APlayerCharacter::FirstAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("First Ability..."));
}

void APlayerCharacter::SecondAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("Second Ability..."));
}

void APlayerCharacter::UltimateAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("Ultimate Ability..."));
}

void APlayerCharacter::CustomAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Custom Action..."));
}

void APlayerCharacter::Jump()
{
	Super::Jump();
}

void APlayerCharacter::Menu()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MenuLevel"), true);
}

//Cooldown and Ult
void APlayerCharacter::AddChargingPoints(float Points)
{
	ChargingPoints += Points;
	if(ChargingPoints>UltimateAbilityChargingCapacity)
	{
		ChargingPoints = UltimateAbilityChargingCapacity;
	}
}

float APlayerCharacter::GetChargingPoints()
{
	return ChargingPoints;
}

void APlayerCharacter::MACooldown()
{
	IsMACooled = true;
}

void APlayerCharacter::FACooldown()
{
	IsFACooled = true;
}

void APlayerCharacter::SACooldown()
{
	IsSACooled = true;
}

void APlayerCharacter::UACooldown()
{
	IsUACooled = true;
}

void APlayerCharacter::AbilityFailed()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), CooldownSound, GetActorLocation());
}

float APlayerCharacter::GetMACT()
{
	return MainAttackCooldownTime;
}

float APlayerCharacter::GetFACT()
{
	return FirstAbilityCooldownTime;
}

float APlayerCharacter::GetSACT()
{
	return SecondAbilityCooldownTime;
}

float APlayerCharacter::GetUACC()
{
	return UltimateAbilityChargingCapacity;
}


//Player's Death
void APlayerCharacter::Die()
{
	Super::Die();

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
	if(PlayerController) 
	{
		PlayerController->Die();
		DetachFromControllerPendingDestroy();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Controller Invalid..."));
	}
}