// Fill out your copyright notice in the Description page of Project Settings.


#include "BomberCharacter.h"
#include "Bomb.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Mine.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Pointer.h"
#include "SuperBomb.h"

void ABomberCharacter::BeginPlay()
{
    Super::BeginPlay();
    CharMoveComp = GetCharacterMovement();
    Controller = Cast<AMyPlayerController>(GetController());
}

// Called to bind functionality to input
void ABomberCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABomberCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Checks if Player is placing the mine or is using SuperBomb's pointer
    //If true then changes its position
    bool bSuccess;
    FHitResult Hit;

    if(IsPlacingMine && CurrentMine)
    {
        bSuccess = PlaceTrace(Hit, MaxMinePlacingRange);
        if(bSuccess)
        {
            CurrentMine->SetActorLocation(Hit.Location);
        }
        else
        {
            FVector MineNewLocation = GetActorLocation() + GetActorForwardVector() * MaxMinePlacingRange;
            MineNewLocation.Z = MineZ;
            CurrentMine->SetActorLocation(MineNewLocation);
        }
    }
    else if(IsPointing && Pointer)
    {
        bSuccess = PlaceTrace(Hit, 10000);
        if(bSuccess)
        {
            Pointer->SetActorLocation(Hit.Location);
        }
    }
}

void ABomberCharacter::MainAttack()
{
    //Checks if Player's pointing or placing the mine
    //if true it spawns SuperBomb or arms the mine
    //if false it shoot a bomb if its able to and launches cooldown event
    if(IsPlacingMine)
    {
        StopPlacingMine(true);
        return;
    }
    else if(IsPointing)
    {
        StopPointing(true);
        return;
    }
    if(IsMACooled)
    {
        Super::MainAttack();
    
        SpawnBomb();
        IsMACooled = false;
        if(Controller)
        {
            Controller->CooldownEvent(1);
            UE_LOG(LogTemp, Warning, TEXT("Controller is Valid..."));
        }
        GetWorldTimerManager().SetTimer(MATimerHandle, this, &APlayerCharacter::MACooldown, MainAttackCooldownTime, false);
    }
    else
    {
        AbilityFailed();
        UE_LOG(LogTemp, Warning, TEXT("Main Attack Is Colling Down..."));
    }
}

void ABomberCharacter::FirstAbility()
{
    //Checks if Player's pointing or placing the mine
    //if true it abandons this activity
    //if false it bursts three bombs if its able to 
    if(IsPlacingMine)
    {
        StopPlacingMine(false);
        return;
    }
    else if(IsPointing)
    {
        StopPointing(false);
        return;
    }

    if(IsFACooled)
    {
        Super::FirstAbility();

        GetWorldTimerManager().SetTimer(BurstTimerHanlde, this, &ABomberCharacter::Burst, BurstRate, true, 0);
    }
    else
    {
        AbilityFailed();
        UE_LOG(LogTemp, Warning, TEXT("First Ability Is Colling Down..."));
    }

}

void ABomberCharacter::SecondAbility()
{
    //Checks conditions to place mine and start the process if they're met
    if(MineCounter()<3 && !CharMoveComp->IsFalling() && IsSACooled)
    {
        if(!IsPlacingMine)
        {
            Super::SecondAbility();

            StartPlacingMine();
        }
    }
    else
    {
        AbilityFailed();
        UE_LOG(LogTemp, Warning, TEXT("Second Ability Is Colling Down..."));
    }
}

void ABomberCharacter::UltimateAbility()
{
    //Checks conditions to use pointer and start the process if they're met
    Super::UltimateAbility();

    if(!IsPointing && !IsPlacingMine)
    {
        if(GetChargingPoints()>=UltimateAbilityChargingCapacity)
        {
            StartPointing();
        }
        else
        {
            AbilityFailed();
            UE_LOG(LogTemp, Warning, TEXT("Ultimate Ability Is Colling Down..."));
        }
        
    }
}

void ABomberCharacter::CustomAction()
{
    //explodes all mines if there are any and launches cooldown event
    if(MineCounter()>0 )
    {
        ExplodeAllMines();
        ExplodeAllMines();
        Controller->ShowCWidget(false);
        IsSACooled = false;
        Controller->CooldownEvent(3);
        GetWorldTimerManager().SetTimer(SATimerHandle, this, &APlayerCharacter::SACooldown, SecondAbilityCooldownTime, false);
    }
    
}

void ABomberCharacter::Jump()
{
    //Bomber can't place mine if jumping
    UE_LOG(LogTemp, Warning, TEXT("Jumping..."));
    if(IsPlacingMine)
    {
        StopPlacingMine(false);
    }

    Super::Jump();
}

void ABomberCharacter::SpawnBomb()
{
    //Spawns bomb actor and plays launching sound

    FVector Location = ProjectileSpawnPoint->GetComponentLocation();
    if(GetCamera()==nullptr) return;
    FRotator Rotation = Camera->GetComponentRotation();

    Bomb = GetWorld()->SpawnActor<ABomb>(BombClass, Location, Rotation);
    Bomb->SetOwner(this);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), LauncherSound, GetActorLocation());
}

void ABomberCharacter::RocketJump()
{
    //Launches Bomber into the sky

    UE_LOG(LogTemp, Warning, TEXT("Rocket Jump!"));

    FVector Velocity(0, 0, UpVelocity);
    LaunchCharacter(Velocity, false, false);
}

