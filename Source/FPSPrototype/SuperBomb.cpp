#include "SuperBomb.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "DamageComponent.h"
#include "InvisibleWall.h"

ASuperBomb::ASuperBomb()
{
	//Compotents setup
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetEnableGravity(true);

	DamageComp = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComp"));
}

void ASuperBomb::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->OnComponentHit.AddDynamic(this, &ASuperBomb::OnHit);
	GetWorldTimerManager().SetTimer(CollisionTimerHandle, this, &ASuperBomb::ChangeCollisionSettings, CollisionTime, false);
}

void ASuperBomb::Tick(float DeltaTime)
{
	//Keeping bomb in place
	Super::Tick(DeltaTime);

	if(Grounded)
	{
		SetActorTransform(Transform);
	}
}

void ASuperBomb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Setting position and timer
	if(!Grounded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Hit"));
		Transform = GetActorTransform();
		GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ASuperBomb::Explode, SuperBombExplosionTime, false);
		Grounded = true;
	}
	
}

void ASuperBomb::Explode()
{
	//Exploding in given range
	FVector ActorLocation = GetActorLocation();
	UWorld* World = GetWorld();
	UGameplayStatics::SpawnEmitterAtLocation(World, ExplosionEmitter, ActorLocation, GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(World, ExplosionSound, ActorLocation);
	DamageComp->RadialDamage(Damage, DamageRadius);
	int Radius = int(DamageRadius);
	for(int i = 0; i<=50; i++)
	{
		FVector RandomLocation = FVector(FMath::RandRange(-Radius, Radius), FMath::RandRange(-Radius, Radius), FMath::RandRange(0, Radius));
		while(FVector::Distance(FVector(0, 0, 0), RandomLocation) > Radius)
		{
			RandomLocation = FVector(FMath::RandRange(-Radius, Radius), FMath::RandRange(-Radius, Radius), FMath::RandRange(0, Radius));
		}
		FRotator RandomRotation = FRotator(FMath::RandRange(0, 360), FMath::RandRange(0, 360), 0);
		UGameplayStatics::SpawnEmitterAtLocation(World, ExplosionEmitter, ActorLocation+RandomLocation, RandomRotation);
		UGameplayStatics::PlaySoundAtLocation(World, ExplosionSound, ActorLocation+RandomLocation);
	}
	Destroy();
}

void ASuperBomb::ChangeCollisionSettings()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}