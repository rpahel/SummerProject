// Copyright (c) 2025, Team Kazuki. All rights reserved.


#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UInteractableComponent::Interact(AActor* ActorInteracting)
{
	OnInteracted.Broadcast(ActorInteracting);
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

