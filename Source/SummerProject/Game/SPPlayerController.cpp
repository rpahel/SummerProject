// Copyright (c) 2025, Team Kazuki. All rights reserved.


#include "SPPlayerController.h"
#include "SummerProject/Player/Kazuki.h"

#include "EnhancedPlayerInput.h"
#include "EnhancedInputSubsystems.h"

//====================================================================================
//==== PUBLIC OVERRIDES
//====================================================================================

bool ASPPlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate)
{
	if (!Super::SetPause(bPause, CanUnpauseDelegate))
		return false;

	SetShowMouseCursor(bPause);

	if (bPause)
	{
		SetInputMode(FInputModeGameAndUI());
		OnPauseDelegate.Broadcast();
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		OnResumeDelegate.Broadcast();
	}

	return true;
}

void ASPPlayerController::AddMappingContext(UInputMappingContext* InIMC, uint32 InPriority)
{
	if (!InputSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("ASPPlayerController::SetUpInputMappingContext() -> InputSubsystem is null !"));
		return;
	}

	InputSubsystem->AddMappingContext(InIMC, InPriority);
}

void ASPPlayerController::RemoveMappingContext(UInputMappingContext* InIMC)
{
	if (!InputSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("ASPPlayerController::SetUpInputMappingContext() -> InputSubsystem is null !"));
		return;
	}

	InputSubsystem->RemoveMappingContext(InIMC);
}


//====================================================================================
//==== PRIVATE OVERRIDES
//====================================================================================

void ASPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ensure(Kazuki = Cast<AKazuki>(GetCharacter()));

	// SetupInputComponent() is called before every actor has been instantiated.
	// So I can this here to ensure the player has been spawned.
	BindInputActions();
}

void ASPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	SetUpInputMappingContext();
}

//====================================================================================
//==== PRIVATE METHODS
//====================================================================================

void ASPPlayerController::SetUpInputMappingContext()
{
	InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!InputSubsystem)
	{
		UE_LOG(LogTemp, Fatal, TEXT("ASPPlayerController::SetUpInputMappingContext() -> Could not get InputSubsystem !"));
		return;
	}

	if (!IMC_Default)
	{
		UE_LOG(LogTemp, Error, TEXT("ASPPlayerController::SetUpInputMappingContext() -> IMC_Main is null."));
		return;
	}

	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(IMC_Default, 0); // 0 should be ok for now, has there is no plan to have another IMC.
}

void ASPPlayerController::BindInputActions()
{
	if (Kazuki) Kazuki->BindInputActions(InputComponent, this);
}
