// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DefaultInputsDataAsset.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class SUMMERPROJECT_API UDefaultInputsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE UInputAction* GetMovementInputAction()	const { return MovementInputAction; }
	FORCEINLINE UInputAction* GetLookInputAction()		const { return LookInputAction; }
	FORCEINLINE UInputAction* GetRunInputAction()		const { return RunInputAction; }
	FORCEINLINE UInputAction* GetJumpInputAction()		const { return JumpInputAction; }
	FORCEINLINE UInputAction* GetGrabInputAction()		const { return GrabInputAction; }

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MovementInputAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RunInputAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> GrabInputAction;
};
