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

USTRUCT(BlueprintType)
struct SUMMERPROJECT_API FKazukiAnimationValues
{
	GENERATED_BODY()

	FKazukiAnimationValues() = default;
	FKazukiAnimationValues(const FVector& InLocalDirection, const FVector& InLookAtLocation, float InSpeedSqrd, bool InIsJumping, bool InIsFalling)
		: LocalDirection(InLocalDirection), LookAtLocation(InLookAtLocation), SpeedSqrd(InSpeedSqrd), IsJumping(InIsJumping), IsFalling(InIsFalling)
	{ }

	UPROPERTY(BlueprintReadOnly)
	FVector LocalDirection = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	FVector LookAtLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	float SpeedSqrd = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	bool IsJumping = false;

	UPROPERTY(BlueprintReadOnly)
	bool IsFalling = false;
};

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

	//==== Methods ====

	UFUNCTION(BlueprintCallable)
	FKazukiAnimationValues GetAnimationValues() const; // Called by Animation Blueprint

protected:
	//==== Overrides ====

	void PostInitializeComponents() final;
	void BeginPlay() final;
	void Tick(float DeltaTime) final;

private:
	//==== Exposed Properties ====

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki")
	TObjectPtr<UDefaultInputsDataAsset> DefaultInputsDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki")
	FName GrabBoneName;

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (ClampMin = 0.0f))
	float LookDistance = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (ClampMin = 0.0f))
	float LookSensitivity = 1.0f; // Oui c'est sale je sais.

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (Units = "cm/s"))
	float MaxWalkSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (Units = "cm/s"))
	float MaxRunSpeed = 150.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (Units = "cm/s"))
	float MaxStrafeSpeed = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Kazuki", meta = (ToolTip = "Rapport de movement vers l'avant sous lequel on considere qu'on strafe."))
	float StrafeRatio = 0.707f;

	//==== Hidden Properties ====

	UPROPERTY()
	TObjectPtr<USceneComponent> CameraComponent = nullptr;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;

	bool bIsRunning = false;
	bool bIsGrabPressed = false;

	//==== Methods ====

	void BindInputActions(UInputComponent* InInputComponent, ASPPlayerController* InController);
	AActor* TraceForGrabbableObject(FHitResult& OutHitResult) const;

	//==== Callbacks ====

	UFUNCTION()
	void MoveCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void MoveStartedCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void MoveCompletedCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void LookCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void JumpStartedCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void JumpCompletedCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void RunStartedCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void RunCompletedCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void GrabStartedCallback(const FInputActionInstance& InInputInstance);

	UFUNCTION()
	void GrabCompletedCallback(const FInputActionInstance& InInputInstance);
};
