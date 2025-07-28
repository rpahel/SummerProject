// Copyright (c) 2025, Team Kazuki. All rights reserved.


#include "BTTask_RoutineInteract.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RoutineComponent.h"
#include "AIController.h"

UBTTask_RoutineInteract::UBTTask_RoutineInteract(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer)
{
	NodeName = "Routine Interact";
	INIT_TASK_NODE_NOTIFY_FLAGS();

}

EBTNodeResult::Type UBTTask_RoutineInteract::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	URoutineComponent* RoutineComp = Pawn->FindComponentByClass<URoutineComponent>();
	if (!RoutineComp)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTask_RoutineInteract::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UBTTask_RoutineInteract::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	
}
