// Copyright (c) 2025, Team Kazuki. All rights reserved.


#include "AlertComponent.h"

UAlertComponent::UAlertComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UAlertComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UAlertComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

