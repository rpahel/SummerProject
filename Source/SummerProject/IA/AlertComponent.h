// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlertComponent.generated.h"

UENUM(BlueprintType)
enum class AlertType : uint8
{
	Player UMETA(DisplayName = "Player")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUMMERPROJECT_API UAlertComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAlertComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	AlertType alertType;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
