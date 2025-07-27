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
		EIC->BindAction(MovementInputAction, ETriggerEvent::Triggered, this, &AKazuki::MoveCallback);

	//todo Run, jump, grab, etc. Ne pas oublier la cam.

	//if (UInputAction* RunInputAction = DefaultInputsDataAsset->GetRunInputAction())
	//{
	//	EIC->BindAction(RunInputAction, ETriggerEvent::Started, this, &AKazuki::MoveCallback);
	//	EIC->BindAction(RunInputAction, ETriggerEvent::Completed, this, &AKazuki::MoveCompletedCallback);
	//	EIC->BindAction(RunInputAction, ETriggerEvent::Canceled, this, &AKazuki::MoveCompletedCallback);
	//}
}

//====================================================================================
//==== PRIVATE CALLBACKS
//====================================================================================

void AKazuki::MoveCallback(const FInputActionInstance& InInputInstance)
{
	const FVector2D inputValue = InInputInstance.GetValue().Get<FVector2D>();

	UE_LOGFMT(LogTemp, Log, "AKazuki::MoveCallback : {0}", inputValue.ToString());

	GetCharacterMovement()->AddInputVector(GetTransform().TransformVectorNoScale(FVector(inputValue, 0)));
}