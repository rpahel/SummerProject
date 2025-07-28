// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlertComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectDetectedEvent);

UENUM(BlueprintType)
enum class EAlertType : uint8
{
	EAT_None	= 0 UMETA(Hidden),
	EAT_Player	= 1 UMETA(DisplayName = "Player")
};

UCLASS(ClassGroup = (SummerProject), meta = (BlueprintSpawnableComponent), AutoExpandCategories = "AlertComponent")
class SUMMERPROJECT_API UAlertComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAlertComponent();

	UFUNCTION(BlueprintCallable)
	EAlertType GetAlertType() {return AlertType; }

	UFUNCTION(BlueprintCallable)
	void ObjectDetected();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AlertComponent")
	EAlertType AlertType;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, meta = (IsBindableEvent = true), Category = "Components|Alert")
	FOnObjectDetectedEvent OnObjectDetected;
};
