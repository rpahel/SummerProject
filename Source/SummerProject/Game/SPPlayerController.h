// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSPControllerSignature);

class AKazuki;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

/**
 * 
 */
UCLASS(
	AutoExpandCategories = ("Controller")
)
class SUMMERPROJECT_API ASPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, meta = (IsBindableEvent = true))
	FSPControllerSignature OnPauseDelegate;

	UPROPERTY(BlueprintAssignable, meta = (IsBindableEvent = true))
	FSPControllerSignature OnResumeDelegate;

public:
	//==== Overrides ====

	bool SetPause(bool bPause, FCanUnpause CanUnpauseDelegate = FCanUnpause()) final;

	//==== Methods ====

	void AddMappingContext(UInputMappingContext* InIMC, uint32 InPriority);
	void RemoveMappingContext(UInputMappingContext* InIMC);

private:
	//==== Exposed Fields ====

	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	TObjectPtr<UInputMappingContext> IMC_Default;

	//==== Hidden Fields ====

	UPROPERTY(VisibleAnywhere, Category = "Controller|Debug")
	TObjectPtr<AKazuki> Kazuki;

	UPROPERTY(VisibleAnywhere, Category = "Controller|Debug")
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem;

	//==== Overrides ====

	void BeginPlay() final;
	void SetupInputComponent() final;

	//==== Methods ====

	void SetUpInputMappingContext();
	void BindInputActions();
};
