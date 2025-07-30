// Copyright (c) 2025, Team Kazuki. All rights reserved.

#include "Kazuki.h"
#include "DefaultInputsDataAsset.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Logging/StructuredLog.h"

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
	
	const FKazukiAnimationValues animValues = FKazukiAnimationValues(
		velocity.SquaredLength(),
		velocityNormal,
		IsJumpProvidingForce(),
		GetCharacterMovement()->IsFalling());

#if WITH_EDITOR
	DrawDebugDirectionalArrow(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + GetTransform().TransformVectorNoScale(velocity),
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
}

void AKazuki::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
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
		EIC->BindAction(MovementInputAction, ETriggerEvent::Triggered, this, &AKazuki::MoveCallback);
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
}

//====================================================================================
//==== PRIVATE CALLBACKS
//====================================================================================

void AKazuki::MoveCallback(const FInputActionInstance& InInputInstance)
{
	const FVector2D inputValue = InInputInstance.GetValue().Get<FVector2D>();
	GetCharacterMovement()->AddInputVector(GetTransform().TransformVectorNoScale(FVector(inputValue, 0)));
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
}

void AKazuki::RunCompletedCallback(const FInputActionInstance& InInputInstance)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}
