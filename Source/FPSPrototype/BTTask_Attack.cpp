// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "EnemyCharacter.h"
#include "AIController.h"

UBTTask_Attack::UBTTask_Attack()
{
    NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();
    if(Controller == nullptr) return EBTNodeResult::Failed;

    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Controller->GetPawn());

    if(Enemy)
    {
        Enemy->Attack();

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

