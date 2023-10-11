// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyCharacter.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/DamageType.h"
#include "BomberCharacter.h"
#include "Mine.h"
#include "DamageComponent.h"

ABomb::ABomb()
{
 	//Components setup
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));
	MoveComp->InitialSpeed = 100.f;
	MoveComp->MaxSpeed = 10.f;

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	DamageComp = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComp"));
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &ABomb::OnHit);

	GetWorldTimerManager().SetTimer(ExplosionTimerHanlde, this, &ABomb::Explode, BombLifeSpan, false);
}

void ABomb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Reaction to Hit
	//Checking if it hit enemy or is it double jump trigger and reacting to it
	ABomberCharacter* MyOwner = Cast<ABomberCharacter>(GetOwner());
	if(!MyOwner) 
	{
		UE_LOG(LogTemp, Error, TEXT("Owner invalid!"));
		return;
	}
	
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	auto CheckOtherActor = Cast<AEnemyCharacter>(OtherActor);
	auto CheckIfIsMine = Cast<AMine>(OtherActor);
	if((CheckIfIsMine || CheckOtherActor) && OtherActor!=this && OtherActor != MyOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Hit!"));
		MyOwner->AddChargingPoints(1);
		Explode();
	}
	else if(MyOwner->RocketJumpCheck(this))
	{	
		MyOwner->RocketJump();
		Explode();
	}
}

void ABomb::Explode()
{
	//Applying damage and visuals
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEmitter, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	DamageComp->RadialDamage(Damage, DamageRadius);
	Destroy();
}