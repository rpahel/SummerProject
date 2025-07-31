// Copyright (c) 2025, Team Kazuki. All rights reserved.

#include "Kazuki.h"
#include "DefaultInputsDataAsset.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Logging/StructuredLog.h"

constexpr ECollisionChannel GrabbableCollisionChannel = ECC_GameTraceChannel1;

//====================================================================================
//==== PUBLIC CONSTRUCTORS
//====================================================================================

AKazuki::AKazuki()
{
	PrimaryActorTick.bCanEverTick = true;
}

FKazukiAnimationValues AKazuki::GetAnimationValues() const
{
	const FVector velocity = GetTransform().InverseTransformVectorNoScale(GetCharacterMovement()->GetLastUpdateVelocity());
	const FVector velocityNormal = velocity.GetSafeNormal();
	const float currentSpeedSqrd = velocity.SquaredLength();

	FVector lookAtLocation;
	if (CameraComponent)
	{
		lookAtLocation = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * LookDistance;
	}
	else
	{
		lookAtLocation = GetActorLocation() + GetActorForwardVector() * LookDistance;
	}

	const FKazukiAnimationValues animValues = FKazukiAnimationValues(
		velocityNormal * (currentSpeedSqrd / (MaxWalkSpeed * MaxWalkSpeed)),
		lookAtLocation,
		currentSpeedSqrd,
		IsJumpProvidingForce(),
		GetCharacterMovement()->IsFalling());

#if WITH_EDITOR
	DrawDebugDirectionalArrow(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + GetTransform().TransformVectorNoScale(velocity) * 0.5f,
		25,
		FColor::Cyan,
		false,
		-1,
		0,
		1
	);

	const FString debugString = FString::Printf(TEXT("SpeedSqrd = %f\nDirection = %s\nIsJumping = %u\nIsFalling = %u"),
		animValues.SpeedSqrd,
		*(animValues.LocalDirection.ToString()),
		+(animValues.IsJumping),
		+(animValues.IsFalling));

	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Cyan, debugString);
#endif // WITH_EDITOR

	return animValues;
}

//====================================================================================
//==== PROTECTED OVERRIDES
//====================================================================================

void AKazuki::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CameraComponent = GetComponentByClass<UCameraComponent>();
	SkeletalMeshComponent = GetComponentByClass<USkeletalMeshComponent>();
}

void AKazuki::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	bUseControllerRotationYaw = false;
}

void AKazuki::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//====================================================================================
//==== PRIVATE METHODS
//====================================================================================
 
void AKazuki::BindInputActions(UInputComponent* InInputComponent, ASPPlayerController* InController)
{
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InInputComponent);

	if (!EIC)
	{
		UE_LOG(LogTemp, Fatal, TEXT("AKazuki::BindInputActions() -> EIC not found !"));
		return;
	}

	if (!DefaultInputsDataAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("AKazuki::BindInputActions() -> DefaultInputsDataAsset is null ! Did you assign it in editor ?"));
		return;
	}

	if (UInputAction* MovementInputAction = DefaultInputsDataAsset->GetMovementInputAction())
	{
		EIC->BindAction(MovementInputAction, ETriggerEvent::Started, this, &AKazuki::MoveStartedCallback);
		EIC->BindAction(MovementInputAction, ETriggerEvent::Triggered, this, &AKazuki::MoveCallback);
		EIC->BindAction(MovementInputAction, ETriggerEvent::Completed, this, &AKazuki::MoveCompletedCallback);
		EIC->BindAction(MovementInputAction, ETriggerEvent::Canceled, this, &AKazuki::MoveCompletedCallback);
	}

	if (UInputAction* LookInputAction = DefaultInputsDataAsset->GetLookInputAction())
	{
		EIC->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AKazuki::LookCallback);
	}

	if (UInputAction* RunInputAction = DefaultInputsDataAsset->GetRunInputAction())
	{
		EIC->BindAction(RunInputAction, ETriggerEvent::Started, this, &AKazuki::RunStartedCallback);
		EIC->BindAction(RunInputAction, ETriggerEvent::Completed, this, &AKazuki::RunCompletedCallback);
		EIC->BindAction(RunInputAction, ETriggerEvent::Canceled, this, &AKazuki::RunCompletedCallback);
	}

	if (UInputAction* JumpInputAction = DefaultInputsDataAsset->GetJumpInputAction())
	{
		EIC->BindAction(JumpInputAction, ETriggerEvent::Started, this, &AKazuki::JumpStartedCallback);
		EIC->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &AKazuki::JumpCompletedCallback);
		EIC->BindAction(JumpInputAction, ETriggerEvent::Canceled, this, &AKazuki::JumpCompletedCallback);
	}

	if (UInputAction* GrabInputAction = DefaultInputsDataAsset->GetGrabInputAction())
	{
		EIC->BindAction(GrabInputAction, ETriggerEvent::Triggered, this, &AKazuki::GrabStartedCallback);
		EIC->BindAction(GrabInputAction, ETriggerEvent::Completed, this, &AKazuki::GrabCompletedCallback);
		EIC->BindAction(GrabInputAction, ETriggerEvent::Canceled, this, &AKazuki::GrabCompletedCallback);
	}
}

