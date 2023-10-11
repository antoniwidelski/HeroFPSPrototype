#include "MageCharacter.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MagicBall.h"
#include "DrawDebugHelpers.h"
#include "BorderPole.h"

AMageCharacter::AMageCharacter()
{
    //Component setup
    BallSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));  
}

void AMageCharacter::BeginPlay()
{
    Super::BeginPlay();

    //Component setup
    BallSpawnPoint->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
    BallSpawnPoint->SetRelativeLocation(FVector(0, 100, 120));
}

void AMageCharacter::Attack()
{
    Super::Attack();
}

void AMageCharacter::Teleport()
{
    //Teleporting in random location
    FVector Location = TeleportLocation();
    UE_LOG(LogTemp, Warning, TEXT("Teleport Location: %s"), *Location.ToString());
    SetActorLocation(Location);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), TeleportSound, GetActorLocation());
}

FVector AMageCharacter::TeleportLocation()
{
    //Finding random location between BorderPoles
    float xMin = 0;
    float xMax = 0;
    float yMin = 0;
    float yMax = 0;

    FVector BorderPoleLocation;

    TArray<AActor*> BorderPoles;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), BorderPoleClass, BorderPoles);

    for(int i = 0; i < BorderPoles.Num(); i++)
    {
        BorderPoleLocation = BorderPoles[i]->GetActorLocation();
        if(i==0)
        {
            xMin = BorderPoleLocation.X;
            xMax = BorderPoleLocation.X;
            yMin = BorderPoleLocation.Y;
            yMax = BorderPoleLocation.Y;
        }
        else
        {
            xMin = FMath::Min(xMin, BorderPoleLocation.X);
            xMax = FMath::Max(xMax, BorderPoleLocation.X);
            yMin = FMath::Min(yMin, BorderPoleLocation.Y);
            yMax = FMath::Max(yMax, BorderPoleLocation.Y);
        }
    }
    
    FVector TeleportLocation;
    TeleportLocation.X = FMath::RandRange(xMin, xMax);
    TeleportLocation.Y = FMath::RandRange(yMin, yMax);
    TeleportLocation.Z = GetActorLocation().Z;

    return TeleportLocation;
}

void AMageCharacter::SpawnMagicBall()
{
    //Spawning MagicBall
    CurrentBall = GetWorld()->SpawnActor<AMagicBall>(MagicBallClass, BallSpawnPoint->GetComponentLocation(), FRotator(0, 0, 0));
    CurrentBall->SetOwner(this);
    UE_LOG(LogTemp, Warning, TEXT("Spawning MagicBall..."));
}



