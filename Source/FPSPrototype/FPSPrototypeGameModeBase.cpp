// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSPrototypeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"

void AFPSPrototypeGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    NumberOfEnemies = 2;
}

void AFPSPrototypeGameModeBase::CharacterKilled(ACharacter* Character)
{
    //Checks if Game Has Ended after any Character is Killed
    APlayerCharacter* Player = Cast<APlayerCharacter>(Character);

    if(Player)
    {
        GameHasEnded(false);
    }
    else
    {
        AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Character);

        if(Enemy)
        {
            NumberOfEnemies--;
            
            UE_LOG(LogTemp, Warning, TEXT("Number of Enemies: %i"), NumberOfEnemies);

            if(NumberOfEnemies == 0)
            {
                GameHasEnded(true);
            }
        }
    }
}

void AFPSPrototypeGameModeBase::GameHasEnded(bool Result)
{
    //Handling game over
    //Creating Win/Lose screen and restarting game
    UUserWidget* EndScreen;
    APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if(Controller!=nullptr)
    {
        if(Result)
        {
            EndScreen = CreateWidget(Controller, WinScreenClass);
        }
        else
        {
            EndScreen = CreateWidget(Controller, LoseScreenClass);
        }
        if(EndScreen!=nullptr)
        {
            EndScreen->AddToViewport();
        }
        GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPSPrototypeGameModeBase::RestartLevel, 3, false);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Controller Invalid..."));
    }
    
}

void AFPSPrototypeGameModeBase::RestartLevel()
{
    //Restarting Level
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLevel"), true);
}

