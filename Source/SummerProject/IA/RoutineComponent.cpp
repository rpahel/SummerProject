// Copyright (c) 2025, Team Kazuki. All rights reserved.


#include "RoutineComponent.h"
#include "InteractableComponent.h"

URoutineComponent::URoutineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void URoutineComponent::InteractWithObjective()
{
	
}

FVector URoutineComponent::GetCurrentObjectivePosition() const
{
	if (Routine.IsValidIndex(CurrentIndexRoutine))
	{
		return Routine[CurrentIndexRoutine].ObjectivePosition;
	}
	return FVector::ZeroVector;
}

UInteractableComponent* URoutineComponent::GetCurrentObjectiveInteractable() const
{
	if (!Routine.IsValidIndex(CurrentIndexRoutine))
	{
		return nullptr;
	}

	if (RoutineInteractables.IsValidIndex(Routine[CurrentIndexRoutine].ObjectiveIndex))
	{
		return RoutineInteractables[Routine[CurrentIndexRoutine].ObjectiveIndex];
	}

	return nullptr;
}

void URoutineComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentIndexRoutine = StartingIndexRoutine;
}


void URoutineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