AActor* AKazuki::TraceForGrabbableObject(FHitResult& OutHitResult) const
{
	if (!CameraComponent)
		return nullptr;

	const FVector cameraLocation = CameraComponent->GetComponentLocation();

	FCollisionObjectQueryParams objectParams(GrabbableCollisionChannel);
	FCollisionQueryParams params("GrabTrace", true);

	if (GetWorld()->LineTraceSingleByObjectType(
		OutHitResult,
		cameraLocation,
		cameraLocation + CameraComponent->GetForwardVector() * LookDistance,
		objectParams,
		params))
	{
		return OutHitResult.GetActor();
	}

	return nullptr;
}

//====================================================================================
//==== PRIVATE CALLBACKS
//====================================================================================

void AKazuki::MoveStartedCallback(const FInputActionInstance& InInputInstance)
{
	bUseControllerRotationYaw = true;
}

void AKazuki::MoveCallback(const FInputActionInstance& InInputInstance)
{
	const FVector2D inputValue = InInputInstance.GetValue().Get<FVector2D>();
	GetCharacterMovement()->AddInputVector(GetTransform().TransformVectorNoScale(FVector(inputValue, 0)));
	if (FVector2D::UnitX().Dot(inputValue.GetSafeNormal()) < StrafeRatio)
		GetCharacterMovement()->MaxWalkSpeed = MaxStrafeSpeed;
	else
		GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? MaxRunSpeed : MaxWalkSpeed;
}

void AKazuki::MoveCompletedCallback(const FInputActionInstance& InInputInstance)
{
	bUseControllerRotationYaw = false;
}

void AKazuki::LookCallback(const FInputActionInstance& InInputInstance)
{
	const FVector2D inputValue = InInputInstance.GetValue().Get<FVector2D>();
	AddControllerYawInput(inputValue.X * LookSensitivity);
	AddControllerPitchInput(-inputValue.Y * LookSensitivity);
}

void AKazuki::JumpStartedCallback(const FInputActionInstance& InInputInstance)
{
	if (CanJump())
	{
		Jump();
	}
}

void AKazuki::JumpCompletedCallback(const FInputActionInstance& InInputInstance)
{
	StopJumping();
}

void AKazuki::RunStartedCallback(const FInputActionInstance& InInputInstance)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
	bIsRunning = true;
}

void AKazuki::RunCompletedCallback(const FInputActionInstance& InInputInstance)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	bIsRunning = false;
}

void AKazuki::GrabStartedCallback(const FInputActionInstance& InInputInstance)
{
	if (bIsGrabPressed) return;
	bIsGrabPressed = true;

	FHitResult hitResult;
	if (AActor* hitActor = TraceForGrabbableObject(hitResult))
	{
#if WITH_EDITOR
		DrawDebugPoint(
			GetWorld(),
			hitResult.ImpactPoint,
			10,
			FColor::Green,
			false,
			2
		);
#endif // WITH_EDITOR

		hitResult.GetComponent()->WakeRigidBody();
	}
#if WITH_EDITOR
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "AKazuki::GrabStartedCallback -> NO GRABBABLE ACTOR HIT.");
	}
#endif
}

void AKazuki::GrabCompletedCallback(const FInputActionInstance& InInputInstance)
{
	bIsGrabPressed = false;

#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(2, 2, FColor::Red, "AKazuki::GrabStartedCallback -> END GRAB.");
#endif
}
