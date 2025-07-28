// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

// Si tu vois ce message envoie "kiki t bo" sur le groupe discord
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionEvent, AActor*, ActorInteracting);

UCLASS(ClassGroup = (SummerProject), meta = (BlueprintSpawnableComponent), AutoExpandCategories = "InteractableComponent")
class SUMMERPROJECT_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractableComponent();

	UFUNCTION(BlueprintCallable)
	void Interact(AActor* ActorInteracting);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, meta=(IsBindableEvent=true), Category = "Components|Interactable")
	FOnInteractionEvent OnInteracted;
};
