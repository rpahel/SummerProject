// Copyright (c) 2025, Team Kazuki. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlertComponent.generated.h"

//! Toujours prefixer le nom de ses enums d'un E !!
UENUM(BlueprintType)
enum class EAlertType : uint8
{
	EAT_None	= 0 UMETA(Hidden), //! Toujours mettre un None dans ses enums
	EAT_Player	= 1 UMETA(DisplayName = "Player")
};

UCLASS(ClassGroup = (SummerProject), meta = (BlueprintSpawnableComponent), AutoExpandCategories = "AlertComponent")
class SUMMERPROJECT_API UAlertComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAlertComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AlertComponent")
	EAlertType AlertType; //! Toujours mettre une majuscule a la premiere lettre de la variable t'es une fou du c++ pur toi ici c'est UE.

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
