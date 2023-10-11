#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Teleport.generated.h"


UCLASS()
class FPSPROTOTYPE_API UBTTask_Teleport : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Teleport();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;	
};
