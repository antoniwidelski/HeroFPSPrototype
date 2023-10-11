#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    //Running AI
    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("BehaviorTreeInvalid"));
    }
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerPawn"), PlayerPawn);
}

