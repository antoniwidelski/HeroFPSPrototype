// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomWait.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"



UBTTask_RandomWait::UBTTask_RandomWait()
{
    NodeName = "RandomWait";
}



EBTNodeResult::Type UBTTask_RandomWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (Character != nullptr)
    {
        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
        if (BlackboardComp != nullptr)
        {
            BlackboardComp->SetValueAsBool("IsWaiting", true);

            float WaitTime = GenerateWaitTime();

            Character->GetWorldTimerManager().SetTimer(TimerHandle, this, &UBTTask_RandomWait::OnTaskFinished, WaitTime, false);

            MyOwnerComp = &OwnerComp;

            return EBTNodeResult::InProgress;
        }
    }

    return EBTNodeResult::Failed;
}

void UBTTask_RandomWait::OnTaskFinished()
{
    if (MyOwnerComp)
    {
        UBlackboardComponent* BlackboardComp = MyOwnerComp->GetBlackboardComponent();
        if (BlackboardComp != nullptr)
        {
            BlackboardComp->SetValueAsBool("IsWaiting", false);
        }
    }

    FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
}

float UBTTask_RandomWait::GenerateWaitTime()
{
    return FMath::RandRange(1, 3);
}
