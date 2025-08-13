// Copyright (c) 2025, Team Kazuki. All rights reserved.


#include "RoutineComponent.h"
#include "InteractableComponent.h"

URoutineComponent::URoutineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void URoutineComponent::InteractWithObjective()
{
	UInteractableComponent* interactable = GetCurrentObjectiveInteractable();
	if (!interactable)
	{
		GoNextObjective();
		return;
	}

	interactable->Interact(GetOwner());
	GoNextObjective();
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

void URoutineComponent::GoNextObjective()
{
	++CurrentIndexRoutine;
	if (CurrentIndexRoutine >= Routine.Num())
		CurrentIndexRoutine = 0;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Changed Objective");
	OnIndexChanged.Broadcast(CurrentIndexRoutine);
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

