#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RandomWait.generated.h"

UCLASS()
class FPSPROTOTYPE_API UBTTask_RandomWait : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RandomWait();

private:
	FTimerHandle TimerHandle;

	float ShouldEnd = false;

	UBehaviorTreeComponent* MyOwnerComp;

	float GenerateWaitTime();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

	void OnTaskFinished();
};
