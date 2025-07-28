// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kazuki.generated.h"

class ASPPlayerController;
class USpringArmComponent;
class UCameraComponent;
class UDefaultInputsDataAsset;
struct FInputActionInstance;

//! I'm too lazy to separate each feature to its component
//! so i'm doing everything in this class.
//! It's a one week prototype after all.
//! Still better than pirate software and elon musk.

UCLASS()
class SUMMERPROJECT_API AKazuki : public ACharacter
{
	GENERATED_BODY()

	friend class ASPPlayerController;

public:
	//==== Constructors ====

	AKazuki();

protected:
	//==== Overrides ====

	void PostInitializeComponents() final;
	void BeginPlay() final;
	void Tick(float DeltaTime) final;

private:
	//==== Properties ====

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki")
	TObjectPtr<UDefaultInputsDataAsset> DefaultInputsDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (ClampMin = 0.0f))
	float LookSensitivity = 1.0f; // Oui c'est sale je sais.

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (Units = "cm/s"))
	float MaxWalkSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (Units = "cm/s"))
	float MaxRunSpeed = 300.0f;

	//==== Methods ====

	void BindInputActions(UInputComponent* InInputComponent, ASPPlayerController* InController);

	//==== Callbacks ====

	UFUNCTION()
	void MoveCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void LookCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void JumpCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void RunCallback(const FInputActionInstance& InInputInstance);
};
