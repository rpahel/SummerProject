// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RoutineComponent.generated.h"

class UInteractableComponent;

USTRUCT(BlueprintType)
struct FRoutineObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVector ObjectivePosition;

	UPROPERTY(EditAnywhere)
	int ObjectiveIndex;
};

UCLASS(ClassGroup = (SummerProject), meta = (BlueprintSpawnableComponent), AutoExpandCategories = "RoutineComponent")
class SUMMERPROJECT_API URoutineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URoutineComponent();

	UFUNCTION(BlueprintCallable)
	void InteractWithObjective();

	UFUNCTION(BlueprintCallable)
	FVector GetCurrentObjectivePosition() const;

	UFUNCTION(BlueprintCallable)
	UInteractableComponent* GetCurrentObjectiveInteractable() const;

private:
	UPROPERTY(EditAnywhere, Category = "Routine")
	int32 StartingIndexRoutine = 0;

	UPROPERTY()
	int32 CurrentIndexRoutine;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Routine")
	TArray<FRoutineObjective> Routine;

	UPROPERTY(EditAnywhere, Category = "Routine")
	TArray<TObjectPtr<UInteractableComponent>> RoutineInteractables;


};
