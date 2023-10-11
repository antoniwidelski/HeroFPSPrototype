#include "MagicBall.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DamageComponent.h"
#include "PlayerCharacter.h"

AMagicBall::AMagicBall()
{
	//Components setup
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	DamageComp = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComp"));
}

void AMagicBall::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMagicBall::Overlap);

	//Rotating to player
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(Player)
	{
		FVector PlayerLocation = Player->GetActorLocation();
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerLocation);
		SetActorRotation(Rotation);
	}
	
}

void AMagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Moving actor
	AddActorWorldOffset(GetActorForwardVector() * DeltaTime * Speed);
}

void AMagicBall::Overlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	//Checking if overlapping Actor is Player and damaging him
	if(OtherActor)
	{
		APawn* Player = Cast<APlayerCharacter>(OtherActor);
		if(Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlapped: %s"), *OtherActor->GetName());

			DamageComp->PointDamage(Damage, OtherActor);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), WhooshSound, GetActorLocation());
		}
	}
}


