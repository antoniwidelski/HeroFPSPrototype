#include "BarbarianCharacter.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "DamageComponent.h" 
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABarbarianCharacter::ABarbarianCharacter()
{
    //Components setup
    HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));    
    HitBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

    DamageComp = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComp"));
}

void ABarbarianCharacter::BeginPlay()
{
    Super::BeginPlay();

    //Hitbox setup
    HitBox->OnComponentBeginOverlap.AddDynamic(this, &ABarbarianCharacter::Overlap);
}

void ABarbarianCharacter::Attack()
{
    Super::Attack();

    UE_LOG(LogTemp, Warning, TEXT("Barbarian Attacking... "));
}

void ABarbarianCharacter::JumpAttack()
{
    //It jumps at Player
    APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if(Player)
    {
        FRotator CurrentRotation = GetActorRotation();
        FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());

        FVector Direction = Rotation.Vector();

        Rotation.Pitch = 0;
        Rotation.Roll = 0;
        SetActorRotation(Rotation);

        FVector Velocity = Direction * FVector::Distance(GetActorLocation(), Player->GetActorLocation()) * JumpPower;

        UE_LOG(LogTemp, Warning, TEXT("Jumping Velocity: %s"), *Velocity.ToString());
        LaunchCharacter(Velocity, false, false);
    }
    
}

void ABarbarianCharacter::Overlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    //If hitbox overlapps Player and is in Attack state it damages Player once
    if(GetIsAttacking() && Cast<APlayerCharacter>(OtherActor) && !HitAlready)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character Hit: %s"), *OtherActor->GetName());
        HitAlready = true;
        DamageComp->PointDamage(Damage, OtherActor);
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), SlashSound, GetActorLocation());
    }
    
}

void ABarbarianCharacter::StopAttack()
{
    Super::StopAttack();

    HitAlready = false;
}