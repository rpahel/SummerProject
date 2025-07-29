// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include <BehaviorTree/Tasks/BTTask_BlackboardBase.h>
#include <BehaviorTree/ValueOrBBKey.h>
#include "BTTask_RoutineInteract.generated.h"

UCLASS()
class SUMMERPROJECT_API UBTTask_RoutineInteract : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_RoutineInteract(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category = Interaction, EditAnywhere, DisplayName = InteractionRange)
	FValueOrBBKey_Float InteractionRange;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
};