bool ABomberCharacter::RocketJumpCheck(AActor* Actor)
{
    //Checks if Bomber and Mine or Bomb meet all conditions to perform RocketJump and returns the result

    FVector PlayerLocation = this->GetActorLocation();
	FVector ActorLocation = Actor->GetActorLocation();
    float DistanceZ = PlayerLocation.Z-ActorLocation.Z;
    float DistanceXY = FMath::Sqrt(FMath::Square(PlayerLocation.X-ActorLocation.X)+FMath::Square(PlayerLocation.Y-ActorLocation.Y));

    if(DistanceZ>0 && DistanceZ<MaxDistanceZ && DistanceXY<MaxDistanceXandY && ((Cast<ABomb>(Actor)&&CharMoveComp->IsFalling())||Cast<AMine>(Actor)))
    {
        UE_LOG(LogTemp, Warning, TEXT("DistanceZ: %f"), DistanceZ);
        UE_LOG(LogTemp, Warning, TEXT("DistanceXY: %f"), DistanceXY);
        return true;
    }
    return false;
}

void ABomberCharacter::Burst()
{
    //Spawns three bombs in intervals and launch cooldown event

    if(BurstCounter<=2)
    {
        SpawnBomb();
        BurstCounter++;
    }
    else
    {
        BurstCounter = 0;
        IsFACooled = false;
        if(Controller) Controller->CooldownEvent(2);
        GetWorldTimerManager().SetTimer(FATimerHandle, this, &APlayerCharacter::FACooldown, FirstAbilityCooldownTime, false);
        GetWorldTimerManager().PauseTimer(BurstTimerHanlde);
    }
}

void ABomberCharacter::StartPlacingMine()
{
    //Checks if Bomber is looking at the floor in range to spawn mine
    //if true it spawns unarmed ghost mine

    UE_LOG(LogTemp, Warning, TEXT("Starting Placing Mine..."));

    FHitResult Hit;
    bool bSuccess = PlaceTrace(Hit, MaxMinePlacingRange);
    if(bSuccess)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawning Mine..."));
        CurrentMine = GetWorld()->SpawnActor<AMine>(MineClass, Hit.Location, FRotator(0, 0, 0));
        if(CurrentMine != nullptr) IsPlacingMine = true;
        MineZ = Hit.Location.Z;
        CurrentMine->SetOwner(this);
    }
}

void ABomberCharacter::StopPlacingMine(bool Commit)
{
    //if true it arms mine and adds widget to show how to destroy it
    //if false it destroys the mine

    if(Commit)
    {
        if(CurrentMine && Controller)
        UE_LOG(LogTemp, Warning, TEXT("Mine Placed..."));
        CurrentMine->Arm();
        Controller->ShowCWidget(true);
    }
    else
    {
        CurrentMine->Destroy();
    }
    IsPlacingMine = false;
}

bool ABomberCharacter::PlaceTrace(FHitResult& HitResult, float PlaceRange)
{
    //Line tracing by "MinePlace" custom channel from camera to given range and returns if object is found

    if(!Controller) return false;

    FVector Location;
    FRotator Rotation;
    Controller->GetPlayerViewPoint(Location, Rotation);

    FVector End = Location + Rotation.Vector() * PlaceRange;
    FCollisionQueryParams Params;

    return GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECC_GameTraceChannel1);
}

int ABomberCharacter::MineCounter()
{
    //returns number of mines placed

    TArray<AActor*> Mines;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), MineClass, Mines);
    return Mines.Num();
}

void ABomberCharacter::ExplodeAllMines()
{
    //Explodes all mines placed in the world

    if(MineCounter()>0)
    {
        TArray<AActor*> Mines;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), MineClass, Mines);
        UE_LOG(LogTemp, Warning, TEXT("Mines Placed: %i"), MineCounter());
        for(int i = 0; i<MineCounter()+1; i++)
        {
            TArray<AActor*> MinesTwo;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), MineClass, MinesTwo);
            AMine* Mine = Cast<AMine>(MinesTwo.Top());
            if(Mine!=nullptr)
            {
                Mine->Explode();
            }
        }
    }
}


void ABomberCharacter::StartPointing()
{
    //Checks if Bomber is looking at the floor in range to start pointing
    //If true it spawns pointer on the floor

    UE_LOG(LogTemp, Warning, TEXT("Starting Pointing..."));

    FHitResult Hit;
    bool bSuccess = PlaceTrace(Hit, 10000);
    if(bSuccess)
    {
        UE_LOG(LogTemp, Warning, TEXT("Pointing..."));
        Pointer = GetWorld()->SpawnActor<APointer>(PointerClass, Hit.Location, FRotator(0, 0, 0));
        if(Pointer != nullptr) IsPointing = true;
        PointerZ = Hit.Location.Z;
        Pointer->SetOwner(this);
    }
}

void ABomberCharacter::StopPointing(bool Commit)
{
    //It destroys pointer and if true it spawns SuperBomb

    if(Commit)
    {
        FVector Location = Pointer->GetActorLocation();
        Location.Z = Location.Z + 5000;
        Pointer->Destroy();
        SuperBomb = GetWorld()->SpawnActor<ASuperBomb>(SuperBombClass, Location, FRotator(0, 0, 0));
        SuperBomb->SetOwner(this);
        ChargingPoints = 0;

        IsPointing = false;
    }
    else
    {
        Pointer->Destroy();
        IsPointing = false;
    }
}